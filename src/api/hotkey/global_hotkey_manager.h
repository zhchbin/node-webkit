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

#ifndef CONTENT_NW_SRC_API_HOTKEY_GLOBAL_HOTKEY_MANAGER_H_
#define CONTENT_NW_SRC_API_HOTKEY_GLOBAL_HOTKEY_MANAGER_H_

#include "base/id_map.h"
#include "base/memory/singleton.h"
#include "base/memory/scoped_ptr.h"
#include "content/nw/src/api/hotkey/hotkey.h"

namespace ui {
class Accelerator;
}  // namespace ui

namespace api {

class DispatcherHost;
class HotKeyHandler;

class GlobalHotKeyManager {
 public:
  static GlobalHotKeyManager* GetInstance();

  virtual ~GlobalHotKeyManager();

  void Register(int object_id);
  void Unregister(int object_id);

  void AddHotKeyObject(HotKey* hotkey, int object_id);
  void RemoveHotKeyObject(int object_id);
  void RemoveHotKeyObjectByDispatcherHost(
     const DispatcherHost *dispatcher_host);

  void OnHotKeyActivated(int object_id);

 private:
  GlobalHotKeyManager();
  friend struct DefaultSingletonTraits<GlobalHotKeyManager>;

  HotKey* GetHotKeyObject(int object_id);

  IDMap<HotKey, IDMapOwnPointer> hot_key_objects_registry_;
  scoped_ptr<HotKeyHandler> hot_key_handler_;

  DISALLOW_COPY_AND_ASSIGN(GlobalHotKeyManager);
};

}  // namespace api

#endif  // CONTENT_NW_SRC_API_HOTKEY_GLOBAL_HOTKEY_MANAGER_H_
