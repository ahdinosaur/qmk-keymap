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

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

// BASE — Qwerty with home-row mods on the home row and layer-tap thumbs.
// Inner-column upper-alpha key is a bilateral MO(SYM), in addition to the
// secondary-thumb LT_BSP/LT_SPC SYM triggers.
[BASE] = LAYOUT_ergodox(
    // ---- LEFT HAND ----
    // Row 0 (top — extras above the alpha grid)
    KC_EQL,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_NO,
    // Row 1 (alphas Q W E R T at args 1..5; inner-column = MO(SYM))
    KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    MO(SYM),
    // Row 2 (alphas A S D F G at args 1..5; home-row mods on A S D F)
    KC_ESC,  HM_A,    HM_S,    HM_D,    HM_F,    KC_G,
    // Row 3 (alphas Z X C V B at args 1..5)
    KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_LGUI,
    // Row 4 (extras below alphas)
    KC_GRV,  KC_LCTL, KC_LALT, KC_LEFT, KC_RGHT,
    // Left thumb cluster, args 0..5. See DESIGN.md §Thumbs for the role-to-key
    // mapping on the Ergodox EZ. The two big thumb keys are at args 3 and 4.
    //   0 = extra (Home)
    //   1 = extra (End)
    //   2 = extra (empty)
    //   3 = secondary (LT_BSP → SYM)
    //   4 = primary   (LT_DEL → NUM)
    //   5 = tertiary  (LT_ESC → MED)
                                                 KC_HOME, KC_END,
                                                          KC_NO,
                                        LT_BSP,  LT_DEL,  LT_ESC,

    // ---- RIGHT HAND ----
    // Row 0 (top — extras)
    KC_NO,   KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS,
    // Row 1 (alphas Y U I O P at args 1..5; inner-column = MO(SYM))
    MO(SYM), KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_BSLS,
    // Row 2 (alphas H J K L ; at args 0..4 — note: row 2 has only 6 args; outer-pinky extra is arg 5)
             KC_H,    HM_J,    HM_K,    HM_L,    HM_SCLN, KC_QUOT,
    // Row 3 (alphas N M , . / at args 1..5)
    KC_RGUI, KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_RSFT,
    // Row 4 (extras)
                      KC_UP,   KC_DOWN, KC_LBRC, KC_RBRC, KC_NO,
    // Right thumb cluster, args 0..5. See DESIGN.md §Thumbs for the role-to-key
    // mapping on the Ergodox EZ. The two big thumb keys are at args 4 and 5.
    //   0 = extra (PgUp)
    //   1 = extra (PgDn)
    //   2 = extra (empty)
    //   3 = tertiary  (LT_TAB → FUN)
    //   4 = primary   (LT_ENT → NAV)
    //   5 = secondary (LT_SPC → SYM)
    KC_PGUP, KC_PGDN,
    KC_NO,
    LT_TAB,  LT_ENT,  LT_SPC
),

// NUM — Number layer (right hand active; trigger LT_DEL on left primary thumb).
[NUM] = LAYOUT_ergodox(
    // ---- LEFT HAND (trigger-side) ----
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, TD(TD_BOOT), KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,
    KC_TRNS, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO,
    KC_TRNS, KC_NO,   KC_NO,   TD(TD_LO), TD(TD_LC), KC_NO,  KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    // Left thumb: extras TRNS; trigger LT_DEL (primary, arg 4) TRNS; other LT thumbs NO
                                                 KC_TRNS, KC_TRNS,
                                                          KC_TRNS,
                                        KC_NO,   KC_TRNS, KC_NO,

    // ---- RIGHT HAND (active — numpad) ----
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_SLSH, KC_7,    KC_8,    KC_9,    KC_MINS, KC_TRNS,
             KC_ASTR, KC_4,    KC_5,    KC_6,    KC_PLUS, KC_TRNS,
    KC_TRNS, KC_PERC, KC_1,    KC_2,    KC_3,    KC_CIRC, KC_TRNS,
                      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    // Right thumb: extras TRNS; numpad continuation `. 0 =` on secondary (arg 5) / primary (arg 4) / tertiary (arg 3).
    KC_TRNS, KC_TRNS,
    KC_TRNS,
    KC_EQL,  KC_0,    KC_DOT
),

// NAV — Navigation layer (left hand active; trigger LT_ENT on right primary thumb).
[NAV] = LAYOUT_ergodox(
    // ---- LEFT HAND (active) ----
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, C(KC_V), C(KC_C), C(KC_X), C(KC_Z), C(S(KC_Z)), KC_TRNS,
    KC_TRNS, KC_LEFT, KC_DOWN, KC_UP,   KC_RGHT, KC_CAPS,
    KC_TRNS, KC_HOME, KC_PGDN, KC_PGUP, KC_END,  KC_INS,  KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    // Left thumb (active-side, "stay as base"): all TRNS
                                                 KC_TRNS, KC_TRNS,
                                                          KC_TRNS,
                                        KC_TRNS, KC_TRNS, KC_TRNS,

    // ---- RIGHT HAND (trigger-side) ----
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   TD(TD_BOOT), KC_TRNS,
             KC_NO,   KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, KC_TRNS,
    KC_TRNS, KC_NO,   TD(TD_LC), TD(TD_LO), KC_NO, KC_NO, KC_TRNS,
                      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    // Right thumb: extras TRNS; trigger LT_ENT (primary, arg 4) TRNS; other LT thumbs NO
    KC_TRNS, KC_TRNS,
    KC_TRNS,
    KC_NO,   KC_TRNS, KC_NO
),

