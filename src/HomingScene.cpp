// Copyright (c) 2023 - Barton Dring
// Use of this source code is governed by a GPLv3 license that can be found in the LICENSE file.

#include "Scene.h"
#include "ConfigItem.h"

extern Scene statusScene;

// Use MAX_AXES from FluidNCModel.h for consistency
IntConfigItem homing_cycles[MAX_AXES] = {
    { "$/axes/x/homing/cycle" },
    { "$/axes/y/homing/cycle" },
    { "$/axes/z/homing/cycle" },
    { "$/axes/a/homing/cycle" },
    { "$/axes/b/homing/cycle" },
    { "$/axes/c/homing/cycle" },
};
BoolConfigItem homing_allows[MAX_AXES] = {
    { "$/axes/x/homing/allow_single_axis" },
    { "$/axes/y/homing/allow_single_axis" },
    { "$/axes/z/homing/allow_single_axis" },
    { "$/axes/a/homing/allow_single_axis" },
    { "$/axes/b/homing/allow_single_axis" },
    { "$/axes/c/homing/allow_single_axis" },
};

int  homed_axes = 0;
bool is_homed(int axis) {
    return homed_axes & (1 << axis);
}
void set_axis_homed(int axis) {
    homed_axes |= 1 << axis;
    current_scene->reDisplay();
}

void detect_homing_info() {
    // Initialize homing info for all axes that FluidNC reports
    for (int i = 0; i < n_axes; i++) {
        homing_cycles[i].init();
        homing_allows[i].init();
    }
    homed_axes = 0;
}
bool can_home(int i) {
    // Cannot home if cycle == 0 and !allow_single_axis
    // Also can't home axes beyond what FluidNC reports
    if (i >= n_axes) return false;
    return homing_cycles[i].get() != 0 || homing_allows[i].get();
}

bool have_homing_info() {
    // Check if we have info for the last configured axis
    return n_axes > 0 && homing_allows[n_axes - 1].known();
}

class HomingScene : public Scene {
private:
    int _axis_to_home = -1;
    int _auto         = false;

    bool _allows[MAX_AXES];

public:
    HomingScene() : Scene("Home", 4) {}

    bool is_homing(int axis) { return can_home(axis) && (_axis_to_home == -1 || _axis_to_home == axis); }
    void onEntry(void* arg) override {
        if (state == Idle && _auto) {
            pop_scene();
        }
        const char* s = static_cast<const char*>(arg);
        _auto         = s && strcmp(s, "auto") == 0;
    }

    void onStateChange(state_t old_state) override {
#ifdef AUTO_HOMING_RETURN
        if (old_state == Homing && state == Idle && _auto) {
            pop_scene();
        }
#endif
    }
    void onDialButtonPress() override { pop_scene(); }
    void onGreenButtonPress() override {
        if (state == Idle || state == Alarm) {
            if (_axis_to_home != -1) {
                send_linef("$H%c", axisNumToChar(_axis_to_home));
            } else {
                send_line("$H");
            }
        } else if (state == Cycle) {
            fnc_realtime(FeedHold);
        } else if (state == Hold || state == DoorClosed) {
            fnc_realtime(CycleStart);
        }
    }
    void onRedButtonPress() override {
        if (state == Homing || state == Alarm) {
            fnc_realtime(Reset);
        }
    }

    void increment_axis_to_home() {
        do {
            ++_axis_to_home;
            if (_axis_to_home > n_axes) {
                _axis_to_home = -1;
                return;
            }
        } while (!can_home(_axis_to_home));
    }
    void onTouchClick() {
        if (state == Idle || state == Homing || state == Alarm) {
            increment_axis_to_home();
            reDisplay();
            ackBeep();
        }
    }

    void onEncoder(int delta) override {
        increment_axis_to_home();
        reDisplay();
    }
    void onDROChange() { reDisplay(); }  // also covers any status change

    void reDisplay() {
        background();
        drawMenuTitle(current_scene->name());
        drawStatus();

        const char* redLabel    = "";
        std::string grnLabel    = "";
        const char* orangeLabel = "";
        std::string green       = "Home ";

        if (false && state == Homing) {
            // Calculate DRO row height based on axis count
            int dro_height = (n_axes <= 3) ? 32 : (n_axes <= 4) ? 28 : 24;
            int dro_start_y = (n_axes <= 3) ? 68 : (n_axes <= 4) ? 64 : 58;
            DRO dro(16, dro_start_y, 210, dro_height);
            for (int axis = 0; axis < n_axes; axis++) {
                dro.draw(axis, -1, true);
            }

        } else if (state == Idle || state == Homing || state == Alarm) {
            // Calculate DRO row height based on axis count
            int dro_height = (n_axes <= 3) ? 32 : (n_axes <= 4) ? 28 : 24;
            int dro_start_y = (n_axes <= 3) ? 68 : (n_axes <= 4) ? 64 : 58;
            DRO dro(16, dro_start_y, 210, dro_height);
            for (int axis = 0; axis < n_axes; ++axis) {
                dro.drawHoming(axis, is_homing(axis), is_homed(axis));
            }

#if 0
            int x      = 50;
            int y      = 65;
            int width  = display.width() - (x * 2);
            int height = 32;

            Stripe button(x, y, width, height, SMALL);
            button.draw("Home All", _axis_to_home == -1);
            y = button.y();  // LEDs start with the Home X button
            button.draw("Home X", _axis_to_home == 0);
            button.draw("Home Y", _axis_to_home == 1);
            button.draw("Home Z", _axis_to_home == 2);
            LED led(x - 16, y + height / 2, 10, button.gap());
            led.draw(myLimitSwitches[0]);
            led.draw(myLimitSwitches[1]);
            led.draw(myLimitSwitches[2]);
#endif

            if (state == Homing) {
                redLabel = "E-Stop";
            } else {
                if (state == Alarm && (strchr(myCtrlPins, 'D') == NULL)) {  // You can reset alarms if door is not active
                    redLabel = "Reset";
                }
                if (_axis_to_home == -1) {
                    for (int axis = 0; axis < n_axes; ++axis) {
                        if (can_home(axis)) {
                            if (!grnLabel.length()) {
                                grnLabel = "Home";
                            }

                            grnLabel += axisNumToChar(axis);
                        }
                    }
                } else {
                    grnLabel = "Home";
                    grnLabel += axisNumToChar(_axis_to_home);
                }
            }
        } else {
            centered_text("Invalid State", 105, WHITE, MEDIUM);
            centered_text("For Homing", 145, WHITE, MEDIUM);
            redLabel = "E-Stop";
            if (state == Cycle) {
                grnLabel = "Hold";
            } else if (state == Hold || state == DoorClosed) {
                grnLabel = "Resume";
            }
        }
        drawButtonLegends(redLabel, grnLabel.c_str(), "Back");

        refreshDisplay();
    }
};
HomingScene homingScene;
