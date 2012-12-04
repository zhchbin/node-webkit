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

var KEYCODE_RANGE = {min: 0, max: 169};
var MODIFIERS_RANGE = {min: 1, max: 15};

var v8_util = process.binding('v8_util');

function Hotkey(keyCode, modifiers) {
  function isInteger(value) {
    return typeof value === 'number'
           && !isNaN(value) 
           && parseFloat(value) == parseInt(value, 10);
  }

  if (typeof keyCode == 'undefined' || typeof modifiers == 'undefined')
    throw new TypeError("Illegal constructor, should specify keyCode and \
          modifiers.");
  // check whether the keyCode is valid
  if (!isInteger(keyCode)) {
    throw new TypeError("Illegal constructor, keyCode should be a integer.");
  } else if (keyCode < KEYCODE_RANGE.min || keyCode > KEYCODE_RANGE.max) {
    throw new TypeError('Illegal constructor, keyCode value error.');
  }

  if (!isInteger(modifiers)) {
    throw new TypeError('Illegal constructor, modifiers should be a integer.');
  } else if (modifiers < MODIFIERS_RANGE.min 
             || modifiers > MODIFIERS_RANGE.max) {
    throw new TypeError('Illegal constructor, modifiers value error.');  
  }
  
  this.keyCode = keyCode;
  this.modifiers = modifiers;
}

Hotkey.prototype.__defineSetter__('activated', function(fun) {
  if (typeof fun != 'function') 
    throw new TypeError(JSON.stringify(fun) + " isn't a valid function.");

  v8_util.setHiddenValue(this, 'OnGlobalHotkeyActivated', fun);
});

Hotkey.prototype.__defineGetter__('activated', function() {
  return v8_util.getHiddenValue(this, 'OnGlobalHotkeyActivated');
});

Hotkey.prototype.__defineSetter__('error', function(fun) {
  if (typeof fun != 'function') 
    throw new TypeError(JSON.stringify(fun) + " isn't a valid function.");

  v8_util.setHiddenValue(this, 'OnRegisterGlobalHotkeyError', fun);
});

Hotkey.prototype.__defineGetter__('error', function() {
  return v8_util.getHiddenValue(this, 'OnRegisterGlobalHotkeyError');
});

// modifiers
Hotkey.Alt = 1;
Hotkey.Ctrl = 1 << 1;
Hotkey.Meta = 1 << 2;
Hotkey.Shift = 1 << 3;

