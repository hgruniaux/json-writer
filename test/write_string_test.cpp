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

#include "json_writer.hpp"

#include "colors.hpp"

#include <gtest/gtest.h>

TEST(WriteStringTest, empty_uncolored)
{
  JsonWriter writer;
  writer.set_use_colors(false);
  writer.write_string("");
  EXPECT_EQ(writer.get_buffer(), "\"\"");
}

TEST(WriteStringTest, empty_default_color)
{
  JsonWriter writer;
  writer.set_use_colors(true);
  writer.write_string("");
  EXPECT_EQ(writer.get_buffer(), COLOR_STRING "\"\"" COLOR_RESET);
}

TEST(WriteStringTest, empty_custom_color)
{
  JsonWriter writer;
  writer.set_use_colors(true);
  writer.get_colors().string = "1;2";
  writer.write_string("");
  EXPECT_EQ(writer.get_buffer(), COLOR_PREFIX "0;1;2" COLOR_SUFFIX "\"\"" COLOR_RESET);
}

TEST(WriteStringTest, escape)
{
  JsonWriter writer;
  writer.set_use_colors(false);
  writer.write_string("\"\\\n\r\t\f");
  EXPECT_EQ(writer.get_buffer(), "\"\\\"\\\\\\n\\r\\t\\f\"");
}

TEST(WriteStringTest, classic)
{
  JsonWriter writer;
  writer.set_use_colors(false);
  writer.write_string("foo\nbar");
  EXPECT_EQ(writer.get_buffer(), "\"foo\\nbar\"");
}

TEST(WriteStringTest, write_string_field)
{
  JsonWriter writer;
  writer.set_use_colors(false);
  writer.set_pretty(true);
  writer.write_string_field("foo", "bar");
  EXPECT_EQ(writer.get_buffer(), "\"foo\": \"bar\",\n");
}
