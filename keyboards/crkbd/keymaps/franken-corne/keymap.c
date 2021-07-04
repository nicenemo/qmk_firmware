#include QMK_KEYBOARD_H

extern keymap_config_t keymap_config;

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

#ifdef OLED_DRIVER_ENABLE
static uint32_t oled_timer = 0;
#endif

// Each layer gets a name for readability, which is then used in the keymap matrix below.
// The underscores don't mean anything - you can have a layer called STUFF or any other name.
// Layer names don't all need to be of the same length, obviously, and you can also skip them
// entirely and just use numbers.
enum layers {
  _QWERTY = 0,
  _NEO2 = 1,
  _SYMBOL = 2,
  _MOUSE = 3,
  _LEFT_NUMPAD = 4,
  _NAV =5,
  _FUNCTION_KEYS = 6,
  _MEDIA = 7,
  _ADJUST = 8
};

// Custom keycodes for layer keys

enum custom_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  RAISE,
  ADJUST,
  RGBRST
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT_split_3x6_3( // 0 qwerty layer
  //,-----------------------------------------.                                   ,---------------------------------------------.
  KC_TILD,  KC_Q,  KC_W,  KC_E,  KC_R,  KC_T,                                      KC_Y,  KC_U,  KC_I,  KC_O,  KC_P,  KC_HASH,
  //------+------+------+------+------+------|                                    |------+------+-------+------+-------+--------|
  MEH_T(KC_TAB),  KC_A, LCTL_T(KC_S), RALT_T(KC_D), LGUI_T(KC_F), LSFT_T(KC_G),    RSFT_T(KC_H),  RGUI_T(KC_J),  RALT_T(KC_K),  RCTL_T(KC_L), KC_SCLN,KC_QUOT,
  //------+------+------+------+------+------|                                    |------+------+-------+------+-------+--------|
  LT(_MEDIA, KC_AT),  KC_Z,  KC_X,  KC_C,  KC_V,  KC_B,                            KC_N,  KC_M,KC_COMM,KC_DOT,KC_SLSH, LT(_FUNCTION_KEYS, KC_BSLS),
  //------+------+------+------+------+------+------|                             |------+------+------+-------+------+-------+--------|
              ALL_T(KC_ESC),LT(_NAV,KC_DEL), LT(_MOUSE,KC_SPC),                    KC_ENT, LT(_LEFT_NUMPAD,KC_BSPC), LT(_SYMBOL, KC_COLN)
             //`--------------------'                                             '--------------------'
  ),
  [_NEO2] = LAYOUT_split_3x6_3( // NEO2 base layer adapted for Corne keyboard and Dutch language. No Diacritics
  //,-----------------------------------------.                                   ,-----------------------------------------.
     KC_TILD, KC_X, KC_V, KC_L, KC_C, KC_W,                                        KC_K, KC_H, KC_G, KC_F, KC_Q, KC_HASH,
  //------+------+------+------+------+------|                                    |------+------+------+------+------+------|
     MEH_T(KC_TAB), KC_U, LCTL_T(KC_I), LALT_T(KC_A), LGUI_T(KC_E), LSFT_T(KC_O),  RSFT_T(KC_S), RGUI_T(KC_N), RALT_T(KC_R), RCTL_T(KC_T), KC_D, KC_Y,
  //------+------+------+------+------+------|                                    |------+------+------+------+------+------|
     LT(_MEDIA, KC_AT), KC_DLR, KC_J, KC_NO, KC_P,KC_Z,                           KC_B, KC_M, KC_COMM, KC_DOT, KC_SLSH, LT(_FUNCTION_KEYS,KC_BSLS),
  //------+------+------+------+------+------+------|                             |------+------+------+------+------+------+------|
                KC_TRNS, KC_TRNS, KC_TRNS,                                         KC_TRNS, KC_TRNS,KC_TRNS
                //`--------------------'                                          `--------------------'
  ),
  [_SYMBOL] = LAYOUT_split_3x6_3( //  2 Symbol layer
  //,---------------------------------------------.                ,-----------------------------------------.
     KC_AT, KC_7,  KC_8,  KC_9,  KC_PAST,  KC_BSLS,                  KC_PSCR, KC_NO,   KC_BRID,   KC_BRIU,  KC_NO,  KC_NO,
  //|------+------+-------+-------+-------+-------|                |------+------+------+------+------+------|
     KC_UNDS, KC_4,  KC_5,  KC_6,  KC_PPLS,  KC_COMM,                KC_RSFT, KC_RGUI, KC_RALT, KC_RCTL, KC_NO, KC_NO,
  //|------+------+-------+-------+-------+-------|                |------+------+------+------+------+------|
     KC_HASH, KC_1,  KC_2,  KC_3,  KC_PCMM,  KC_DLR,                  KC_CAPS,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO,
  //|------+------+-------+-------+-------+-------+------|  |------+------+------+------+------+------+------|
                                   KC_0, KC_NO, KC_PEQL,      TO(_NEO2), TO(_QWERTY), KC_NO
                                  //`--------------------'  `--------------------'
  ),
  [_MOUSE] = LAYOUT_split_3x6_3( // 3 mouse layer
  //,-----------------------------------------.                ,-----------------------------------------.
     KC_NO,  KC_NO,KC_NO, KC_NO, KC_NO, KC_NO,                  KC_WBAK, KC_WREF, KC_WHOM, KC_WFWD,  KC_NO, KC_WFAV,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_NO, KC_NO, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT,            KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_BTN4, KC_WSTP,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,KC_ACL0,                    KC_WH_L, KC_WH_D, KC_WH_U, KC_WH_R, KC_BTN5, KC_WSCH,
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                KC_ACL2, KC_ACL1, KC_NO,      KC_BTN1, KC_BTN2, KC_BTN3
                              //`--------------------'  `--------------------'
  ),
  [_LEFT_NUMPAD] = LAYOUT_split_3x6_3( // 4 left numpad layer
  //,---------------------------------------------.                                    ,-----------------------------------------.
     KC_EXLM, KC_7,  KC_8,  KC_9,  KC_PAST,  KC_PSLS,                                   KC_PSCR, KC_NO, KC_BRID, KC_BRIU, KC_NO, KC_NO,
  //------+------+-------+-------+-------+-------|                                    |------+------+------+------+------+------|
     KC_PMNS, KC_4,  KC_5,  KC_F6,  KC_PPLS, KC_DOT,                                  KC_RSFT, KC_RGUI, KC_RALT, KC_RCTL, KC_NO, KC_NO,
  //------+------+-------+-------+-------+-------|                                    |------+------+------+------+------+------|
     KC_PDOT, KC_1,  KC_2,  KC_3,  KC_PCMM,  KC_PERC,                                    KC_CAPS, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
  //------+------+-------+-------+-------+-------+------|                             |------+------+------+------+------+------+------|
                                   KC_0, KC_CIRC, KC_PEQL,                            KC_NO, KC_NO, KC_NO
                                  //`--------------------'                             `--------------------'
  ),
  [_NAV] = LAYOUT_split_3x6_3( // 5 nav layer
  //,---------------------------------------------.                ,-----------------------------------------.
     KC_NO, KC_NO,  KC_NO,   KC_NO,   KC_NO,   KC_NO,               KC_CUT,KC_COPY,KC_PSTE,KC_AGIN,KC_UNDO,KC_PIPE,
  //|------+------+-------+-------+-------+-------|                |------+------+------+------+------+------|
     KC_CAPS, KC_NO,  KC_LCTL, KC_LALT, KC_LGUI,KC_LSFT,              KC_LEFT,KC_DOWN,KC_UP,KC_RIGHT,KC_NO,KC_NO,
  //|------+------+-------+-------+-------+-------|                |------+------+------+------+------+------|
     KC_NO, KC_NO,  KC_NO,  KC_NO,  KC_NO,  KC_NO,                  KC_HOME,KC_PGDN,KC_PGUP,KC_END,KC_NO,KC_NO,
  //|------+------+-------+-------+-------+-------+------|  |------+------+------+------+------+------+------|
                                   KC_NO, KC_NO, KC_NO,      KC_NO, KC_NO, TO(_ADJUST)
                                  //`--------------------'  `--------------------'
  ),
  [_FUNCTION_KEYS] = LAYOUT_split_3x6_3( // 6 functions keys
  //,---------------------------------------------.                                    ,-----------------------------------------.
     KC_MYCM, KC_F7,  KC_F8,  KC_F9,  KC_NO,  KC_F23,                                   KC_F24, KC_NO, KC_F17, KC_F18, KC_F19, KC_WAKE,
  //------+------+-------+-------+-------+-------|                                    |------+------+------+------+------+------|
     KC_CALC, KC_F4,  LCTL_T(KC_F5),  LALT_T(KC_F6),  LGUI_T(KC_NO), LSFT(KC_F21),      RSFT_T(KC_F22), RGUI_T(KC_NO), RALT_T(KC_F14), RCTL_T(KC_F15), KC_F16, KC_SLEP,
  //------+------+-------+-------+-------+-------|                                    |------+------+------+------+------+------|
     KC_MENU, KC_F1,  KC_F2,  KC_F3,  KC_NO,  KC_NO,                                    KC_NO, KC_NO, KC_F11, KC_F12, KC_F13, KC_NO,
  //------+------+-------+-------+-------+-------+------|                             |------+------+------+------+------+------+------|
                                   KC_F10, KC_MSEL, KC_MAIL,                            KC_PWR, KC_NO, KC_F20
                                  //`--------------------'                             `--------------------'
  ),
  [_MEDIA] = LAYOUT_split_3x6_3( // 7 media
  //,-----------------------------------------.                ,-----------------------------------------.
     KC_NO,  KC_NO,KC_NO, KC_NO, KC_NO, KC_NO,                   KC_NO, KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_NO, KC_NO, KC_LCTL, KC_LALT, KC_LGUI, KC_LSFT,            KC_MPRV, KC_VOLD, KC_VOLU, KC_MNXT, KC_NO, KC_NO,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    KC_NO, KC_NO, KC_NO, KC_NO, KC_NO,KC_NO,                    KC_MRWD, KC_EJCT, KC_PAUS, KC_MFFD, KC_NO, KC_NO,
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                KC_NO, KC_NO, KC_NO,      KC_MSTP, KC_MPLY, KC_MUTE
                              //`--------------------'  `--------------------'
  ),

  [_ADJUST] = LAYOUT_split_3x6_3( // 8 adjust
  //,-----------------------------------------.                ,-----------------------------------------.
      RESET,RGBRST, KC_NO, KC_NO, KC_NO, KC_NO,                  KC_NO,KC__MUTE, KC_NO, KC_NO, KC_NO, KC_NO,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    RGB_TOG,RGB_HUI,RGB_SAI,RGB_VAI,RGB_SPI,KC_NO,               KC_PAUSE,KC__VOLUP, KC_NO, KC_NO, KC_NO, KC_NO,
  //|------+------+------+------+------+------|                |------+------+------+------+------+------|
    RGB_MOD,RGB_HUD,RGB_SAD,RGB_VAD,RGB_SPD,KC_NO,               KC_SCROLLLOCK,KC__VOLDOWN, KC_NO, KC_NO, KC_NO, RGB_RMOD,
  //|------+------+------+------+------+------+------|  |------+------+------+------+------+------+------|
                                KC_NO, KC_NO, KC_NO,      KC_NO, TO(_NEO2), TO(_QWERTY)
                              //`--------------------'  `--------------------'
  )
};