// key codes 
// Note: The value is the index of the kKeyboardCodesMap of the file
//       |keycodes.h|. If you want to change the value, please make sure the
//       squenece is corresponding.
Hotkey.VKEY_BACK = 0;
Hotkey.VKEY_TAB = 1;
Hotkey.VKEY_BACKTAB = 2;  // Note: windows doesn't have this virtual key.
Hotkey.VKEY_CLEAR = 3;
Hotkey.VKEY_RETURN = 4;
Hotkey.VKEY_SHIFT = 5;
Hotkey.VKEY_CONTROL = 6;
Hotkey.VKEY_MENU = 7;
Hotkey.VKEY_PAUSE = 8;
Hotkey.VKEY_CAPITAL = 9;
Hotkey.VKEY_KANA = 10;
Hotkey.VKEY_HANGUL = 11;
Hotkey.VKEY_JUNJA = 12;
Hotkey.VKEY_FINAL = 13;
Hotkey.VKEY_HANJA = 14;
Hotkey.VKEY_KANJI = 15;
Hotkey.VKEY_ESCAPE = 16;
Hotkey.VKEY_CONVERT = 17;
Hotkey.VKEY_NONCONVERT = 18;
Hotkey.VKEY_ACCEPT = 19;
Hotkey.VKEY_MODECHANGE = 20;
Hotkey.VKEY_SPACE = 21;
Hotkey.VKEY_PRIOR = 22;
Hotkey.VKEY_NEXT = 23;
Hotkey.VKEY_END = 24;
Hotkey.VKEY_HOME = 25;
Hotkey.VKEY_LEFT = 26;
Hotkey.VKEY_UP = 27;
Hotkey.VKEY_RIGHT = 28;
Hotkey.VKEY_DOWN = 29;
Hotkey.VKEY_SELECT = 30;
Hotkey.VKEY_PRINT = 31;
Hotkey.VKEY_EXECUTE = 32;
Hotkey.VKEY_SNAPSHOT = 33;
Hotkey.VKEY_INSERT = 34;
Hotkey.VKEY_DELETE = 35;
Hotkey.VKEY_HELP = 36;
Hotkey.VKEY_0 = 37;
Hotkey.VKEY_1 = 38;
Hotkey.VKEY_2 = 39;
Hotkey.VKEY_3 = 40;
Hotkey.VKEY_4 = 41;
Hotkey.VKEY_5 = 42;
Hotkey.VKEY_6 = 43;
Hotkey.VKEY_7 = 44;
Hotkey.VKEY_8 = 45;
Hotkey.VKEY_9 = 46;
Hotkey.VKEY_A = 47;
Hotkey.VKEY_B = 48;
Hotkey.VKEY_C = 49;
Hotkey.VKEY_D = 50;
Hotkey.VKEY_E = 51;
Hotkey.VKEY_F = 52;
Hotkey.VKEY_G = 53;
Hotkey.VKEY_H = 54;
Hotkey.VKEY_I = 55;
Hotkey.VKEY_J = 56;
Hotkey.VKEY_K = 57;
Hotkey.VKEY_L = 58;
Hotkey.VKEY_M = 59;
Hotkey.VKEY_N = 60;
Hotkey.VKEY_O = 61;
Hotkey.VKEY_P = 62;
Hotkey.VKEY_Q = 63;
Hotkey.VKEY_R = 64;
Hotkey.VKEY_S = 65;
Hotkey.VKEY_T = 66;
Hotkey.VKEY_U = 67;
Hotkey.VKEY_V = 68;
Hotkey.VKEY_W = 69;
Hotkey.VKEY_X = 70;
Hotkey.VKEY_Y = 71;
Hotkey.VKEY_Z = 72;
Hotkey.VKEY_LWIN = 73;
Hotkey.VKEY_COMMAND = 74;
Hotkey.VKEY_RWIN = 75;
Hotkey.VKEY_APPS = 76;
Hotkey.VKEY_SLEEP = 77;
Hotkey.VKEY_NUMPAD0 = 78;
Hotkey.VKEY_NUMPAD1 = 79;
Hotkey.VKEY_NUMPAD2 = 80;
Hotkey.VKEY_NUMPAD3 = 81;
Hotkey.VKEY_NUMPAD4 = 82;
Hotkey.VKEY_NUMPAD5 = 83;
Hotkey.VKEY_NUMPAD6 = 84;
Hotkey.VKEY_NUMPAD7 = 85;
Hotkey.VKEY_NUMPAD8 = 86;
Hotkey.VKEY_NUMPAD9 = 87;
Hotkey.VKEY_MULTIPLY = 88;
Hotkey.VKEY_ADD = 89;
Hotkey.VKEY_SEPARATOR = 90;
Hotkey.VKEY_SUBTRACT = 91;
Hotkey.VKEY_DECIMAL = 92;
Hotkey.VKEY_DIVIDE = 93;
Hotkey.VKEY_F1 = 94;
Hotkey.VKEY_F2 = 95;
Hotkey.VKEY_F3 = 96;
Hotkey.VKEY_F4 = 97;
Hotkey.VKEY_F5 = 98;
Hotkey.VKEY_F6 = 99;
Hotkey.VKEY_F7 = 100;
Hotkey.VKEY_F8 = 101;
Hotkey.VKEY_F9 = 102;
Hotkey.VKEY_F10 = 103;
Hotkey.VKEY_F11 = 104;
Hotkey.VKEY_F12 = 105;
Hotkey.VKEY_F13 = 106;
Hotkey.VKEY_F14 = 107;
Hotkey.VKEY_F15 = 108;
Hotkey.VKEY_F16 = 109;
Hotkey.VKEY_F17 = 110;
Hotkey.VKEY_F18 = 111;
Hotkey.VKEY_F19 = 112;
Hotkey.VKEY_F20 = 113;
Hotkey.VKEY_F21 = 114;
Hotkey.VKEY_F22 = 115;
Hotkey.VKEY_F23 = 116;
Hotkey.VKEY_F24 = 117;
Hotkey.VKEY_NUMLOCK = 118;
Hotkey.VKEY_SCROLL = 119;
Hotkey.VKEY_LSHIFT = 120;
Hotkey.VKEY_RSHIFT = 121;
Hotkey.VKEY_LCONTROL = 122;
Hotkey.VKEY_RCONTROL = 123;
Hotkey.VKEY_LMENU = 124;
Hotkey.VKEY_RMENU = 125;
Hotkey.VKEY_BROWSER_BACK = 126;
Hotkey.VKEY_BROWSER_FORWARD = 127;
Hotkey.VKEY_BROWSER_REFRESH = 128;
Hotkey.VKEY_BROWSER_STOP = 129;
Hotkey.VKEY_BROWSER_SEARCH = 130;
Hotkey.VKEY_BROWSER_FAVORITES = 131;
Hotkey.VKEY_BROWSER_HOME = 132;
Hotkey.VKEY_VOLUME_MUTE = 133;
Hotkey.VKEY_VOLUME_DOWN = 134;
Hotkey.VKEY_VOLUME_UP = 135;
Hotkey.VKEY_MEDIA_NEXT_TRACK = 136;
Hotkey.VKEY_MEDIA_PREV_TRACK = 137;
Hotkey.VKEY_MEDIA_STOP = 138;
Hotkey.VKEY_MEDIA_PLAY_PAUSE = 139;
Hotkey.VKEY_MEDIA_LAUNCH_MAIL = 140;
Hotkey.VKEY_MEDIA_LAUNCH_MEDIA_SELECT = 141;
Hotkey.VKEY_MEDIA_LAUNCH_APP1 = 142;
Hotkey.VKEY_MEDIA_LAUNCH_APP2 = 143;
Hotkey.VKEY_OEM_1 = 144;
Hotkey.VKEY_OEM_PLUS = 145;
Hotkey.VKEY_OEM_COMMA = 146;
Hotkey.VKEY_OEM_MINUS = 147;
Hotkey.VKEY_OEM_PERIOD = 148;
Hotkey.VKEY_OEM_2 = 149;
Hotkey.VKEY_OEM_3 = 150;
Hotkey.VKEY_OEM_4 = 151;
Hotkey.VKEY_OEM_5 = 152;
Hotkey.VKEY_OEM_6 = 153;
Hotkey.VKEY_OEM_7 = 154;
Hotkey.VKEY_OEM_8 = 155;
Hotkey.VKEY_OEM_102 = 156;
Hotkey.VKEY_PROCESSKEY = 157;
Hotkey.VKEY_PACKET = 158;
Hotkey.VKEY_DBE_SBCSCHAR = 159;
Hotkey.VKEY_DBE_DBCSCHAR = 160;
Hotkey.VKEY_ATTN = 161;
Hotkey.VKEY_CRSEL = 162;
Hotkey.VKEY_EXSEL = 163;
Hotkey.VKEY_EREOF = 164;
Hotkey.VKEY_PLAY = 165;
Hotkey.VKEY_ZOOM = 166;
Hotkey.VKEY_NONAME = 167;
Hotkey.VKEY_PA1 = 168;
Hotkey.VKEY_OEM_CLEAR = 169;

Object.freeze(Hotkey);

require('util').inherits(Hotkey, exports.Base);
exports.Hotkey = Hotkey;
