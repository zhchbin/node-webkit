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

#ifndef CONTENT_NW_SRC_API_HOTKEY_HOTKEY_HANDLER_H_
#define CONTENT_NW_SRC_API_HOTKEY_HOTKEY_HANDLER_H_

#include <map>

#include "base/basictypes.h"

#if defined(OS_WIN)
#include "ui/base/win/window_impl.h"
#elif defined(OS_LINUX)
#include <gtk/gtk.h>
#include <gdk/gdkx.h>
#include <X11/Xlib.h>

#include "ui/base/gtk/gtk_signal.h"
#endif

namespace ui {
class Accelerator;
}  // namespace ui

namespace api {

#if defined(OS_WIN)
class HotKeyHandler : public ui::WindowImpl {
#else 
class HotKeyHandler {
#endif
 public:
  typedef std::pair<uint32, uint32> HotkeyItem;

  HotKeyHandler();
  ~HotKeyHandler();

  bool add_hot_key(const ui::Accelerator& accelerator, int object_id);
  void remove_hot_key(int object_id);

 private:
  uint32 GetNativeModifiers(const ui::Accelerator& accelerator);
 
#if defined(OS_LINUX)
  CHROMEG_CALLBACK_1(HotKeyHandler, GdkFilterReturn, OnXEvent,
                     GdkXEvent*, GdkEvent*); 

  GdkWindow *root_win;
  Display* display;
  Window x_win;
#elif defined(OS_WIN)
  BEGIN_MSG_MAP_EX(HotKeyHandler)
    MESSAGE_HANDLER(WM_HOTKEY, OnHotKey)
  END_MSG_MAP()
  // Handle the registered Hotkey being activated.
  LRESULT OnHotKey(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
#endif

  std::map<HotkeyItem, int> valid_hotkeys_;
  DISALLOW_COPY_AND_ASSIGN(HotKeyHandler);
};

}  // namespace api

#endif  // CONTENT_NW_SRC_API_HOTKEY_HOTKEY_HANDLER_H_
