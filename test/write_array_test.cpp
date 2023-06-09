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

TEST(WriteArrayTest, empty_pretty)
{
  JsonWriter writer;
  writer.set_use_colors(false);
  writer.set_pretty(true);

  writer.begin_array();
  writer.end_array();

  EXPECT_EQ(writer.get_buffer(), "[\n]");
}

TEST(WriteArrayTest, indent_level_pretty)
{
  JsonWriter writer;
  writer.set_use_colors(false);
  writer.set_pretty(true);

  writer.begin_array();
  writer.begin_array_item();
  writer.write_null();
  writer.end_array_item();
  writer.end_array();

  EXPECT_EQ(writer.get_buffer(), "[\n  null\n]");
}

TEST(WriteArrayTest, indent_level_compact)
{
  JsonWriter writer;
  writer.set_use_colors(false);
  writer.set_pretty(false);

  writer.begin_array();
  writer.begin_array_item();
  writer.write_null();
  writer.end_array_item();
  writer.end_array();

  EXPECT_EQ(writer.get_buffer(), "[null]");
}

TEST(WriteArrayTest, trailing_comma_pretty)
{
  JsonWriter writer;
  writer.set_use_colors(false);
  writer.set_pretty(true);

  writer.begin_array();

  writer.begin_array_item();
  writer.write_null();
  writer.end_array_item();

  writer.begin_array_item();
  writer.write_null();
  writer.end_array_item();

  writer.end_array();

  EXPECT_EQ(writer.get_buffer(), "[\n  null,\n  null\n]");
}

TEST(WriteArrayTest, trailing_comma_compact)
{
  JsonWriter writer;
  writer.set_use_colors(false);
  writer.set_pretty(false);

  writer.begin_array();

  writer.begin_array_item();
  writer.write_null();
  writer.end_array_item();

  writer.begin_array_item();
  writer.write_null();
  writer.end_array_item();

  writer.end_array();

  EXPECT_EQ(writer.get_buffer(), "[null,null]");
}

TEST(WriteArrayTest, write_array_with_func)
{
  JsonWriter writer;
  writer.set_use_colors(false);
  writer.set_pretty(false);

  int values[] = { 5, 10, 28 };
  writer.write_array(std::begin(values), std::end(values), [](JsonWriter& writer, auto item) {
    writer.write_integer(item);
  });

  EXPECT_EQ(writer.get_buffer(), "[5,10,28]");
}
