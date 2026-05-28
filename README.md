# qmk-keymap

My personal ergonomic split keyboard layouts.

After using my Erogdox's on the same config for almost a decade, not once using layers, hold-keys, combos, or anything fancy, I'm going to experiment with a 3x5 keyboard layout to maybe learn something new.

Built as a [QMK External Userspace](https://docs.qmk.fm/newbs_external_userspace) repo on top of [QMK firmware](https://qmk.fm).

## Layout

See [DESIGN.md](./DESIGN.md) for the layout spec, then the keymap.c per board:

- [`keyboards/ergodox_ez/keymaps/dinosaur/keymap.c`](./keyboards/ergodox_ez/keymaps/dinosaur/keymap.c)
- [`keyboards/cheapino/keymaps/dinosaur/keymap.c`](./keyboards/cheapino/keymaps/dinosaur/keymap.c)

## Keyboards

- [Ergodox EZ](https://www.zsa.io/ergodox/)
- [Cheapino v2](https://github.com/tompi/cheapino) — 36-key 3x5+3 split with RP2040-Zero. Not in mainline QMK; the keyboard definition is vendored here under `keyboards/cheapino/` and `make setup` symlinks it into `qmk_firmware/keyboards/cheapino/` so the QMK CLI can discover it.

## Setup

Install the [QMK CLI](https://docs.qmk.fm/cli):

```sh
curl -fsSL https://install.qmk.fm | sh
```

Then run setup:

```sh
make setup
```

## Build

```sh
make build
```

This runs `qmk userspace-compile`, which builds every target listed in `qmk.json`.

The compiled firmware will be a `.hex`.

You can also drive the underlying make target directly:

```sh
make ergodox_ez:dinosaur
make cheapino:dinosaur
```

## Flash

### Ergodox EZ

Press the reset button on the back of the right half, then:

```sh
make flash
```

GUI alternatives: [Wally](https://www.zsa.io/wally) or [QMK Toolbox](https://github.com/qmk/qmk_toolbox).

### Cheapino

Hold the boot button while tapping reset on the RP2040-Zero (the Cheapino mounts as a USB drive), then:

```sh
make flash-cheapino
```

## keyboard-helper integration

This repo doubles as a [keyboard-helper](https://github.com/ahdinosaur/keyboard-helper) keymap library. Point the keyboard-helper app at the root of this repo to load the rendered layers and live-track the active layer + key presses as you type.

Two pieces wire it up:

### Firmware side

The [`ahdinosaur/keyboard-helper`](https://github.com/ahdinosaur/keyboard-helper) repo is vendored as a git submodule at `modules/ahdinosaur/keyboard-helper/`. It's a Rust + QMK monorepo, so the actual QMK [community module](https://docs.qmk.fm/features/community_modules) sits at `modules/ahdinosaur/keyboard-helper/firmware/qmk/keyboard_helper/` — QMK's module dispatch matches by path, so the keymap references that full depth.

The keymap opts in via:

- `keyboards/ergodox_ez/keymaps/dinosaur/keymap.json` — lists `ahdinosaur/keyboard-helper/firmware/qmk/keyboard_helper` in the `modules` array.
- `keyboards/ergodox_ez/keymaps/dinosaur/config.h` — defines `KEYBOARD_HELPER_ID "ergodox-ez-dinosaur"` (matches the table key in `keymaps.toml`).
- `keyboards/ergodox_ez/keymaps/dinosaur/keymap.c` — overrides `keyboard_helper_position_from_keypos` with a hand-built table mapping the ergodox matrix to `LAYOUT_ergodox` argument order. The module's default mapping is row-major matrix order, which the ergodox's permuted LAYOUT macro doesn't match.

The module owns `process_record_keyboard_helper`, `layer_state_set_keyboard_helper`, `default_layer_state_set_keyboard_helper`, and `raw_hid_receive`; the keymap's own `process_record_user` / `layer_state_set_user` continue to fire independently (they sit in the QMK `_user` chain, not the module chain).

Cloning fresh:

```sh
git clone --recurse-submodules git@github.com:ahdinosaur/ergodox-layout.git
```

Or, after a regular clone:

```sh
git submodule update --init --recursive
```

### Host side

- `keymaps.toml` — manifest with one entry per board, keyed on the firmware-reported `KEYBOARD_HELPER_ID`.
- `ergodox-ez-dinosaur.yaml` / `cheapino-dinosaur.yaml` — [keymap-drawer](https://github.com/caksoylar/keymap-drawer) YAML for the six layers (BASE, NUM, NAV, MED, FUN, SYM); layer order and per-layer key order mirror the `LAYOUT_…(...)` argument order in the matching `keymap.c`. Labels are hand-written; if you change the keymap, edit this file too (or regenerate via `keymap-drawer parse`).

### Forking to another board

If you copy this keymap to a non-ergodox board:

1. Change `KEYBOARD_HELPER_ID` in `config.h` to match a new entry in `keymaps.toml`.
2. Rewrite `keyboard_helper_position_from_keypos` for the new board's `LAYOUT()` macro (or delete it if the matrix already walks in row-major order).
3. Add a new YAML for the new board's layout.

## CI

Every push and pull request validates the firmware builds.

Pushing a git tag runs the publish workflow to attach the `.hex` to a GitHub release named after the tag.

See [`.github/workflows/build.yml`](./.github/workflows/build.yml).

Cut a release with:

```sh
git tag v1.0
git push origin v1.0
```
