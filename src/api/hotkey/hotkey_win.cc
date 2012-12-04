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

#include "content/nw/src/api/hotkey/hotkey.h"

#include "base/memory/singleton.h"
#include "content/nw/src/api/app/app.h"
#include "content/nw/src/api/keycodes.h"
#include "ui/base/win/window_impl.h"
#include "ui/gfx/rect.h"

#include <algorithm>
#include <map>

namespace api {

class HotkeySingleton : public ui::WindowImpl {
 public:
  ~HotkeySingleton() {
    std::map<HotkeyItem, uint32>::iterator it; 
    for (it = hotkeyItems_.begin(); it != hotkeyItems_.end(); it++) {
      UnregisterHotKey(hwnd(), it->second);
    }
    DestroyWindow(hwnd()); 
  }

  static HotkeySingleton* GetInstance() {
    return Singleton<HotkeySingleton>::get(); 
  }
  
  bool Register(const HotkeyItem& item) {
    // check the item modifiers range
    if (item.modifiers_ < kModifiersRnageMin 
        || item.modifiers_ > kModifiersRnageMax) {
      return false; 
    }
    
    // check whether the keyCode is valid
    if (item.keyCode_ < 0 || item.keyCode_ >= arraysize(kKeyboardCodesMap)) {
      return false;
    }

    uint8 modifiers = GetNativeModifiers(item.modifiers_);
    uint8 keyCode = kKeyboardCodesMap[item.keyCode_];

    int sizeOfHotkeyItems = hotkeyItems_.size();
    // use index as hotkey id
    if (RegisterHotKey(hwnd(), sizeOfHotkeyItems, modifiers, keyCode) == TRUE) {
      hotkeyItems_[item] = sizeOfHotkeyItems; 
      return true;
    } else {
      return false;
    }
  }

  void Unregister(const HotkeyItem& item) {
    std::map<HotkeyItem, uint32>::iterator it; 
    it = hotkeyItems_.find(item);
    if (it != hotkeyItems_.end()) {
      UnregisterHotKey(hwnd(), it->second);
      hotkeyItems_.erase(it);
    }
  }
 
  BEGIN_MSG_MAP_EX(HotKeyHandler)
    MESSAGE_HANDLER(WM_HOTKEY, OnHotKey)
  END_MSG_MAP()

 private:
  HotkeySingleton() {
    set_window_style(WS_POPUP);
    Init(NULL, gfx::Rect());
  }
  DISALLOW_COPY_AND_ASSIGN(HotkeySingleton);

  friend struct DefaultSingletonTraits<HotkeySingleton>;

  uint8 GetNativeModifiers(uint32 modifiers) {
    uint8 nativeModifiers = 0;
    if (modifiers & kModifiersAlt) 
      nativeModifiers |= MOD_ALT;
    if (modifiers & kModifiersCtrl) 
      nativeModifiers |= MOD_CONTROL;
    if (modifiers & kModifiersMeta)
      nativeModifiers |= MOD_WIN;
    if (modifiers & kModifiersShirt) 
      nativeModifiers |= MOD_SHIFT;
    
    // Note: Changes the hotkey behavior so that the keyboard auto-repeat does 
    //       not yield multiple hotkey notifications.
    //       Windows Vista and Windows XP/2000:  This flag is not supported.
    nativeModifiers |= MOD_NOREPEAT;

    return nativeModifiers;
  }

  // Handle the registered Hotkey being pressed.
  virtual LRESULT OnHotKey(UINT uMsg, WPARAM wParam,
                           LPARAM lParam, BOOL& bHandled) {
    uint32 hotkeyId = (uint32)wParam;
    std::map<HotkeyItem, uint32>::iterator it;
    for (it = hotkeyItems_.begin(); it != hotkeyItems_.end(); it++) {
      if (it->second == hotkeyId) {
        Hotkey::OnHotkeyActivated(it->first); 
        break;
      }
    }
    return 1;
  }

  std::map<HotkeyItem, uint32> hotkeyItems_;
};

// static 
bool Hotkey::RegisterHotkey(const HotkeyItem& item) {
  return HotkeySingleton::GetInstance()->Register(item);
}

// static
void Hotkey::UnregisterHotkey(const HotkeyItem& item) {
  HotkeySingleton::GetInstance()->Unregister(item);
}

void Hotkey::OnHotkeyActivated(const HotkeyItem& item) {
  App::EmitGlobalHotkeyActivatedEvent(item.keyCode_, item.modifiers_);  
}

} // namespace api
