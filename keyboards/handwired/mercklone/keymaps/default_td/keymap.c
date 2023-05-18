#include QMK_KEYBOARD_H

// Define a type for as many tap dance states as you need
typedef enum {
    TD_NONE,
    TD_UNKNOWN,
    TD_SINGLE_TAP,
    TD_SINGLE_HOLD,
    TD_DOUBLE_TAP
} td_state_t;

typedef struct {
    bool is_press_action;
    td_state_t state;
} td_tap_t;

enum {
    F1_L1, // tap: F1, hold: MO(L1), double tap: TO(L1)
	F2_L2, // tap: F2, hold: MO(L2), double tap: TO(L2)
	F3_L3, // tap: F3, hold: MO(L3), double tap: TO(L3)
};

// Declare the functions to be used with your tap dance key(s)

// Function associated with all tap dances
td_state_t cur_dance(qk_tap_dance_state_t *state);

// Functions associated with individual tap dances
void FL1_finished(qk_tap_dance_state_t *state, void *user_data);
void FL1_reset(qk_tap_dance_state_t *state, void *user_data);
void FL2_finished(qk_tap_dance_state_t *state, void *user_data);
void FL2_reset(qk_tap_dance_state_t *state, void *user_data);
void FL3_finished(qk_tap_dance_state_t *state, void *user_data);
void FL3_reset(qk_tap_dance_state_t *state, void *user_data);

// Determine the current tap dance state
td_state_t cur_dance(qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (!state->pressed) return TD_SINGLE_TAP;
        else return TD_SINGLE_HOLD;
    } else if (state->count == 2) return TD_DOUBLE_TAP;
    else return TD_UNKNOWN;
}

// Initialize tap structure associated with tap dance key(s)
static td_tap_t FL1_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
static td_tap_t FL2_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};
static td_tap_t FL3_tap_state = {
    .is_press_action = true,
    .state = TD_NONE
};

// Functions that control what our tap dance key does
void FL1_finished(qk_tap_dance_state_t *state, void *user_data) {
    FL1_tap_state.state = cur_dance(state);
    switch (FL1_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_F1);
            break;
        case TD_SINGLE_HOLD:
            layer_on(1);
            break;
        case TD_DOUBLE_TAP:
            // Check to see if the layer is already set
            if (layer_state_is(1)) {
                // If already set, then switch it off
                layer_off(1);
            } else {
                // If not already set, then switch the layer on
                layer_on(1);
            }
            break;
        default:
            break;
    }
}

void FL1_reset(qk_tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (FL1_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(1);
    }
    FL1_tap_state.state = TD_NONE;
}
void FL2_finished(qk_tap_dance_state_t *state, void *user_data) {
    FL2_tap_state.state = cur_dance(state);
    switch (FL2_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_F2);
            break;
        case TD_SINGLE_HOLD:
            layer_on(2);
            break;
        case TD_DOUBLE_TAP:
            // Check to see if the layer is already set
            if (layer_state_is(2)) {
                // If already set, then switch it off
                layer_off(2);
            } else {
                // If not already set, then switch the layer on
                layer_on(2);
            }
            break;
        default:
            break;
    }
}

void FL2_reset(qk_tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (FL2_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(2);
    }
    FL2_tap_state.state = TD_NONE;
}
void FL3_finished(qk_tap_dance_state_t *state, void *user_data) {
    FL3_tap_state.state = cur_dance(state);
    switch (FL3_tap_state.state) {
        case TD_SINGLE_TAP:
            tap_code(KC_F3);
            break;
        case TD_SINGLE_HOLD:
            layer_on(3);
            break;
        case TD_DOUBLE_TAP:
            // Check to see if the layer is already set
            if (layer_state_is(3)) {
                // If already set, then switch it off
                layer_off(3);
            } else {
                // If not already set, then switch the layer on
                layer_on(3);
            }
            break;
        default:
            break;
    }
}

