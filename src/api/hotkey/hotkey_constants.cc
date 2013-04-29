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

#include "content/nw/src/api/hotkey/hotkey_constants.h"

namespace hotkey_errors {
const char kInvalidKeyBinding[] =
     "Invalid value for 'hotkey[*] on *': *.";

const char kInvalidKeyBindingUnknownPlatform[] =
    "Unknown platform for 'hotkey[*]': *. Valid values are: 'windows', 'mac'"
    " 'linux' and 'default'.";

const char kRegisterHotkeyFailed[] =
    "Register global hot key failed, maybe it has been registered.";
}  // namespace hotkey_errors

namespace hotkey_values {
const char kKeybindingPlatformDefault[] = "default";
const char kKeybindingPlatformLinux[] = "linux";
const char kKeybindingPlatformMac[] = "mac";
const char kKeybindingPlatformWin[] = "windows";
}  // namespace hotkey_values

namespace hotkey_modifiers {
const char kCtrl[] = "CTRL";
const char kAlt[] = "ALT";
const char kCommand[] = "COMMAND";
const char kShift[] = "SHIFT";
}  // namespace hotkey_modifiers
