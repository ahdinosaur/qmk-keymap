# Layout design

A 36-key (3×5 + 3 thumbs per hand) ergonomic split keyboard layout design, designed for both the Ergodox EZ and the Cheapino.

## Conventions

- Layouts are shown as 3 rows × 5 columns per hand, plus 3 thumb keys per hand.
- Each hand reads pinky → inner-index from outer column to inner column.
- `NO` means the key does nothing (`KC_NO`).
  - Every active key is explicit; unspecified positions default to `NO`, not transparent.
- `--` marks the layer's trigger key (held while the layer is active).
- Modifier abbreviations: `Sup` (Super/GUI), `Alt`, `Ctl`, `Sft` (Shift).
- Where a non-base layer shows `Sup` / `Alt` / `Ctl` / `Sft` on the home row, these are **plain modifiers**, not mod-taps. Mod-taps only exist on the base layer.

## Home row mods

GACS order, mirrored across hands:

```
Left:   A = Sup   S = Alt   D = Ctl   F = Sft
Right:  J = Sft   K = Ctl   L = Alt   ; = Sup
```

Settings:

- [`TAPPING_TERM`](https://docs.qmk.fm/tap_hold#tapping-term): `250`
- [`PERMISSIVE_HOLD`](https://docs.qmk.fm/tap_hold#permissive-hold)
- [`FLOW_TAP_TERM`](https://docs.qmk.fm/tap_hold#flow-tap): `150`
- [`CHORDAL_HOLD`](https://docs.qmk.fm/tap_hold#chordal-hold)
- [`SPECULATIVE_HOLD`](https://docs.qmk.fm/tap_hold#speculative-hold)

Thumb layer-taps are marked `'*'` in `chordal_hold_layout` (exempt from the opposite-hand rule), so the trigger-side extras (Boot/Lc/Lo) chord with the held trigger thumb. This is ZSA Oryx's default behavior as of June 2025.

## Thumbs

```
Left thumbs:    Esc    Del    Bsp
                (tertiary, primary, secondary)

Right thumbs:   Spc    Ent    Tab
                (secondary, primary, tertiary)
```

Each thumb is a layer-tap (`LT(layer, kc)`). Layer is determined by the
**position**, not the keycap — so the primary thumbs always trigger
Number/Nav, the secondary thumbs always trigger Symbol (bilateral), and the
tertiary thumbs always trigger Media/Fun.

```
Left tertiary  (Esc) → Media     Right secondary (Spc) → Symbol
Left primary   (Del) → Number    Right primary   (Ent) → Nav
Left secondary (Bsp) → Symbol    Right tertiary  (Tab) → Fun
```

### Primary / secondary / tertiary

`primary`, `secondary`, and `tertiary` rank the three thumb keys by ergonomic accessibility, not by physical position. `primary` is the most natural reach (Del / Ent), `tertiary` is the most awkward (Esc / Tab). Which physical key takes each role depends on the board.

Below, **inside** means "toward the hand" and **outside** means "toward the other half of the keyboard".

**Ergodox EZ:**

- `primary` → the big thumb key in the middle.
- `secondary` → the other big thumb key, on the inside (toward the hand).
- `tertiary` → the bottom small thumb key on the outside (toward the other side).

**Cheapino** (and other 3-thumb-row boards in the Miryoku family — Corne, etc.):

- `primary` → middle thumb.
- `secondary` → outside thumb (toward the other side).
- `tertiary` → inside thumb (toward the hand).

Note that `secondary` and `tertiary` end up on opposite sides between the two boards. This isn't a contradiction: the labels rank ergonomic preference, and the Ergodox's `secondary` is a big key (more comfortable than any small key) so it stays second-best even on the inside; on a 3-key thumb row all keys are the same size, so accessibility comes down to reach distance and the outside (center-ward) reach wins.

## Additional features

While any single-hand layer is held, the **trigger-side hand** gets these extras (inspired by Miryoku's "Additional Features"):

- Top row pinky:    `Boot` — activate the bootloader.
- Bottom row index: `Lc`   — lock the current layer.
- Bottom row middle: `Lo`  — lock the opposite-hand layer.

All require **double-tap** to activate (QMK tap-dance), to prevent accidental triggering.

These do **not** apply to the Symbol layer (bilateral, no trigger-side hand).

## Layers

### Base (Qwerty)

```
  Q      W      E      R      T          Y      U      I      O      P
  A      S      D      F      G          H      J      K      L      ;
  Z      X      C      V      B          N      M      ,      .      /

                Esc    Del    Bsp        Spc    Ent    Tab
```

Home-row alphas are mod-taps. Thumbs are layer-taps. See sections above for assignments.

### Number layer

Hold left primary (Del). Active: right hand.

```
  Boot   NO     NO     NO     NO         /      7      8      9      -
  Sup    Alt    Ctl    Sft    NO         *      4      5      6      +
  NO     NO     Lo     Lc     NO         %      1      2      3      ^

                NO     --     NO         .      0      =
```

- Right hand: numpad style, inspired by the Moonlander symbol layer and getreuer's number layer.
- Right thumbs continue the numpad (`. 0 =`).
- `Lo` = lock Nav (opposite of Number).

### Navigation layer

Hold right primary (Ent). Active: left hand.

```
  Paste  Copy   Cut    Undo   Redo       NO     NO     NO     NO     Boot
  Left   Down   Up     Right  Caps       NO     Sft    Ctl    Alt    Sup
  Home   PgDn   PgUp   End    Ins        NO     Lc     Lo     NO     NO

                Esc    Del    Bsp        NO     --     NO
```

- Inspired by Miryoku.
- `Caps` = Caps Lock (`KC_CAPS`).
- Left thumbs stay as base (Esc/Del/Bsp), so they remain available (auto-repeat, normal use) while Nav is held.
- `Lo` = lock Number (opposite of Nav).

### Symbol layer

Hold left secondary (Bsp) **or** right secondary (Spc). Active: both hands.

On the Ergodox EZ, the inner-column upper-alpha key on either hand is an
additional `MO(SYM)` trigger (alongside the secondary thumbs).

```
  !      @      #      $      %          ^      &      [      ]      |
  *      _      -      =      "          :      (      )      {      }
  ~      /      +      '      `          \      →      <      >      ?

                NO     NO     --         --     NO     NO
```

- Both secondary thumbs trigger Symbol (`--`); other thumbs are `NO` since both hands' thumbs are trigger-adjacent.
- No additional features (no clear trigger-side hand).
- No home-row mods (positions taken by symbols).
- Brackets pair on adjacent positions: `[]` `{}` `()`.
- Shifted-number positions preserved: `! @ # $ % ^ &` in their natural spots.
- `< > ?` kept where they are as shifted `, . /` on Qwerty.
- `~ /` adjacent (left bottom) for shell paths.
- `( )` adjacent on right index/middle for autocomplete-friendly typing.
- `→` (right hand, bottom row index) is a TBD placeholder slot.

### Fun layer

Hold right tertiary (Tab). Active: left hand.

```
  F12    F7     F8     F9     PrSc       NO     NO     NO     NO     Boot
  F11    F4     F5     F6     ScLk       NO     Sft    Ctl    Alt    Sup
  F10    F1     F2     F3     Paus       NO     Lc     Lo     NO     NO

                Esc    Del    Bsp        NO     NO     --
```

- Left thumbs stay as base (Esc/Del/Bsp), so they remain available (auto-repeat, normal use) while Fun is held.
- `Lo` = lock Media (opposite of Fun).

### Media layer

Hold left tertiary (Esc). Active: right hand.

```
  Boot   NO     NO     NO     NO         NO     NO     NO     NO     NO
  Sup    Alt    Ctl    Sft    NO         Prev   VolDn  VolUp  Next   NO
  NO     NO     Lo     Lc     NO         Play   Stop   Mute   NO     NO

                --     NO     NO         Spc    Ent    Tab
```

- Right thumbs stay as base (Spc/Ent/Tab), so they remain available (auto-repeat, normal use) while Media is held.
- Top row right hand intentionally empty for now.
- `Lo` = lock Fun (opposite of Media).

## Inspiration

- [manna-harbour/miryoku](https://github.com/manna-harbour/miryoku)
- getreuer
  - [Designing a symbol layer](https://getreuer.info/posts/keyboards/symbol-layer/index.html)
  - [getreuer/qmk-keymap](https://github.com/getreuer/qmk-keymap)
- precondition
  - [A guide to home row mods](https://precondition.github.io/home-row-mods)
  - [precondition/dactyl-manuform-keymap](https://github.com/precondition/dactyl-manuform-keymap)
- [urob's ZMK "timeless" home row mods, ported to native QMK (reddit)](https://www.reddit.com/r/ErgoMechKeyboards/comments/1q1jo3c/urobs_zmk_timeless_home_row_mods_ported_to_native/)
- [urob/zmk-config](https://github.com/urob/zmk-config)
- [Seniply](https://stevep99.github.io/seniply/)
- [Ben Vallack — 36-key Corne layout](https://benvallack.com/notebook/36-key-corne-keyboard-layout/)
- [Wellum — for 36 keys (en)](https://github.com/braindefender/wellum/blob/master/for-36-keys_en.md)
- [mforman/zmk-config](https://github.com/mforman/zmk-config)
- [keymap-drawer (Streamlit)](https://keymap-drawer.streamlit.app/)
- [markstos — Corne 3×5+1 layout](https://mark.stosberg.com/markstos-corne-3x5-1-keyboard-layout/)
- [keymap-drawer 3x5 example](https://keymap-drawer.streamlit.app/?example_yaml=3x5.yaml)
- [sunaku — bilateral combinations / home row mods](https://sunaku.github.io/home-row-mods.html)

## Maybe?

Ideas to consider after the base design has been used for a while:

- **Two-layers-held "adjust" layer** — e.g., simultaneous Number + Nav unlocks a tri-state layer for system bits (EE_CLR, RGB controls, etc.).
- **Mouse layer** — cursor, scroll, buttons. Possibly urob's "smart mouse" pattern (auto-activates from Nav, auto-deactivates on non-mouse input).
- **Caps Word** — auto-shift the next word, releases on space/punctuation. Great for `SCREAMING_SNAKE_CASE`.
- **Repeat Key / Magic Key** — re-fires the previous key; useful for repeated symbols (`==`, `..`, `->`) and to relieve pinky strain.
- **Autocorrect** — Getreuer's typo-fixing module (now in QMK core).
- **Numword** — sticky Number layer that auto-exits on non-numeric input.
- **Combos** — multi-key chords; possible alternative trigger for the Nav layer (right + left primary thumbs).
- **Swapper** — tri-state alt-tab window switching.
- **Move home-row mods to bottom row** — less mistrigger risk, but bottom row is more awkward to reach.
