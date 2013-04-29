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

var v8_util = process.binding('v8_util');

function HotKey(option) {
  if (typeof option != 'object')
    throw new TypeError('Invalid option.');

  if (!option.hasOwnProperty('key')) {
    throw new TypeError("A normal hotkey must have a 'key', which specifies \
                        the combinations of keys, like 'Ctrl+Alt+S'.");
  } else {
    option.key = String(option.key);
    this.key = option.key;
  }

  if (option.hasOwnProperty('keydown')) {
    if (typeof option.keydown != 'function')
      throw new TypeError("'keydown' must be a valid function.");
    else
      this.keydown = option.keydown;
  }

  if (option.hasOwnProperty('keyup')) {
    if (typeof option.keyup != 'function')
      throw new TypeError("'keyup' must be a valid function.");
    else
      this.keyup = option.keyup;
  }

  if (option.hasOwnProperty('failed')) {
    if (typeof option.failed != 'function')
      throw new TypeError("'failed' must be a valid function.");
    else
      this.failed = option.failed;
  }

  v8_util.setHiddenValue(this, 'option', option);
  nw.allocateObject(this, option);
}
require('util').inherits(HotKey, exports.Base);

HotKey.prototype.handleEvent = function(ev) {
  if (ev == 'keydown') {
    // Emit keydown handler
    if (typeof this.keydown == 'function')
      this.keydown();
  } else if (ev == 'keyup') {
    if (typeof this.keyup == 'function')
      this.keyup();
  } else if (ev == 'failed') {
    if (typeof this.failed == 'function')
      this.failed(arguments[1]);
  }

  // Emit generate event handler
  exports.Base.prototype.handleEvent.apply(this, arguments);
}

exports.HotKey = HotKey;
