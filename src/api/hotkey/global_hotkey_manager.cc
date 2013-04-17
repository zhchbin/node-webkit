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

#include "content/nw/src/api/dispatcher_host.h"
#include "content/public/browser/browser_thread.h"
#include "ui/base/accelerators/accelerator.h"

using content::BrowserThread;

namespace api {

// static
GlobalHotKeyManager* GlobalHotKeyManager::GetInstance() {
  return Singleton<GlobalHotKeyManager>::get();
}

void GlobalHotKeyManager::AddHotKeyObject(HotKey* hot_key, int object_id) {
  hot_key_objects_registry_.AddWithID(hot_key, object_id);
}

void GlobalHotKeyManager::RemoveHotKeyObject(int object_id) {
  hot_key_objects_registry_.Remove(object_id);
  Unregister(object_id);
}

void GlobalHotKeyManager::RemoveHotKeyObjectByDispatcherHost(
    const DispatcherHost* dispatcher_host) {
  IDMap<HotKey, IDMapOwnPointer>::const_iterator iter(
      &hot_key_objects_registry_);
  for (; !iter.IsAtEnd(); iter.Advance())
    if (iter.GetCurrentValue()->dispatcher_host() == dispatcher_host)
      RemoveHotKeyObject(iter.GetCurrentKey());
}

HotKey* GlobalHotKeyManager::GetHotKeyObject(int object_id) {
  return hot_key_objects_registry_.Lookup(object_id);
}

void GlobalHotKeyManager::OnHotKeyActivated(int object_id) {
  HotKey* hot_key = GetHotKeyObject(object_id);
  if (hot_key != NULL)
    hot_key->OnActivated();
}

}  // namespace api
