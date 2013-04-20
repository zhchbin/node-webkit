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

#include <string>

#include "base/logging.h"
#include "content/nw/src/api/hotkey/global_hotkey_manager.h"
#include "ui/base/accelerators/accelerator.h"

namespace api {

// This is used for ignore the lock modifiers.
static uint32 lock_modifiers[] = {
   0,
   Mod2Mask, // NUM_LOCK
   LockMask, // CAPS_LOCK
   Mod5Mask, // SCROLL_LOCK
   Mod2Mask | LockMask,
   Mod2Mask | Mod5Mask,
   LockMask | Mod5Mask,
   Mod2Mask | LockMask | Mod5Mask
};

HotKeyHandler::HotKeyHandler() 
    : root_win(gdk_get_default_root_window()),
      x_win(gdk_x11_get_default_root_xwindow()) {
  display = static_cast<Display*>(GDK_WINDOW_XDISPLAY(root_win));
  gdk_window_add_filter(root_win, &HotKeyHandler::OnXEventThunk, this);
}

HotKeyHandler::~HotKeyHandler() {
  std::map<HotkeyItem, int>::iterator it;
  for (it = valid_hotkeys_.begin(); it != valid_hotkeys_.end(); it++) {
    for (size_t i = 0; i < arraysize(lock_modifiers); ++i) {
      int modifiers = it->first.first;
      int keycode = it->first.second;
      XUngrabKey(display, keycode, modifiers | lock_modifiers[i], x_win);
    }
  }
}

bool HotKeyHandler::add_hot_key(const ui::Accelerator& accelerator,
                                int object_id) {
  uint32 modifiers = GetNativeModifiers(accelerator);
  int keycode = XKeysymToKeycode(display, accelerator.key_code());

  for (size_t index = 0; index < arraysize(lock_modifiers); ++index) {
    XGrabKey(display, keycode, modifiers | lock_modifiers[index],
             x_win, true, GrabModeAsync, GrabModeAsync);  
  }

  HotkeyItem item(modifiers, keycode);
  valid_hotkeys_[item] = object_id;
  return true;
}

void HotKeyHandler::remove_hot_key(int object_id) {
  std::map<HotkeyItem, int>::iterator it;
  for (it = valid_hotkeys_.begin(); it != valid_hotkeys_.end(); it++) {
    if (it->second == object_id)
      break;
  }
  if (it == valid_hotkeys_.end())
    return;
  
  for (size_t i = 0; i < arraysize(lock_modifiers); ++i) {
    int modifiers = it->first.first;
    int keycode = it->first.second;
    XUngrabKey(display, keycode, modifiers | lock_modifiers[i], x_win);
  }
  valid_hotkeys_.erase(it);
}

uint32 HotKeyHandler::GetNativeModifiers(const ui::Accelerator& accelerator) {
  uint32 native_modifiers = 0;
  if (accelerator.IsShiftDown())
    native_modifiers |= ShiftMask;
  if (accelerator.IsCtrlDown())
    native_modifiers |= ControlMask;
  if (accelerator.IsAltDown())
    native_modifiers |= Mod1Mask;
  
  return native_modifiers;
}

GdkFilterReturn HotKeyHandler::OnXEvent(GdkXEvent* xevent, GdkEvent* event) {
  XEvent* xev = static_cast<XEvent*>(xevent);

  if (xev->type == KeyPress) {
    // remove NumLock, CapsLock and ScrollLock from key state.
    uint32 modifiers = xev->xkey.state & ~(lock_modifiers[7]);
    HotkeyItem item(modifiers, xev->xkey.keycode);
    std::map<HotkeyItem, int>::iterator it = valid_hotkeys_.find(item);
    if (it != valid_hotkeys_.end())
      GlobalHotKeyManager::GetInstance()->OnHotKeyActivated(it->second);
  }

  return GDK_FILTER_CONTINUE;
}

}  // namespace api
