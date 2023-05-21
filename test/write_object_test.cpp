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

TEST(WriteObjectTest, empty_pretty)
{
  JsonWriter writer;
  writer.set_use_colors(false);
  writer.set_pretty(true);

  writer.begin_object();
  writer.end_object();

  EXPECT_EQ(writer.get_buffer(), "{\n}");
}

TEST(WriteObjectTest, indent_level_pretty)
{
  JsonWriter writer;
  writer.set_use_colors(false);
  writer.set_pretty(true);

  writer.begin_object();

  writer.begin_field("foo");
  writer.write_null();
  writer.end_field();

  writer.end_object();

  EXPECT_EQ(writer.get_buffer(), "{\n  \"foo\": null\n}");
}

TEST(WriteObjectTest, indent_level_compact)
{
  JsonWriter writer;
  writer.set_use_colors(false);
  writer.set_pretty(false);

  writer.begin_object();

  writer.begin_field("foo");
  writer.write_null();
  writer.end_field();

  writer.end_object();

  EXPECT_EQ(writer.get_buffer(), "{\"foo\":null}");
}

TEST(WriteObjectTest, trailing_comma_pretty)
{
  JsonWriter writer;
  writer.set_use_colors(false);
  writer.set_pretty(true);

  writer.begin_object();

  writer.begin_field("foo");
  writer.write_null();
  writer.end_field();

  writer.begin_field("bar");
  writer.write_null();
  writer.end_field();

  writer.end_object();

  EXPECT_EQ(writer.get_buffer(), "{\n  \"foo\": null,\n  \"bar\": null\n}");
}

TEST(WriteObjectTest, trailing_comma_compact)
{
  JsonWriter writer;
  writer.set_use_colors(false);
  writer.set_pretty(false);

  writer.begin_object();

  writer.begin_field("foo");
  writer.write_null();
  writer.end_field();

  writer.begin_field("bar");
  writer.write_null();
  writer.end_field();

  writer.end_object();

  EXPECT_EQ(writer.get_buffer(), "{\"foo\":null,\"bar\":null}");
}
