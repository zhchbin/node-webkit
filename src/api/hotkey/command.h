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

#ifndef CONTENT_NW_SRC_API_HOTKEY_COMMAND_H_
#define CONTENT_NW_SRC_API_HOTKEY_COMMAND_H_

#include <string>

#include "ui/base/accelerators/accelerator.h"

namespace api {

class Command {
 public:
  explicit Command(const std::string& accelerator);
  ~Command();

  // The platform value for the Command.
  static std::string CommandPlatform();

  // Parse a string as an accelerator. If the accelerator is unparsable then
  // a generic ui::Accelerator object will be returns (with key_code Unknown).
  static ui::Accelerator StringToAccelerator(const std::string& accelerator);

  // Accessors:
  const ui::Accelerator& accelerator() const { return accelerator_; }

  // Setter:
  void set_accelerator(ui::Accelerator accelerator) {
    accelerator_ = accelerator;
  }

  const std::string& get_error() {
    return error_;
  }

 private:
  ui::Accelerator accelerator_;
  std::string error_;
};

}  // namespace api

#endif  // CONTENT_NW_SRC_API_HOTKEY_COMMAND_H_