int RGB_current_mode;

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
}

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) { return OLED_ROTATION_270; }

void render_space(void) {
    oled_write_P(PSTR("     "), false);
}

void render_mod_status_gui_alt(uint8_t modifiers) {
    static const char PROGMEM gui_off_1[] = {0x85, 0x86, 0};
    static const char PROGMEM gui_off_2[] = {0xa5, 0xa6, 0};
    static const char PROGMEM gui_on_1[] = {0x8d, 0x8e, 0};
    static const char PROGMEM gui_on_2[] = {0xad, 0xae, 0};

    static const char PROGMEM alt_off_1[] = {0x87, 0x88, 0};
    static const char PROGMEM alt_off_2[] = {0xa7, 0xa8, 0};
    static const char PROGMEM alt_on_1[] = {0x8f, 0x90, 0};
    static const char PROGMEM alt_on_2[] = {0xaf, 0xb0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_1, false);
    } else {
        oled_write_P(gui_off_1, false);
    }

    if ((modifiers & MOD_MASK_GUI) && (modifiers & MOD_MASK_ALT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_1, false);
    } else {
        oled_write_P(alt_off_1, false);
    }

    if(modifiers & MOD_MASK_GUI) {
        oled_write_P(gui_on_2, false);
    } else {
        oled_write_P(gui_off_2, false);
    }

    if (modifiers & MOD_MASK_GUI & MOD_MASK_ALT) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_GUI) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_ALT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_ALT) {
        oled_write_P(alt_on_2, false);
    } else {
        oled_write_P(alt_off_2, false);
    }
}

