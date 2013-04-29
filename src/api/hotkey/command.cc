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

#include "content/nw/src/api/hotkey/command.h"

#include <vector>

#include "base/logging.h"
#include "base/string_util.h"
#include "base/strings/string_number_conversions.h"
#include "base/strings/string_split.h"
#include "content/nw/src/api/hotkey/hotkey_constants.h"
#include "extensions/common/error_utils.h"
#include "ui/base/accelerators/accelerator.h"

namespace errors = hotkey_errors;
namespace values = hotkey_values;
namespace modifiers = hotkey_modifiers;

using extensions::ErrorUtils;

namespace {

static const char kMissing[] = "Missing";

static const char kCommandKeyNotSupported[] =
    "Command key is not supported. Note: Ctrl means Command on Mac";


ui::Accelerator ParseImpl(const std::string& accelerator,
                          const std::string& platform_key,
                          int index,
                          std::string* error) {
  std::string upper_accelerator = StringToUpperASCII(accelerator);
  if (platform_key != values::kKeybindingPlatformWin &&
      platform_key != values::kKeybindingPlatformMac &&
      platform_key != values::kKeybindingPlatformLinux &&
      platform_key != values::kKeybindingPlatformDefault) {
    *error = ErrorUtils::FormatErrorMessage(
        errors::kInvalidKeyBindingUnknownPlatform,
        base::IntToString(index),
        platform_key);
    return ui::Accelerator();
  }

  std::vector<std::string> tokens;
  base::SplitString(upper_accelerator, '+', &tokens);
  if (tokens.size() < 2 || tokens.size() > 3) {
    *error = ErrorUtils::FormatErrorMessage(
        errors::kInvalidKeyBinding,
        base::IntToString(index),
        platform_key,
        upper_accelerator);
    return ui::Accelerator();
  }

  // Now, parse it into an accelerator.
  int modifiers = ui::EF_NONE;
  ui::KeyboardCode key = ui::VKEY_UNKNOWN;
  for (size_t i = 0; i < tokens.size(); i++) {
    if (tokens[i] == modifiers::kCtrl) {
      modifiers |= ui::EF_CONTROL_DOWN;
    } else if (tokens[i] == modifiers::kCommand) {
      if (platform_key == "mac") {
        // Either the developer specified Command+foo in the manifest for Mac or
        // they specified Ctrl and it got normalized to Command (to get Ctrl on
        // Mac the developer has to specify MacCtrl). Therefore we treat this
        // as Command.
        modifiers |= ui::EF_COMMAND_DOWN;
#if defined(OS_MACOSX)
      } else if (platform_key == "default") {
        // If we see "Command+foo" in the Default section it can mean two
        // things, depending on the platform:
        // The developer specified "Ctrl+foo" for Default and it got normalized
        // on Mac to "Command+foo". This is fine. Treat it as Command.
        modifiers |= ui::EF_COMMAND_DOWN;
#endif
      } else {
        // No other platform supports Command.
        key = ui::VKEY_UNKNOWN;
        break;
      }
    } else if (tokens[i] == modifiers::kAlt) {
      modifiers |= ui::EF_ALT_DOWN;
    } else if (tokens[i] == modifiers::kShift) {
      modifiers |= ui::EF_SHIFT_DOWN;
    } else if (tokens[i].size() == 1) {
      if (key != ui::VKEY_UNKNOWN) {
        // Multiple key assignments.
        key = ui::VKEY_UNKNOWN;
        break;
      }
      if (tokens[i][0] >= 'A' && tokens[i][0] <= 'Z') {
        key = static_cast<ui::KeyboardCode>(ui::VKEY_A + (tokens[i][0] - 'A'));
      } else if (tokens[i][0] >= '0' && tokens[i][0] <= '9') {
        key = static_cast<ui::KeyboardCode>(ui::VKEY_0 + (tokens[i][0] - '0'));
      } else {
        key = ui::VKEY_UNKNOWN;
        break;
      }
    } else {
      *error = ErrorUtils::FormatErrorMessage(
          errors::kInvalidKeyBinding,
          base::IntToString(index),
          platform_key,
          upper_accelerator);
      return ui::Accelerator();
    }
  }
  bool command = (modifiers & ui::EF_COMMAND_DOWN) != 0;
  bool ctrl = (modifiers & ui::EF_CONTROL_DOWN) != 0;
  bool alt = (modifiers & ui::EF_ALT_DOWN) != 0;
  bool shift = (modifiers & ui::EF_SHIFT_DOWN) != 0;

  // We support Ctrl+foo, Alt+foo, Ctrl+Shift+foo, Alt+Shift+foo, Ctrl+Alt+foo,
  // but not Shift+foo.
  // In the chromium upstream code, it don't support Ctrl+Alt+foo. For a more
  // detailed reason why they don't support Ctrl+Alt+foo see this article:
  // http://blogs.msdn.com/b/oldnewthing/archive/2004/03/29/101121.aspx.
  // However, I(zhchbin) think we can support this, because it can be the duty
  // of the application developer to choose which kind he used.
  // On Mac Command can also be used in combination with Shift or on its own,
  // as a modifier.
  if (key == ui::VKEY_UNKNOWN || (shift && !ctrl && !alt && !command)) {
    *error = ErrorUtils::FormatErrorMessage(
        errors::kInvalidKeyBinding,
        base::IntToString(index),
        platform_key,
        upper_accelerator);
    return ui::Accelerator();
  }

  return ui::Accelerator(key, modifiers);
}

}  // namespace

namespace api {

Command::Command(const std::string& accelerator) {
  accelerator_ = ParseImpl(accelerator, CommandPlatform(), 0, &error_);
}

Command::~Command() {}

// static
std::string Command::CommandPlatform() {
#if defined(OS_WIN)
  return values::kKeybindingPlatformWin;
#elif defined(OS_MACOSX)
  return values::kKeybindingPlatformMac;
#elif defined(OS_LINUX)
  return values::kKeybindingPlatformLinux;
#else
  return "";
#endif
}

// static
ui::Accelerator Command::StringToAccelerator(const std::string& accelerator) {
  std::string error;
  ui::Accelerator parsed =
      ParseImpl(accelerator, Command::CommandPlatform(), 0, &error);
  return parsed;
}

}  // namespace extensions

