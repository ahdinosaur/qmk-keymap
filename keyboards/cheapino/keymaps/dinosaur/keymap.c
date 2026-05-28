#include QMK_KEYBOARD_H

// Layers. Higher numbers win when multiple are held; SYM sits on top so it
// can stack onto NUM/NAV/MED/FUN when both a primary/tertiary trigger and a
// secondary trigger are pressed at the same time.
enum layers {
    BASE,
    NUM,
    NAV,
    MED,
    FUN,
    SYM,
};

enum custom_keycodes {
    RIGHT_ARROW = SAFE_RANGE,
};

enum tap_dance_indices {
    TD_BOOT,
    TD_LC,
    TD_LO,
};

// Home-row mod-tap aliases (GACS).
#define HM_A    LGUI_T(KC_A)
#define HM_S    LALT_T(KC_S)
#define HM_D    LCTL_T(KC_D)
#define HM_F    LSFT_T(KC_F)
#define HM_J    RSFT_T(KC_J)
#define HM_K    RCTL_T(KC_K)
#define HM_L    RALT_T(KC_L)
#define HM_SCLN RGUI_T(KC_SCLN)

// Layer-tap thumb aliases. Layer is determined by the thumb POSITION:
// primary → NUM/NAV, secondary → SYM (bilateral), tertiary → MED/FUN.
#define LT_ESC LT(MED, KC_ESC)
#define LT_DEL LT(NUM, KC_DEL)
#define LT_BSP LT(SYM, KC_BSPC)
#define LT_SPC LT(SYM, KC_SPC)
#define LT_ENT LT(NAV, KC_ENT)
#define LT_TAB LT(FUN, KC_TAB)

// LAYOUT_split_3x5_3 argument order (per cheapino's keyboard.json):
//   30 alphas: row-by-row, each row L pinky→inner then R inner→pinky.
//   6 thumbs:  L inside (secondary), L middle (primary), L outside (tertiary),
//              R outside (tertiary), R middle (primary), R inside (secondary).
// Role-to-position mirrors the Ergodox EZ (see DESIGN.md §Thumbs): SYM on
// the inside thumb, NUM/NAV on the middle, MED/FUN on the outside.

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// BASE — Qwerty with home-row mods on the home row and layer-tap thumbs.
[BASE] = LAYOUT_split_3x5_3(
    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,
    HM_A,    HM_S,    HM_D,    HM_F,    KC_G,        KC_H,    HM_J,    HM_K,    HM_L,    HM_SCLN,
    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,        KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,
                      LT_BSP,  LT_DEL,  LT_ESC,      LT_TAB,  LT_ENT,  LT_SPC
),

// NUM — Number layer (right hand active; trigger LT_DEL on left primary thumb).
// Left hand (trigger-side): Boot + GACS mods + Lc/Lo.
// Right hand (active): numpad, with `. 0 =` continuing on the thumbs.
[NUM] = LAYOUT_split_3x5_3(
    TD(TD_BOOT), KC_NO, KC_NO,     KC_NO,      KC_NO,       KC_SLSH, KC_7,    KC_8,    KC_9,    KC_MINS,
    KC_LGUI,     KC_LALT, KC_LCTL, KC_LSFT,    KC_NO,       KC_ASTR, KC_4,    KC_5,    KC_6,    KC_PLUS,
    KC_NO,       KC_NO,   TD(TD_LO), TD(TD_LC), KC_NO,      KC_PERC, KC_1,    KC_2,    KC_3,    KC_CIRC,
                                  KC_NO,   KC_TRNS, KC_NO,    KC_EQL,  KC_0,    KC_DOT
),

// NAV — Navigation layer (left hand active; trigger LT_ENT on right primary thumb).
// Left hand (active): clipboard row, arrows + Caps, line/page nav + Ins.
// Right hand (trigger-side): Boot + GACS mods (mirrored) + Lc/Lo.
[NAV] = LAYOUT_split_3x5_3(
    C(KC_V), C(KC_C), C(KC_X), C(KC_Z), C(S(KC_Z)),     KC_NO,   KC_NO,   KC_NO,   KC_NO,   TD(TD_BOOT),
    KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_CAPS,        KC_NO,   KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI,
    KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_INS,         KC_NO,   TD(TD_LC), TD(TD_LO), KC_NO, KC_NO,
                      KC_TRNS, KC_TRNS, KC_TRNS,        KC_NO,   KC_TRNS, KC_NO
),

