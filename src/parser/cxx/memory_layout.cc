// Copyright (c) 2023 Roberto Raggi <roberto.raggi@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <cxx/memory_layout.h>
#include <cxx/symbols.h>
#include <cxx/types.h>

#include <cassert>
#include <cstdlib>

namespace cxx {

MemoryLayout::MemoryLayout(int bits) : bits_(bits) {
  sizeOfPointer_ = bits / 8;
  sizeOfLong_ = bits / 8;
}

MemoryLayout::~MemoryLayout() = default;

auto MemoryLayout::bits() const -> int { return bits_; }

auto MemoryLayout::sizeOfPointer() const -> int { return sizeOfPointer_; }

auto MemoryLayout::sizeOfLong() const -> int { return sizeOfLong_; }

}  // namespace cxx