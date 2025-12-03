# FluidDial Development Notes

## Project Overview

FluidDial is a pendant firmware for CNC machines running FluidNC. It provides a touch-screen interface with encoder/jog wheel support for machine control.

## Current State

- Hardware: Supports CYD (Cheap Yellow Display) and PiBot Pendant V4
- Communication: UART at 1000000 baud (RJ12) or 115200 (Bluetooth)
- Primary contributor: Mitch Bradley (original author), Barton Dring

---

## A-Axis Support Implementation

### Branch: `feature/a-axis-support`

### Status: ✅ COMPLETE - Ready for Testing

### Changes Made

#### 1. FluidNCModel.h

- Added `#define MAX_AXES 6` constant for consistency
- Updated `myAxes[]` and `myLimitSwitches[]` to use `MAX_AXES`

#### 2. FluidNCModel.cpp

- Updated array declarations to use `MAX_AXES`

#### 3. MultiJogScene.cpp

- Changed `const int num_axes = 3` to dynamic `int num_axes() { return n_axes; }`
- Expanded `_dist_index[6]` array for all possible axes
- Added dynamic DRO sizing based on axis count:
  - 3 axes: 32px rows starting at y=68
  - 4 axes: 28px rows starting at y=64
  - 5-6 axes: 24px rows starting at y=58
- Updated `which()` function for dynamic touch detection
- All axis iteration loops now use `num_axes()` instead of hardcoded 3

#### 4. StatusScene.cpp

- Replaced hardcoded `dro.draw(0/1/2)` with dynamic loop
- Added same DRO height/position calculations

#### 5. HomingScene.cpp

- Replaced `#define HOMING_N_AXIS 3` with `MAX_AXES`
- Added A/B/C axis homing config paths
- Updated `detect_homing_info()` to iterate over `n_axes`
- Added bounds checking in `can_home()` for axes beyond n_axes
- Updated `have_homing_info()` to use dynamic axis count

#### 6. ProbingScene.cpp

- Updated axis selection to allow 0 to `n_axes-1`
- Added dynamic DRO sizing for probe display

### Build Verification

- ✅ `pibot` environment: SUCCESS
- ✅ `cyddial` environment: SUCCESS

### How It Works

The `n_axes` variable in FluidNCModel is automatically set by FluidNC's status reports. When FluidNC reports 4 axes (XYZA), `n_axes` becomes 4, and all UI scenes dynamically adjust:

- DRO rows shrink to fit more axes
- Touch targets recalculate
- Homing, jogging, and probing all work with the correct axis count

### Testing Checklist

- [x] Build and upload successful (2024-12-02)
- [x] Initial functional test PASSED
- [ ] Test with 3-axis machine (regression)
- [ ] Verify jogging on A-axis
- [ ] Verify homing on A-axis (if configured)
- [ ] Verify probing axis selection includes A
- [ ] Check touch targets are correct with 4 axes
- [ ] Test with 5+ axes if available

---

## Known Issues / Bugs

- (none documented yet)

## Future Feature Ideas

- [x] A-axis (rotary table) support ← IN PROGRESS
- [ ] Degrees vs mm display for rotary axes
- [ ] Different jog rate defaults for rotary
- [ ] Touchscreen calibration utility
- [ ] Macro editor on device

## Development Environment

- PlatformIO with VS Code
- ESP32 target boards
- Claude Code integration for version control

---

*Last updated: A-axis support implementation complete, awaiting testing*