// MED — Media layer (right hand active; trigger LT_ESC on left tertiary thumb).
// Left hand (trigger-side): Boot + GACS mods + Lc/Lo.
// Right hand (active): media transport on home and bottom rows.
[MED] = LAYOUT_split_3x5_3(
    TD(TD_BOOT), KC_NO,   KC_NO,   KC_NO,   KC_NO,       KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,
    KC_LGUI,     KC_LALT, KC_LCTL, KC_LSFT, KC_NO,       KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, KC_NO,
    KC_NO,       KC_NO,   TD(TD_LO), TD(TD_LC), KC_NO,   KC_MPLY, KC_MSTP, KC_MUTE, KC_NO,   KC_NO,
                                  KC_NO,   KC_NO,   KC_TRNS,  KC_TRNS, KC_TRNS, KC_TRNS
),

// FUN — Function layer (left hand active; trigger LT_TAB on right tertiary thumb).
// Left hand (active): F-keys grouped 1-9 with system keys on inner column.
// Right hand (trigger-side): Boot + GACS mods (mirrored) + Lc/Lo.
[FUN] = LAYOUT_split_3x5_3(
    KC_F12, KC_F7,   KC_F8,   KC_F9,   KC_PSCR,         KC_NO,   KC_NO,   KC_NO,   KC_NO,   TD(TD_BOOT),
    KC_F11, KC_F4,   KC_F5,   KC_F6,   KC_SCRL,         KC_NO,   KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI,
    KC_F10, KC_F1,   KC_F2,   KC_F3,   KC_PAUS,         KC_NO,   TD(TD_LC), TD(TD_LO), KC_NO, KC_NO,
                      KC_TRNS, KC_TRNS, KC_TRNS,        KC_TRNS, KC_NO,   KC_NO
),

// SYM — Symbol layer (bilateral; triggers LT_BSP on left secondary OR LT_SPC on right secondary).
// No trigger-side "extras" (Boot/Lc/Lo) since both hands are trigger-adjacent.
//
// `:` uses S(KC_P) (not KC_COLN = S(KC_SCLN)): the firmware sends QWERTY
// scancodes, but the OS is Colemak/DH, which maps QWERTY's `;` position to
// `o` — so S(KC_SCLN) would print capital O. QWERTY's P position maps to
// `;` in Colemak/DH, so S(KC_P) yields `:`. Switch back to KC_COLN if the
// OS keyboard layout is set to QWERTY.
[SYM] = LAYOUT_split_3x5_3(
    KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,        KC_CIRC, KC_AMPR, KC_LBRC, KC_RBRC, KC_PIPE,
    KC_ASTR, KC_UNDS, KC_MINS, KC_EQL,  KC_DQT,         S(KC_P), KC_LPRN, KC_RPRN, KC_LCBR, KC_RCBR,
    KC_TILD, KC_SLSH, KC_PLUS, KC_QUOT, KC_GRV,         KC_BSLS, RIGHT_ARROW, KC_LT, KC_GT, KC_QUES,
                      KC_TRNS, KC_NO,   KC_NO,          KC_NO,   KC_NO,   KC_TRNS
),

};

// chordal_hold_layout: 'L' = left hand, 'R' = right hand, '*' = exempt from
// the opposite-hands rule. The 6 layer-tap thumbs are '*' so the trigger-side
// Boot/Lc/Lo extras (on the SAME hand as the held thumb) can chord with the
// thumb. All other positions are tagged by hand.
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT_split_3x5_3(
        'L','L','L','L','L',   'R','R','R','R','R',
        'L','L','L','L','L',   'R','R','R','R','R',
        'L','L','L','L','L',   'R','R','R','R','R',
                '*','*','*',   '*','*','*'
    );

// Flow Tap: limit to alpha/punctuation typing keys. Omitting KC_SPC (and
// implicitly all other layer-tap thumb tap-keycodes — KC_BSPC, KC_DEL,
// KC_ENT, KC_TAB, KC_ESC) lets the thumbs activate their layers without
// Flow Tap forcing them to their tap action during fast typing.
bool is_flow_tap_key(uint16_t keycode) {
    switch (get_tap_keycode(keycode)) {
        case KC_A ... KC_Z:
        case KC_DOT:
        case KC_COMM:
        case KC_SCLN:
        case KC_SLSH:
            return true;
    }
    return false;
}

// Tap dance: all three keys do nothing on a single tap and fire on the
// second tap. This prevents accidental triggering of bootloader / layer-lock
// while typing on the trigger-side hand of a held layer.
static void td_boot_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count >= 2) reset_keyboard();
}

static void td_lc_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count >= 2) {
        layer_lock_invert(get_highest_layer(layer_state));
    }
}

