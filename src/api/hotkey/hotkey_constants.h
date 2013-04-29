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

#ifndef CONTENT_NW_SRC_API_HOTKEY_HOTKEY_CONSTANTS_H_
#define CONTENT_NW_SRC_API_HOTKEY_HOTKEY_CONSTANTS_H_

namespace hotkey_errors {
  extern const char kInvalidKeyBinding[];
  extern const char kInvalidKeyBindingUnknownPlatform[];
  extern const char kRegisterHotkeyFailed[];
}  // namespace hotkey_errors

namespace hotkey_values {
  extern const char kKeybindingPlatformDefault[];
  extern const char kKeybindingPlatformLinux[];
  extern const char kKeybindingPlatformMac[];
  extern const char kKeybindingPlatformWin[];
}  // namespace hotkey_values

namespace hotkey_modifiers {
  extern const char kCtrl[];
  extern const char kAlt[];
  extern const char kCommand[];
  extern const char kShift[];
}  // namespace hotkey_modifiers

#endif  // CONTENT_NW_SRC_API_HOTKEY_HOTKEY_CONSTANTS_H_

