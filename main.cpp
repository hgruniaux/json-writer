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

#define JSON_WRITER_IMPLEMENTATION
#include "json_writer.hpp"

#include <cstdio>

int
main()
{
  JsonWriter writer;
  writer.set_use_colors(true);
  writer.set_pretty(true);

  {
    writer.begin_object();

    writer.write_string_field("name", "Bob");
    writer.write_integer_field("age", 42);
    writer.write_bool_field("is_adult", true);
    writer.write_float_field("height", 175.6);

    writer.begin_field("children");
    {
      writer.begin_array();

      {
        writer.begin_array_item();

        {
          writer.begin_object();
          writer.write_string_field("name", "Alice");
          writer.write_integer_field("age", 10);
          writer.write_bool_field("is_adult", false);
          writer.end_object();
        }

        writer.end_array_item();
      }

      {
        writer.begin_array_item();

        {
          writer.begin_object();
          writer.write_string_field("name", "Charlie");
          writer.write_integer_field("age", 8);
          writer.write_bool_field("is_adult", false);
          writer.end_object();
        }

        writer.end_array_item();
      }

      writer.end_array();
    }
    writer.end_field();

    writer.write_null_field("extra");

    writer.end_object();
  }

  puts(writer.get_buffer().c_str());
}
