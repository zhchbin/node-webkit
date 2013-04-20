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

#include "content/nw/src/api/hotkey/hotkey_handler.h"

#include "content/nw/src/api/hotkey/global_hotkey_manager.h"
#include "ui/base/accelerators/accelerator.h"
#include "ui/gfx/rect.h"

namespace api {

HotKeyHandler::HotKeyHandler() {
  set_window_style(WS_POPUP);
  Init(NULL, gfx::Rect());
}

HotKeyHandler::~HotKeyHandler() {
  for (std::map<HotkeyItem, int>::iterator it = valid_hotkeys_.begin();
       it != valid_hotkeys_.end(); it++) {
    UnregisterHotKey(hwnd(), it->second);
  }
  DestroyWindow(hwnd());
}

bool HotKeyHandler::add_hot_key(const ui::Accelerator& accelerator,
                                int object_id) {
  uint32 modifiers = GetNativeModifiers(accelerator);
  uint32 vkey = accelerator.key_code();
  if (RegisterHotKey(hwnd(), object_id, modifiers, vkey) == TRUE) {
    HotkeyItem item(modifiers, vkey);
    valid_hotkeys_[item] = object_id;
    return true;
  } else {
    return false;
  }
}
void HotKeyHandler::remove_hot_key(int object_id) {
  std::map<HotkeyItem, int>::iterator it;
  for (it = valid_hotkeys_.begin(); it != valid_hotkeys_.end(); it++) {
    if (it->second == object_id)
      break;
  }
  if (it == valid_hotkeys_.end())
    return;

  UnregisterHotKey(hwnd(), it->second);
  valid_hotkeys_.erase(it);
}

uint32 HotKeyHandler::GetNativeModifiers(const ui::Accelerator& accelerator) {
  uint8 native_modifiers = 0;
  if (accelerator.IsShiftDown())
    native_modifiers |= MOD_SHIFT;
  if (accelerator.IsCtrlDown())
    native_modifiers |= MOD_CONTROL;
  if (accelerator.IsAltDown())
    native_modifiers |= MOD_ALT;

  // Note: Changes the hotkey behavior so that the keyboard auto-repeat does
  //       not yield multiple hotkey notifications.
  //       Windows Vista and Windows XP/2000:  This flag is not supported.
  native_modifiers |= MOD_NOREPEAT;

  return native_modifiers;
}

LRESULT HotKeyHandler::OnHotKey(UINT uMsg, WPARAM wParam,
                                LPARAM lParam, BOOL& bHandled) {
  int id = static_cast<int>(wParam);
  for (std::map<HotkeyItem, int>::iterator it = valid_hotkeys_.begin();
       it != valid_hotkeys_.end(); it++)
    if (it->second == id)
      GlobalHotKeyManager::GetInstance()->OnHotKeyActivated(id);

  return TRUE;
}

}  // namespace api