static void td_lo_finished(tap_dance_state_t *state, void *user_data) {
    if (state->count < 2) return;
    switch (get_highest_layer(layer_state)) {
        case NUM: layer_lock_invert(NAV); break;
        case NAV: layer_lock_invert(NUM); break;
        case MED: layer_lock_invert(FUN); break;
        case FUN: layer_lock_invert(MED); break;
        // BASE and SYM intentionally do nothing — Lc/Lo aren't reachable from those layers.
    }
}

tap_dance_action_t tap_dance_actions[] = {
    [TD_BOOT] = ACTION_TAP_DANCE_FN(td_boot_finished),
    [TD_LC]   = ACTION_TAP_DANCE_FN(td_lc_finished),
    [TD_LO]   = ACTION_TAP_DANCE_FN(td_lo_finished),
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case RIGHT_ARROW:
            if (record->event.pressed) {
                SEND_STRING("->");
            }
            return false;
    }
    return true;
}

// Override the ahdinosaur/keyboard_helper community module's default
// `row * MATRIX_COLS + col` mapping. The cheapino's `LAYOUT_split_3x5_3`
// macro fills only a subset of its 8×12 duplex matrix (the cheapino
// uses col 5 on rows 0-2 for the right thumbs and col 11 on rows 4-6
// for the left thumbs; many other matrix slots are wired-but-unused).
// The host-side visualizer keys positions off LAYOUT-arg index (= the
// flat key order in cheapino-dinosaur.yaml), so without this override
// every press would highlight the wrong cell.
//
// The map is derived from
// `keyboards/cheapino/keyboard.json` → `layouts.LAYOUT_split_3x5_3.layout`:
// each entry there is one LAYOUT argument, and its `matrix: [row, col]`
// field gives the matrix position that argument fills. Entries written
// `KH_NO_POS` are matrix slots with no physical key.
#define KH_NO_POS 0xFFFFu

// Pin the table to the matrix shape it was hand-built for.
_Static_assert(MATRIX_ROWS == 8 && MATRIX_COLS == 12,
               "kh_layout_arg_index is hand-derived for cheapino 8x12; "
               "regenerate from keyboard.json if matrix dims change.");

static const uint16_t kh_layout_arg_index[MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
    // Right hand: cols 0..4 are the alphas (inner-idx → pinky), col 5 is the right thumb.
    /* 0 */ {  5,  6,  7,  8,  9, 33, KH_NO_POS, KH_NO_POS, KH_NO_POS, KH_NO_POS, KH_NO_POS, KH_NO_POS },
    /* 1 */ { 15, 16, 17, 18, 19, 34, KH_NO_POS, KH_NO_POS, KH_NO_POS, KH_NO_POS, KH_NO_POS, KH_NO_POS },
    /* 2 */ { 25, 26, 27, 28, 29, 35, KH_NO_POS, KH_NO_POS, KH_NO_POS, KH_NO_POS, KH_NO_POS, KH_NO_POS },
    // Row 3: encoder row (zeroed by `fix_encoder_action` before per-key dispatch).
    /* 3 */ { KH_NO_POS, KH_NO_POS, KH_NO_POS, KH_NO_POS, KH_NO_POS, KH_NO_POS, KH_NO_POS, KH_NO_POS, KH_NO_POS, KH_NO_POS, KH_NO_POS, KH_NO_POS },
    // Left hand: cols 6..10 are the alphas (inner-idx → pinky, but reversed by LAYOUT order),
    // col 11 is the left thumb. Matrix col index runs opposite of the visual layout.
    /* 4 */ { KH_NO_POS, KH_NO_POS, KH_NO_POS, KH_NO_POS, KH_NO_POS, KH_NO_POS,  4,  3,  2,  1,  0, 32 },
    /* 5 */ { KH_NO_POS, KH_NO_POS, KH_NO_POS, KH_NO_POS, KH_NO_POS, KH_NO_POS, 14, 13, 12, 11, 10, 31 },
    /* 6 */ { KH_NO_POS, KH_NO_POS, KH_NO_POS, KH_NO_POS, KH_NO_POS, KH_NO_POS, 24, 23, 22, 21, 20, 30 },
    /* 7 */ { KH_NO_POS, KH_NO_POS, KH_NO_POS, KH_NO_POS, KH_NO_POS, KH_NO_POS, KH_NO_POS, KH_NO_POS, KH_NO_POS, KH_NO_POS, KH_NO_POS, KH_NO_POS },
};

uint16_t keyboard_helper_position_from_keypos(keypos_t key) {
    if (key.row >= MATRIX_ROWS || key.col >= MATRIX_COLS) {
        return KH_NO_POS;
    }
    return pgm_read_word(&kh_layout_arg_index[key.row][key.col]);
}
