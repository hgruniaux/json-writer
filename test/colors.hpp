// MIT License
//
// Copyright (c) 2023 Hubert Gruniaux
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef COLORS_HPP
#define COLORS_HPP

#define COLOR_PREFIX "\x1b["
#define COLOR_SUFFIX "m"

#define COLOR_RESET COLOR_PREFIX "0" COLOR_SUFFIX
#define COLOR_NULL COLOR_PREFIX "0;35" COLOR_SUFFIX
#define COLOR_BOOLEAN COLOR_PREFIX "0;31" COLOR_SUFFIX
#define COLOR_STRING COLOR_PREFIX "0;32" COLOR_SUFFIX
#define COLOR_NUMBER COLOR_PREFIX "0;33" COLOR_SUFFIX
#define COLOR_FIELD COLOR_PREFIX "0;36" COLOR_SUFFIX

#endif
