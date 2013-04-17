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

#include "content/nw/src/api/hotkey/global_hotkey_manager.h"

#include <map>
#include <string>

#include "base/logging.h"
#include "content/nw/src/api/hotkey/command.h"
#include "content/nw/src/api/hotkey/hotkey_constants.h"
#include "ui/base/accelerators/accelerator.h"
#include "ui/base/win/window_impl.h"
#include "ui/gfx/rect.h"

namespace api {

// HotKey handler.
// Programs wishing to register a hotkey can use this.
class HotKeyHandler : public ui::WindowImpl {
 public:
  typedef std::pair<uint32, uint32> HotkeyItem;

  HotKeyHandler() {
    set_window_style(WS_POPUP);
    Init(NULL, gfx::Rect());
  }

  ~HotKeyHandler() {
    for (std::map<HotkeyItem, int>::iterator it = valid_hotkeys_.begin();
         it != valid_hotkeys_.end(); it++) {
      UnregisterHotKey(hwnd(), it->second);
    }
    DestroyWindow(hwnd());
  }

  bool add_hot_key(uint32 modifiers, uint32 vkey, int object_id) {
    if (RegisterHotKey(hwnd(), object_id, modifiers, vkey) == TRUE) {
      HotkeyItem item(modifiers, vkey);
      valid_hotkeys_[item] = object_id;
      return true;
    } else {
      return false;
    }
  }

  void remove_hot_key(int object_id) {
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

  BEGIN_MSG_MAP_EX(HotKeyHandler)
    MESSAGE_HANDLER(WM_HOTKEY, OnHotKey)
  END_MSG_MAP()

 private:
  std::map<HotkeyItem, int> valid_hotkeys_;

  // Handle the registered Hotkey being activated.
  virtual LRESULT OnHotKey(UINT uMsg, WPARAM wParam,
                           LPARAM lParam, BOOL& bHandled) {
    int id = static_cast<int>(wParam);
    for (std::map<HotkeyItem, int>::iterator it = valid_hotkeys_.begin();
         it != valid_hotkeys_.end(); it++)
      if (it->second == id)
        GlobalHotKeyManager::GetInstance()->OnHotKeyActivated(id);

    return TRUE;
  }
};

GlobalHotKeyManager::GlobalHotKeyManager() {
}

GlobalHotKeyManager::~GlobalHotKeyManager() {
}

void GlobalHotKeyManager::Register(int object_id) {
  if (!hot_key_handler_.get())
    hot_key_handler_.reset(new HotKeyHandler);

  HotKey *hot_key = GetHotKeyObject(object_id);
  if (hot_key == NULL)
    return;
  const std::string& hotkey_str = hot_key->GetCombination();
  Command command(hotkey_str);
  if (command.get_error() != "") {
    hot_key->OnFailed(command.get_error());
    return;
  }

  const ui::Accelerator& accelerator = command.accelerator();
  uint8 native_modifiers = GetNativeModifiers(accelerator);
  bool is_add_success = hot_key_handler_->add_hot_key(native_modifiers,
                                                      accelerator.key_code(),
                                                      object_id);
  if (!is_add_success) {
    hot_key->OnFailed(hotkey_errors::kRegisterHotkeyFailed);
    return;
  }
}

void GlobalHotKeyManager::Unregister(int object_id) {
  hot_key_handler_->remove_hot_key(object_id);
}

uint8 GlobalHotKeyManager::GetNativeModifiers(
    const ui::Accelerator& accelerator) {
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

}  // namespace api