void render_mod_status_ctrl_shift(uint8_t modifiers) {
    static const char PROGMEM ctrl_off_1[] = {0x89, 0x8a, 0};
    static const char PROGMEM ctrl_off_2[] = {0xa9, 0xaa, 0};
    static const char PROGMEM ctrl_on_1[] = {0x91, 0x92, 0};
    static const char PROGMEM ctrl_on_2[] = {0xb1, 0xb2, 0};

    static const char PROGMEM shift_off_1[] = {0x8b, 0x8c, 0};
    static const char PROGMEM shift_off_2[] = {0xab, 0xac, 0};
    static const char PROGMEM shift_on_1[] = {0xcd, 0xce, 0};
    static const char PROGMEM shift_on_2[] = {0xcf, 0xd0, 0};

    // fillers between the modifier icons bleed into the icon frames
    static const char PROGMEM off_off_1[] = {0xc5, 0};
    static const char PROGMEM off_off_2[] = {0xc6, 0};
    static const char PROGMEM on_off_1[] = {0xc7, 0};
    static const char PROGMEM on_off_2[] = {0xc8, 0};
    static const char PROGMEM off_on_1[] = {0xc9, 0};
    static const char PROGMEM off_on_2[] = {0xca, 0};
    static const char PROGMEM on_on_1[] = {0xcb, 0};
    static const char PROGMEM on_on_2[] = {0xcc, 0};

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_1, false);
    } else {
        oled_write_P(ctrl_off_1, false);
    }

    if ((modifiers & MOD_MASK_CTRL) && (modifiers & MOD_MASK_SHIFT)) {
        oled_write_P(on_on_1, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_1, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_1, false);
    } else {
        oled_write_P(off_off_1, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_1, false);
    } else {
        oled_write_P(shift_off_1, false);
    }

    if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(ctrl_on_2, false);
    } else {
        oled_write_P(ctrl_off_2, false);
    }

    if (modifiers & MOD_MASK_CTRL & MOD_MASK_SHIFT) {
        oled_write_P(on_on_2, false);
    } else if(modifiers & MOD_MASK_CTRL) {
        oled_write_P(on_off_2, false);
    } else if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(off_on_2, false);
    } else {
        oled_write_P(off_off_2, false);
    }

    if(modifiers & MOD_MASK_SHIFT) {
        oled_write_P(shift_on_2, false);
    } else {
        oled_write_P(shift_off_2, false);
    }
}