// MED — Media layer (right hand active; trigger LT_ESC on left tertiary thumb).
[MED] = LAYOUT_ergodox(
    // ---- LEFT HAND (trigger-side) ----
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, TD(TD_BOOT), KC_NO, KC_NO, KC_NO, KC_NO, KC_TRNS,
    KC_TRNS, KC_LGUI, KC_LALT, KC_LCTL, KC_LSFT, KC_NO,
    KC_TRNS, KC_NO,   KC_NO,   TD(TD_LO), TD(TD_LC), KC_NO, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    // Left thumb: extras TRNS; trigger LT_ESC (tertiary, arg 5) TRNS; other LT thumbs NO
                                                 KC_TRNS, KC_TRNS,
                                                          KC_TRNS,
                                        KC_NO,   KC_NO,   KC_TRNS,

    // ---- RIGHT HAND (active) ----
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_TRNS,
             KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, KC_NO,   KC_TRNS,
    KC_TRNS, KC_MPLY, KC_MSTP, KC_MUTE, KC_NO,   KC_NO,   KC_TRNS,
                      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    // Right thumb (active-side, "stay as base"): all TRNS
    KC_TRNS, KC_TRNS,
    KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS
),

// FUN — Function layer (left hand active; trigger LT_TAB on right tertiary thumb).
[FUN] = LAYOUT_ergodox(
    // ---- LEFT HAND (active — F-keys) ----
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_F12,  KC_F7,   KC_F8,   KC_F9,   KC_PSCR, KC_TRNS,
    KC_TRNS, KC_F11,  KC_F4,   KC_F5,   KC_F6,   KC_SCRL,
    KC_TRNS, KC_F10,  KC_F1,   KC_F2,   KC_F3,   KC_PAUS, KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    // Left thumb (active-side, "stay as base"): all TRNS
                                                 KC_TRNS, KC_TRNS,
                                                          KC_TRNS,
                                        KC_TRNS, KC_TRNS, KC_TRNS,

    // ---- RIGHT HAND (trigger-side) ----
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   TD(TD_BOOT), KC_TRNS,
             KC_NO,   KC_RSFT, KC_RCTL, KC_RALT, KC_RGUI, KC_TRNS,
    KC_TRNS, KC_NO,   TD(TD_LC), TD(TD_LO), KC_NO, KC_NO, KC_TRNS,
                      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    // Right thumb: extras TRNS; trigger LT_TAB (tertiary, arg 3) TRNS; other LT thumbs NO
    KC_TRNS, KC_TRNS,
    KC_TRNS,
    KC_TRNS, KC_NO,   KC_NO
),

// SYM — Symbol layer (bilateral; triggers LT_BSP on left secondary OR LT_SPC on right secondary;
// also MO(SYM) on inner-column upper-alpha row of either hand).
//
// `:` uses S(KC_P) (not KC_COLN = S(KC_SCLN)): the firmware sends QWERTY
// scancodes, but the OS is Colemak/DH, which maps QWERTY's `;` position to
// `o` — so S(KC_SCLN) would print capital O. QWERTY's P position maps to
// `;` in Colemak/DH, so S(KC_P) yields `:`. Switch back to KC_COLN if the
// OS keyboard layout is set to QWERTY.
[SYM] = LAYOUT_ergodox(
    // ---- LEFT HAND ----
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC, KC_TRNS,
    KC_TRNS, KC_ASTR, KC_UNDS, KC_MINS, KC_EQL,  KC_DQT,
    KC_TRNS, KC_TILD, KC_SLSH, KC_PLUS, KC_QUOT, KC_GRV,  KC_TRNS,
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    // Left thumb: extras TRNS; trigger LT_BSP (secondary, arg 3) TRNS; other LT thumbs NO
                                                 KC_TRNS, KC_TRNS,
                                                          KC_TRNS,
                                        KC_TRNS, KC_NO,   KC_NO,

    // ---- RIGHT HAND ----
    KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    KC_TRNS, KC_CIRC, KC_AMPR, KC_LBRC, KC_RBRC, KC_PIPE, KC_TRNS,
             S(KC_P), KC_LPRN, KC_RPRN, KC_LCBR, KC_RCBR, KC_TRNS,
    KC_TRNS, KC_BSLS, RIGHT_ARROW, KC_LT, KC_GT, KC_QUES, KC_TRNS,
                      KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
    // Right thumb: extras TRNS; trigger LT_SPC (secondary, arg 5) TRNS; other LT thumbs NO
    KC_TRNS, KC_TRNS,
    KC_TRNS,
    KC_NO,   KC_NO,   KC_TRNS
),

};

