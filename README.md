This keeb created by a group of people who loves keyball.

Special Thanks to: <br>
PCB: *[yangxing844](https://github.com/yangxing844)* <br>
Case: *[delock](https://github.com/delock)* <br>
Firmware: *[Amos698](https://github.com/Amos698)* <br>

<img src="keymap-drawer/keyball39.svg" >

## Keymap notes

### Base layer

- `MAIN`: The default QWERTY layer.
  - Includes separate positions for `Ctrl`, `Shift`, `Win`, and `Esc`.
    - This allows key combinations such as `Ctrl + Shift + Esc` and `Win + L`.
  - Provides `Left Alt + Grave` for switching between Japanese and English input.
  - Places `MINUS` on the rightmost key of the home row for typing a hyphen with a Japanese keyboard layout.

### Trackball layers

- `MOUSE`: Activates automatically when the PMW3610 trackball moves and remains active for 700 ms after the last movement.
  - Provides left, middle, and right mouse buttons on both halves.
  - Provides arrow keys, Page Up, Page Down, Home, and End on the right half.
  - Allows the right half to be used by itself as a trackball and navigation device.
- `SCROLL`: From `MOUSE`, hold the `F` position to use trackball movement for scrolling instead of pointer movement.
  - Vertical ball movement scrolls vertically, and horizontal ball movement scrolls horizontally.
- `SNIPE`: From `MOUSE`, hold the `G` position to reduce the trackball sensitivity for precise pointer movement.
  - Useful for selecting small targets and making fine cursor adjustments.

### Keyboard layers

The `Esc`/`SYM` hold-tap uses the `hold-preferred` behavior. Pressing another key while holding `Esc` activates `SYM` immediately, without waiting for the 240 ms tapping term to expire. This makes it possible to continue directly to `NUM` or `FN` as part of the same key sequence, without waiting for `SYM` to activate first.

- `SYM`: Hold `Esc` to access symbols, operators, and brackets.
- `NUM`: From `SYM`, hold the `Enter` position to activate matching number pads on both halves.
  - Each number pad contains `0`–`9`, arithmetic operators, a decimal point, and an equals sign.
- `FN`: From `SYM`, hold the `Backspace` position to access `F1`–`F12` on either half.
- `SYS`: From `FN`, hold the right `Shift` position to access Bluetooth profile selection and pairing-data removal.

Accessing `SYS` requires the `SYM` → `FN` → `SYS` sequence, which helps prevent accidental Bluetooth configuration changes.
