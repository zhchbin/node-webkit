// Copyright (c) 2012 Intel Corp
// Copyright (c) 2012 The Chromium Authors
// 
// Permission is hereby granted, free of charge, to any person obtaining a copy 
// of this software and associated documentation files (the "Software"), to deal
//  in the Software without restriction, including without limitation the rights
//  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell co
// pies of the Software, and to permit persons to whom the Software is furnished
//  to do so, subject to the following conditions:
// 
// The above copyright notice and this permission notice shall be included in al
// l copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IM
// PLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNES
// S FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS
//  OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WH
// ETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
//  CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

#ifndef CONTENT_NW_SRC_API_KEYCODES_H_
#define CONTENT_NW_SRC_API_KEYCODES_H_ 

#include "ui/base/keycodes/keyboard_codes.h"

namespace api {

const uint8 kModifiersRnageMin = 1;
const uint8 kModifiersRnageMax = 15;

const uint8 kModifiersAlt = 1; 
const uint8 kModifiersCtrl = 1 << 1; 
const uint8 kModifiersMeta = 1 << 2; 
const uint8 kModifiersShirt = 1 << 3; 

// Note: This KeyboardCodesMap map whit the index of the |hotkey.js|
const ui::KeyboardCode kKeyboardCodesMap[] = {
  ui::VKEY_BACK,
  ui::VKEY_TAB,
#if defined(OS_WIN)
  ui::VKEY_UNKNOWN,
#elif defined(OS_POSIX)
  ui::VKEY_BACKTAB,  // Note: windows doesn't have this virtual key.
#endif
  ui::VKEY_CLEAR,
  ui::VKEY_RETURN,
  ui::VKEY_SHIFT,
  ui::VKEY_CONTROL,
  ui::VKEY_MENU,
  ui::VKEY_PAUSE,
  ui::VKEY_CAPITAL,
  ui::VKEY_KANA,
  ui::VKEY_HANGUL,
  ui::VKEY_JUNJA,
  ui::VKEY_FINAL,
  ui::VKEY_HANJA,
  ui::VKEY_KANJI,
  ui::VKEY_ESCAPE,
  ui::VKEY_CONVERT,
  ui::VKEY_NONCONVERT,
  ui::VKEY_ACCEPT,
  ui::VKEY_MODECHANGE,
  ui::VKEY_SPACE,
  ui::VKEY_PRIOR,
  ui::VKEY_NEXT,
  ui::VKEY_END,
  ui::VKEY_HOME,
  ui::VKEY_LEFT,
  ui::VKEY_UP,
  ui::VKEY_RIGHT,
  ui::VKEY_DOWN,
  ui::VKEY_SELECT,
  ui::VKEY_PRINT,
  ui::VKEY_EXECUTE,
  ui::VKEY_SNAPSHOT,
  ui::VKEY_INSERT,
  ui::VKEY_DELETE,
  ui::VKEY_HELP,
  ui::VKEY_0,
  ui::VKEY_1,
  ui::VKEY_2,
  ui::VKEY_3,
  ui::VKEY_4,
  ui::VKEY_5,
  ui::VKEY_6,
  ui::VKEY_7,
  ui::VKEY_8,
  ui::VKEY_9,
  ui::VKEY_A,
  ui::VKEY_B,
  ui::VKEY_C,
  ui::VKEY_D,
  ui::VKEY_E,
  ui::VKEY_F,
  ui::VKEY_G,
  ui::VKEY_H,
  ui::VKEY_I,
  ui::VKEY_J,
  ui::VKEY_K,
  ui::VKEY_L,
  ui::VKEY_M,
  ui::VKEY_N,
  ui::VKEY_O,
  ui::VKEY_P,
  ui::VKEY_Q,
  ui::VKEY_R,
  ui::VKEY_S,
  ui::VKEY_T,
  ui::VKEY_U,
  ui::VKEY_V,
  ui::VKEY_W,
  ui::VKEY_X,
  ui::VKEY_Y,
  ui::VKEY_Z,
  ui::VKEY_LWIN,
  ui::VKEY_COMMAND,
  ui::VKEY_RWIN,
  ui::VKEY_APPS,
  ui::VKEY_SLEEP,
  ui::VKEY_NUMPAD0,
  ui::VKEY_NUMPAD1,
  ui::VKEY_NUMPAD2,
  ui::VKEY_NUMPAD3,
  ui::VKEY_NUMPAD4,
  ui::VKEY_NUMPAD5,
  ui::VKEY_NUMPAD6,
  ui::VKEY_NUMPAD7,
  ui::VKEY_NUMPAD8,
  ui::VKEY_NUMPAD9,
  ui::VKEY_MULTIPLY,
  ui::VKEY_ADD,
  ui::VKEY_SEPARATOR,
  ui::VKEY_SUBTRACT,
  ui::VKEY_DECIMAL,
  ui::VKEY_DIVIDE,
  ui::VKEY_F1,
  ui::VKEY_F2,
  ui::VKEY_F3,
  ui::VKEY_F4,
  ui::VKEY_F5,
  ui::VKEY_F6,
  ui::VKEY_F7,
  ui::VKEY_F8,
  ui::VKEY_F9,
  ui::VKEY_F10,
  ui::VKEY_F11,
  ui::VKEY_F12,
  ui::VKEY_F13,
  ui::VKEY_F14,
  ui::VKEY_F15,
  ui::VKEY_F16,
  ui::VKEY_F17,
  ui::VKEY_F18,
  ui::VKEY_F19,
  ui::VKEY_F20,
  ui::VKEY_F21,
  ui::VKEY_F22,
  ui::VKEY_F23,
  ui::VKEY_F24,
  ui::VKEY_NUMLOCK,
  ui::VKEY_SCROLL,
  ui::VKEY_LSHIFT,
  ui::VKEY_RSHIFT,
  ui::VKEY_LCONTROL,
  ui::VKEY_RCONTROL,
  ui::VKEY_LMENU,
  ui::VKEY_RMENU,
  ui::VKEY_BROWSER_BACK,
  ui::VKEY_BROWSER_FORWARD,
  ui::VKEY_BROWSER_REFRESH,
  ui::VKEY_BROWSER_STOP,
  ui::VKEY_BROWSER_SEARCH,
  ui::VKEY_BROWSER_FAVORITES,
  ui::VKEY_BROWSER_HOME,
  ui::VKEY_VOLUME_MUTE,
  ui::VKEY_VOLUME_DOWN,
  ui::VKEY_VOLUME_UP,
  ui::VKEY_MEDIA_NEXT_TRACK,
  ui::VKEY_MEDIA_PREV_TRACK,
  ui::VKEY_MEDIA_STOP,
  ui::VKEY_MEDIA_PLAY_PAUSE,
  ui::VKEY_MEDIA_LAUNCH_MAIL,
  ui::VKEY_MEDIA_LAUNCH_MEDIA_SELECT,
  ui::VKEY_MEDIA_LAUNCH_APP1,
  ui::VKEY_MEDIA_LAUNCH_APP2,
  ui::VKEY_OEM_1,
  ui::VKEY_OEM_PLUS,
  ui::VKEY_OEM_COMMA,
  ui::VKEY_OEM_MINUS,
  ui::VKEY_OEM_PERIOD,
  ui::VKEY_OEM_2,
  ui::VKEY_OEM_3,
  ui::VKEY_OEM_4,
  ui::VKEY_OEM_5,
  ui::VKEY_OEM_6,
  ui::VKEY_OEM_7,
  ui::VKEY_OEM_8,
  ui::VKEY_OEM_102,
  ui::VKEY_PROCESSKEY,
  ui::VKEY_PACKET,
  ui::VKEY_DBE_SBCSCHAR,
  ui::VKEY_DBE_DBCSCHAR,
  ui::VKEY_ATTN,
  ui::VKEY_CRSEL,
  ui::VKEY_EXSEL,
  ui::VKEY_EREOF,
  ui::VKEY_PLAY,
  ui::VKEY_ZOOM,
  ui::VKEY_NONAME,
  ui::VKEY_PA1,
  ui::VKEY_OEM_CLEAR
};

} // namespace api

#endif // CONTENT_NW_SRC_API_KEYCODES_H_