void FL3_reset(qk_tap_dance_state_t *state, void *user_data) {
    // If the key was held down and now is released then switch off the layer
    if (FL3_tap_state.state == TD_SINGLE_HOLD) {
        layer_off(3);
    }
    FL3_tap_state.state = TD_NONE;
}

qk_tap_dance_action_t tap_dance_actions[] = {
    [F1_L1] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, FL1_finished, FL1_reset),
	[F2_L2] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, FL2_finished, FL2_reset),
	[F3_L3] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, FL3_finished, FL3_reset)
};


// Set a long-ish tapping term for tap-dance keys
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case QK_TAP_DANCE ... QK_TAP_DANCE_MAX:
            return 275;
        default:
            return TAPPING_TERM;
    }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Default Layer (0)
	 * NOK = NO PHYSICAL KEY IN MATRIX
     * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
     * │     │     │     │     │     │     │     │LT-1/│
     * │  7  │  8  │  9  │  0  │  -  │  =  │ ESC │   F1│
     * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     * │     │     │     │XXXXX│     │     │     │LT-2/│
     * │  1  │  2  │  3  │-NOK-│  4  │  5  │  6  │  F2 │
     * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     * │     │     │     │     │     │     │     │LT-1/│
     * │  P  │ TAB │  Q  │  W  │  E  │  R  │  T  │  F3 │
     * └─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
	 *       │     │     │     │     │     │     │LT-1/│
     *       │  C  │  A  │  S  │  D  │  F  │  G  │   F4│
     *       ├─────┼─────┴─────┴─────┼─────┼─────┼─────┤
     *       │     │                 │     │     │     │
     *       │SHIFT│                 │  V  │  B  │  ~  │	 
     *       ├─────┤                 ├─────┼─────┼─────┘
     *       │     │                 │     │     │
     *       │CTRL │                 │ ALT │ SPC │ 
     *       └─────┘                 └─────┴─────┘
     */
    [0] = LAYOUT_default(
		KC_7,		KC_8, 	KC_9, 	KC_0,	KC_MINS,	KC_EQL,	KC_ESC,	TD(F1_L1),
		KC_1,		KC_2,	KC_3,	/*---*/	KC_4, 		KC_5, 	KC_6, 	TD(F2_L2),
		KC_P,		KC_TAB,	KC_Q,	KC_W,	KC_E,		KC_R,	KC_T,	TD(F3_L3),
		/*---*/		KC_C, 	KC_A, 	KC_S,	KC_D,	 	KC_F, 	KC_G, 	KC_F4,
		/*---*/		KC_LSFT,/*---*//*---*/ /*---*/		KC_V,	KC_B,	KC_GRV,
		/*---*/		KC_LCTL,/*---*//*---*/ /*---*/		KC_LALT,KC_SPC
	),
    /* Layer 1
	 * NOK = NO PHYSICAL KEY IN MATRIX
     * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
     * │ BL  │ BL  │     │     │     │ BL  │ TO  │     │
     * │ STEP│ BRTH│ TRN │ TRN │ TRN │ TOGG│ L(0)│ TRN │
     * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     * │ BL  │ BL  │     │XXXXX│     │     │     │ TO  │
     * │  -  │  +  │ TRN │-NOK-│ TRN │ TRN │ TRN │ L(1)│
     * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     * │     │     │ VOL │     │ VOL │     │     │     │
     * │ TRN │ TRN │  -  │ MUTE│  +  │ TRN │ TRN │ TRN │
     * └─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
	 *       │     │     │     │     │     │     │     │
     *       │ TRN │ PREV│ PLAY│ NEXT│ TRN │ TRN │ TRN │
     *       ├─────┼─────┴─────┴─────┼─────┼─────┼─────┤
     *       │     │                 │     │     │BTLDR│
     *       │ TRN │                 │ TRN │ TRN │RESET│	 
     *       ├─────┤                 ├─────┼─────┼─────┘
     *       │     │                 │     │     │
     *       │ TRN │                 │ TRN │ TRN │ 
     *       └─────┘                 └─────┴─────┘
     */
    [1] = LAYOUT_default(
		BL_STEP,	BL_BRTG, KC_TRNS, KC_TRNS,	KC_TRNS, BL_TOGG, TO(0),	KC_TRNS,
		BL_DEC,		BL_INC,	 KC_TRNS, /*---*/	KC_TRNS, KC_TRNS, KC_TRNS,	KC_TRNS,
		KC_TRNS,	KC_TRNS, KC_VOLD, KC_MUTE,	KC_VOLU, KC_TRNS, KC_TRNS,	KC_TRNS,
		/*---*/		KC_TRNS, KC_MPRV, KC_MPLY,	KC_MNXT, KC_TRNS, KC_TRNS,	KC_TRNS,
		/*---*/		KC_TRNS, /*---*/  /*---*/	/*---*/  KC_TRNS, KC_TRNS,	QK_BOOT,
		/*---*/		KC_TRNS, /*---*/  /*---*/	/*---*/  KC_TRNS, KC_TRNS
	),
    /* Layer 2
	 * NOK = NO PHYSICAL KEY IN MATRIX
     * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
     * │MOUSE│MOUSE│MOUSE│     │     │     │ TO  │     │
     * │ACCL1│ACCL2│ACCL3│ TRN │ TRN │ TRN │ L(0)│ TRN │
     * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     * │MOUSE│MOUSE│MOUSE│XXXXX│     │     │     │     │
     * │BTN 3│BTN 4│BTN 5│-NOK-│ TRN │ TRN │ TRN │ TRN │
     * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     * │     │     │MOUSE│MOUSE│MOUSE│MOUSE│     │ TO  │
     * │ TRN │ TRN │BTN 1│ UP  │BTN 2│WHL U│ TRN │ L(2)│
     * └─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
	 *       │     │MOUSE│MOUSE│MOUSE│MOUSE│     │     │
     *       │ TRN │ LEFT│ DOWN│RIGHT│WHL D│ TRN │ TRN │
     *       ├─────┼─────┴─────┴─────┼─────┼─────┼─────┤
     *       │     │                 │     │     │     │
     *       │ TRN │                 │ TRN │ TRN │ TRN │	 
     *       ├─────┤                 ├─────┼─────┼─────┘
     *       │     │                 │     │     │
     *       │ TRN │                 │ TRN │ TRN │ 
     *       └─────┘                 └─────┴─────┘
     */
    [2] = LAYOUT_default(
		KC_ACL0, KC_ACL1, KC_ACL2, KC_TRNS, KC_TRNS, KC_TRNS, TO(0),	KC_TRNS,
		KC_BTN3, KC_BTN4, KC_BTN5, /*	 */	KC_TRNS, KC_TRNS, KC_TRNS,	KC_TRNS,
		KC_TRNS, KC_TRNS, KC_BTN1, KC_MS_U,	KC_BTN2, KC_WH_U, KC_TRNS,	KC_TRNS,
		/*	 */	 KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D, KC_TRNS,	KC_TRNS,
		/*	 */	 KC_TRNS, /*---*/  /*---*/  /*---*/  KC_TRNS, KC_TRNS,	KC_TRNS,
		/*	 */	 KC_TRNS, /*---*/  /*---*/  /*---*/  KC_TRNS, KC_TRNS
	),
    /* Layer 3
	 * NOK = NO PHYSICAL KEY IN MATRIX
     * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
     * │     │     │     │     │     │     │ TO  │     │
     * │ TRN │ TRN │ TRN │ TRN │ TRN │ TRN │ L(0)│ TRN │
     * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     * │     │     │     │XXXXX│     │     │     │     │
     * │  F5 │ F6  │ F7  │-NOK-│  F8 │  F9 │ F10 │ TRN │
     * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     * │     │     │PAGE │     │PAGE │COPY │UNDO │     │
     * │ TRN │ TRN │ UP  │ UP  │ DOWN│CTR-C│CTR-Z│ TRN │
     * └─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
	 *       │     │     │     │     │PASTE│REDO │ TO  │
     *       │ TRN │LEFT │ DOWN│RIGHT│CTR-V│CTR-Y│ L(3)│
	 *       ├─────┼─────┴─────┴─────┼─────┼─────┼─────┤
     *       │     │                 │CUT  │     │ KB  │
     *       │ TRN │                 │CTR-X│ TRN │ RST │	 
     *       ├─────┤                 ├─────┼─────┼─────┘
     *       │     │                 │     │     │
     *       │ TRN │                 │ TRN │ TRN │ 
     *       └─────┘                 └─────┴─────┘
     */
    [3] = LAYOUT_default(
		KC_TRNS, KC_TRNS, KC_TRNS,	KC_TRNS,	KC_TRNS,	KC_TRNS,	TO(0),		KC_TRNS,
		KC_F5,	 KC_F6,	  KC_F7,	/*---*/		KC_F8,		KC_F9,		KC_F10,		KC_TRNS,
		KC_TRNS, KC_TRNS, KC_PGUP,	KC_UP,		KC_PGDN,	LCTL(KC_C), LCTL(KC_Z),	KC_TRNS,
		/*---*/	 KC_TRNS, KC_LEFT,	KC_DOWN,	KC_RGHT,	LCTL(KC_V), LCTL(KC_Y),	KC_TRNS,
		/*---*/	 KC_TRNS, /*---*/	/*---*/		/*---*/		LCTL(KC_X),	KC_TRNS,	QK_RBT,
		/*---*/	 KC_TRNS, /*---*/	/*---*/		/*---*/		KC_TRNS,	KC_TRNS
	),
    /* Layer 4
	 * NOK = NO PHYSICAL KEY IN MATRIX
     * ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┬─────┐
     * │     │     │     │     │     │     │ TO  │     │
     * │ TRN │ TRN │ TRN │ TRN │ TRN │ TRN │ L(0)│ TRN │
     * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     * │     │     │     │XXXXX│     │     │     │     │
     * │  F5 │ F6  │ F7  │-NOK-│  F8 │  F9 │ F10 │ TRN │
     * ├─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
     * │     │     │     │     │     │ PAGE│     │     │
     * │ TRN │ TRN │COPY │ UP  │PASTE│ UP  │ TRN │ TRN │
     * └─────┼─────┼─────┼─────┼─────┼─────┼─────┼─────┤
	 *       │     │     │     │     │ PAGE│     │     │
     *       │ TRN │LEFT │ DOWN│RIGHT│ DOWN│ TRN │ TRN │
     *       ├─────┼─────┴─────┴─────┼─────┼─────┼─────┤
     *       │     │                 │     │     │ KB  │
     *       │ TRN │                 │ TRN │ TRN │ RST │	 
     *       ├─────┤                 ├─────┼─────┼─────┘
     *       │     │                 │     │     │
     *       │ TRN │                 │ TRN │ TRN │ 
     *       └─────┘                 └─────┴─────┘
     */
	/*[4] = LAYOUT_default(
		KC_TRNS, KC_TRNS, KC_TRNS,	KC_TRNS, KC_TRNS, KC_TRNS,	TO(0),  KC_TRNS,
		KC_F5,	 KC_F6,	  KC_F7,	/---/	 KC_F8,   KC_F9,	KC_F10, KC_TRNS,
		KC_TRNS, KC_TRNS, KC_COPY,	KC_UP,	 KC_PSTE, KC_PGUP,	KC_TRNS,KC_TRNS,
		/---/	 KC_TRNS, KC_LEFT,	KC_DOWN, KC_RGHT, KC_PGDN,	TG(4),	KC_TRNS,
		/---/	 KC_TRNS, /---/	/---/	 /---/  KC_TRNS,	KC_TRNS,QK_RBT,
		/---/	 KC_TRNS, /---/	/---/	 /---/  KC_TRNS,	KC_TRNS
	),
	*/
};