void render_logo(void) {
    static const char PROGMEM corne_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0};
    oled_write_P(corne_logo, false);
    oled_write_P(PSTR("corne"), false);
}

void render_layer_state(void) {
    static const char PROGMEM default_layer[] = {
        0x20, 0x94, 0x95, 0x96, 0x20,
        0x20, 0xb4, 0xb5, 0xb6, 0x20,
        0x20, 0xd4, 0xd5, 0xd6, 0x20, 0};
    static const char PROGMEM raise_layer[] = {
        0x20, 0x97, 0x98, 0x99, 0x20,
        0x20, 0xb7, 0xb8, 0xb9, 0x20,
        0x20, 0xd7, 0xd8, 0xd9, 0x20, 0};
    static const char PROGMEM lower_layer[] = {
        0x20, 0x9a, 0x9b, 0x9c, 0x20,
        0x20, 0xba, 0xbb, 0xbc, 0x20,
        0x20, 0xda, 0xdb, 0xdc, 0x20, 0};
    static const char PROGMEM adjust_layer[] = {
        0x20, 0x9d, 0x9e, 0x9f, 0x20,
        0x20, 0xbd, 0xbe, 0xbf, 0x20,
        0x20, 0xdd, 0xde, 0xdf, 0x20, 0};
    if(layer_state_is(_ADJUST)) {
        oled_write_P(adjust_layer, false);
    } else if(layer_state_is(_SYMBOL)) {
        oled_write_P(lower_layer, false);
    } else if(layer_state_is(_LEFT_NUMPAD)) {
        oled_write_P(raise_layer, false);
    } else {
        oled_write_P(default_layer, false);
    }
}

