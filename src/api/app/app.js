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

var argv;

function App() {
  this.hotkeys = new Array();

  this.on('registerGlobalHotkeyError', function(keyCode, modifiers) {
    for (var i = this.hotkeys.length - 1; i >= 0; i--) {
      if (this.hotkeys[i].keyCode == keyCode
          && this.hotkeys[i].modifiers == modifiers) {
        if (typeof this.hotkeys[i].error == 'function') {
          this.hotkeys[i].error("Register Global Hotkey Error.");
        }
        this.hotkeys.splice(i, 1);
        break;
      }
    }
  });

  this.on('globalHotkeyActivated', function(keyCode, modifiers) {
    for (var i = this.hotkeys.length - 1; i >= 0; i--) {
      if (this.hotkeys[i].keyCode == keyCode
          && this.hotkeys[i].modifiers == modifiers) {
        if (typeof this.hotkeys[i].activated == 'function') {
          this.hotkeys[i].activated(this.hotkeys[i]);
        }
      }
    }
  });
}
require('util').inherits(App, exports.Base);

App.prototype.quit = function() {
  nw.callStaticMethod('App', 'Quit', [ ]);
}

App.prototype.closeAllWindows = function() {
  nw.callStaticMethod('App', 'CloseAllWindows', [ ]);
}

App.prototype.registerGlobalHotkey = function(hotkey) {
  if (typeof hotkey == 'undefined')
    throw new TypeError('Invalid hotkey.');

  if (hotkey.constructor.name != 'Hotkey')
    throw new TypeError('Invalid hotkey: ' + JSON.stringify(hotkey) + '.');

  this.hotkeys.push(hotkey);
  nw.callStaticMethod('App', 'RegisterGlobalHotkey',
                      [hotkey.keyCode, hotkey.modifiers]);
}

App.prototype.unregisterGlobalHotkey = function(hotkey) {
  if (typeof hotkey == 'undefined')
    throw new TypeError('Invalid hotkey.');

  if (hotkey.constructor.name != 'Hotkey')
    throw new TypeError('Invalid hotkey: ' + JSON.stringify(hotkey) + '.');
  for (var i = this.hotkeys.length - 1; i >= 0; i--) {
    if (this.hotkeys[i].keyCode == hotkey.keyCode
          && this.hotkeys[i].modifiers == hotkey.modifiers) {
      nw.callStaticMethod('App', 'UnregisterGlobalHotkey',
                          [hotkey.keyCode, hotkey.modifiers]);
      this.hotkeys.splice(i, 1);
    }
  }
}

App.prototype.__defineGetter__('argv', function() {
  if (!argv)
    argv = nw.callStaticMethodSync('App', 'GetArgv', [ ]);

  return argv;
});

// Store App object in node's context.
if (process['_nw_app']) {
  exports.App = process['_nw_app'];
} else {
  exports.App = process['_nw_app'] = new App();
}