// chordal_hold_layout: 'L' = left hand, 'R' = right hand, '*' = exempt from
// the opposite-hands rule. The 6 layer-tap thumbs are '*' so the trigger-side
// Boot/Lc/Lo extras (on the SAME hand as the held thumb) can chord with the
// thumb. All other positions are tagged by hand.
const char chordal_hold_layout[MATRIX_ROWS][MATRIX_COLS] PROGMEM =
    LAYOUT_ergodox(
        // ---- LEFT HAND ----
        'L','L','L','L','L','L','L',
        'L','L','L','L','L','L','L',
        'L','L','L','L','L','L',
        'L','L','L','L','L','L','L',
        'L','L','L','L','L',
        // Left thumb: LT thumbs '*' (args 3, 4, 5); extras 'L' (args 0, 1, 2)
                                  'L','L',
                                       'L',
                              '*','*','*',

        // ---- RIGHT HAND ----
        'R','R','R','R','R','R','R',
        'R','R','R','R','R','R','R',
        'R','R','R','R','R','R',
        'R','R','R','R','R','R','R',
        'R','R','R','R','R',
        // Right thumb: LT thumbs '*' (args 3, 4, 5); extras 'R' (args 0, 1, 2)
        'R','R',
            'R',
        '*','*','*'
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

layer_state_t layer_state_set_user(layer_state_t state) {
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();

    switch (get_highest_layer(state)) {
        case NUM:
            ergodox_right_led_1_on();
            break;
        case NAV:
            ergodox_right_led_2_on();
            break;
        case MED:
            ergodox_right_led_1_on();
            ergodox_right_led_3_on();
            break;
        case FUN:
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
            break;
        case SYM:
            ergodox_right_led_3_on();
            break;
        default:
            break;
    }

    return state;
}

// Light the on-board (left half) LED whenever any layer is locked.
bool layer_lock_set_user(layer_state_t locked_layers) {
    if (locked_layers) {
        ergodox_board_led_on();
    } else {
        ergodox_board_led_off();
    }
    return true;
}

// Override the ahdinosaur/keyboard_helper community module's default
// `row * MATRIX_COLS + col` because `LAYOUT_ergodox` permutes the
// matrix into physical-visual order. The host-side visualizer keys
// positions off LAYOUT-arg index (= the flat key order in
// ergodox-ez-dinosaur.yaml), so without this override every press
// would highlight the wrong cell. Layer indication does not depend
// on position and works either way.
//
// The map is derived from
// `qmk_firmware/keyboards/ergodox_ez/info.json` →
// `layouts.LAYOUT_ergodox.layout`: each entry there is one LAYOUT
// argument, and its `matrix: [row, col]` field gives the matrix
// position that argument fills. The 8 entries written `KH_NO_POS`
// are matrix slots with no physical key; a correctly wired ergodox
// will never fire an event from them, but a deliberate sentinel
// beats falling back to a default that would alias a valid index.
#define KH_NO_POS 0xFFFFu

// Pin the table to the matrix shape it was hand-built for. If QMK
// ever changes the ergodox_ez matrix dimensions the array would
// resize silently and the extra slots would default-init to 0 — a
// valid LAYOUT index — aliasing every press into the top-left key.
_Static_assert(MATRIX_ROWS == 14 && MATRIX_COLS == 6,
               "kh_layout_arg_index is hand-derived for ergodox_ez 14x6; "
               "regenerate from info.json if matrix dims change.");

static const uint16_t kh_layout_arg_index[MATRIX_ROWS][MATRIX_COLS] PROGMEM = {
    // Left half. col 5 = left thumb cluster.
    /*  0 */ {  0,  7, 14, 20, 27, KH_NO_POS },
    /*  1 */ {  1,  8, 15, 21, 28, 37 },
    /*  2 */ {  2,  9, 16, 22, 29, 36 },
    /*  3 */ {  3, 10, 17, 23, 30, 35 },
    /*  4 */ {  4, 11, 18, 24, 31, 34 },
    /*  5 */ {  5, 12, 19, 25, KH_NO_POS, 32 },
    /*  6 */ {  6, 13, KH_NO_POS, 26, KH_NO_POS, 33 },
    // Right half. col 5 = right thumb cluster.
    /*  7 */ { 38, 45, KH_NO_POS, 58, KH_NO_POS, 70 },
    /*  8 */ { 39, 46, 52, 59, KH_NO_POS, 71 },
    /*  9 */ { 40, 47, 53, 60, 65, 72 },
    /* 10 */ { 41, 48, 54, 61, 66, 75 },
    /* 11 */ { 42, 49, 55, 62, 67, 74 },
    /* 12 */ { 43, 50, 56, 63, 68, 73 },
    /* 13 */ { 44, 51, 57, 64, 69, KH_NO_POS },
};

uint16_t keyboard_helper_position_from_keypos(keypos_t key) {
    if (key.row >= MATRIX_ROWS || key.col >= MATRIX_COLS) {
        return KH_NO_POS;
    }
    return pgm_read_word(&kh_layout_arg_index[key.row][key.col]);
}