void render_status_main(void) {
    render_logo();
    render_space();
    render_layer_state();
    render_space();
    render_mod_status_gui_alt(get_mods()|get_oneshot_mods());
    render_mod_status_ctrl_shift(get_mods()|get_oneshot_mods());
}

void render_status_secondary(void) {
    render_logo();
    render_space();
    render_layer_state();
    render_space();
    render_mod_status_gui_alt(get_mods()|get_oneshot_mods());
    render_mod_status_ctrl_shift(get_mods()|get_oneshot_mods());
}

void suspend_power_down_user() {
    oled_off();
}

void oled_task_user(void) {
    if (timer_elapsed32(oled_timer) > 30000) {
        oled_off();
        return;
    }
#ifndef SPLIT_KEYBOARD
    else { oled_on(); }
#endif

    if (is_keyboard_master()) {
        render_status_main();  // Renders the current keyboard state (layer, lock, caps, scroll, etc)
    } else {
        render_status_secondary();
    }
}

#endif
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
        oled_timer = timer_read32();
#endif
    // set_timelog();
  }

  switch (keycode) {
    case LOWER:
      if (record->event.pressed) {
        layer_on(_SYMBOL);
        update_tri_layer_RGB(_SYMBOL, _LEFT_NUMPAD, _ADJUST);
      } else {
        layer_off(_SYMBOL);
        update_tri_layer_RGB(_SYMBOL, _LEFT_NUMPAD, _ADJUST);
      }
      return false;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_LEFT_NUMPAD);
        update_tri_layer_RGB(_SYMBOL, _LEFT_NUMPAD, _ADJUST);
      } else {
        layer_off(_LEFT_NUMPAD);
        update_tri_layer_RGB(_SYMBOL, _LEFT_NUMPAD, _ADJUST);
      }
      return false;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
    case RGBRST:
      #ifdef RGBLIGHT_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgblight_default();
          rgblight_enable();
          RGB_current_mode = rgblight_config.mode;
        }
      #endif
      #ifdef RGB_MATRIX_ENABLE
        if (record->event.pressed) {
          eeconfig_update_rgb_matrix_default();
          rgb_matrix_enable();
        }
      #endif
      break;
  }
  return true;
}

#ifdef RGB_MATRIX_ENABLE

void suspend_power_down_keymap(void) {
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_keymap(void) {
    rgb_matrix_set_suspend_state(false);
}

#endif
