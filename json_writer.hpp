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

#ifndef JSON_WRITER_HPP
#define JSON_WRITER_HPP

#include <charconv>
#include <limits>
#include <string>
#include <string_view>

class JsonWriter
{
public:
  struct Colors
  {
    const char* field = "36";
    const char* string = "32";
    const char* boolean = "31";
    const char* null = "35";
    const char* number = "33";
  };

  const std::string& get_buffer() const { return m_buffer; }

  Colors& get_colors() { return m_colors; }
  const Colors& get_colors() const { return m_colors; }

  void set_use_colors(bool use_colors) { m_use_colors = use_colors; }
  void set_pretty(bool pretty) { m_pretty = pretty; }

  void begin_object();
  void end_object();

  void begin_array();
  void end_array();

  void begin_array_item();
  void end_array_item();

  void begin_field(std::string_view name);
  void end_field();

  void write_null();
  void write_bool(bool value);
  void write_string(std::string_view value);
  template<class T>
  void write_integer(T value)
  {
    constexpr size_t BUFFER_SIZE = std::numeric_limits<T>::digits10 + 1 + std::is_signed<T>::value;
    char buffer[BUFFER_SIZE];
    auto [ptr, ec] = std::to_chars(buffer, buffer + BUFFER_SIZE, value);
    *ptr = '\0';
    set_color(m_colors.number);
    m_buffer.append(buffer);
    reset_color();
  }
  template<class T>
  void write_float(T value)
  {
    constexpr size_t BUFFER_SIZE =
      5 + std::numeric_limits<T>::max_digits10 + std::max(2, log10ceil(std::numeric_limits<T>::max_exponent10));
    char buffer[BUFFER_SIZE];
    auto [ptr, ec] = std::to_chars(buffer, buffer + BUFFER_SIZE, value);
    *ptr = '\0';
    set_color(m_colors.number);
    m_buffer.append(buffer);
    reset_color();
  }

  void write_null_field(std::string_view name)
  {
    begin_field(name);
    write_null();
    end_field();
  }
  void write_bool_field(std::string_view name, bool value)
  {
    begin_field(name);
    write_bool(value);
    end_field();
  }
  void write_string_field(std::string_view name, std::string_view value)
  {
    begin_field(name);
    write_string(value);
    end_field();
  }
  template<class T>
  void write_integer_field(std::string_view name, T value)
  {
    begin_field(name);
    write_integer(value);
    end_field();
  }
  template<class T>
  void write_float_field(std::string_view name, T value)
  {
    begin_field(name);
    write_float(value);
    end_field();
  }

  template<class It, class F>
  void write_array(It begin, It end, F func)
  {
    begin_array();

    for (auto it = begin; it != end; ++it) {
      begin_array_item();
      func(*this, *it);
      end_array_item();
    }

    end_array();
  }

private:
  template<typename T>
  static constexpr int log10ceil(T num)
  {
    return num < 10 ? 1 : 1 + log10ceil(num / 10);
  }

  void set_color(const char* color);
  void reset_color();

  void write_indent();
  void write_comma();
  void write_quoted_string(std::string_view value);

  void remove_trailing_comma();

private:
  std::string m_buffer;
  Colors m_colors;
  int m_indent_level = 0;
  bool m_use_colors = false;
  bool m_pretty = true;
};

#ifdef JSON_WRITER_IMPLEMENTATION
void
JsonWriter::begin_object()
{
  m_buffer.push_back('{');
  if (m_pretty)
    m_buffer.push_back('\n');
  ++m_indent_level;
}

void
JsonWriter::end_object()
{
  remove_trailing_comma();

  --m_indent_level;
  write_indent();
  m_buffer.push_back('}');
}

void
JsonWriter::begin_array()
{
  m_buffer.push_back('[');
  if (m_pretty)
    m_buffer.push_back('\n');
  ++m_indent_level;
}

void
JsonWriter::end_array()
{
  remove_trailing_comma();

  --m_indent_level;
  write_indent();
  m_buffer.push_back(']');
}

void
JsonWriter::begin_array_item()
{
  write_indent();
}

void
JsonWriter::end_array_item()
{
  write_comma();
}

void
JsonWriter::begin_field(std::string_view name)
{
  write_indent();

  set_color(m_colors.field);
  write_quoted_string(name);
  m_buffer.push_back(':');
  reset_color();

  if (m_pretty)
    m_buffer.push_back(' ');
}

void
JsonWriter::end_field()
{
  write_comma();
}

void
JsonWriter::write_null()
{
  set_color(m_colors.null);
  m_buffer.append("null");
  reset_color();
}

void
JsonWriter::write_bool(bool value)
{
  set_color(m_colors.boolean);
  if (value)
    m_buffer.append("true");
  else
    m_buffer.append("false");
  reset_color();
}

void
JsonWriter::write_string(std::string_view value)
{
  set_color(m_colors.string);
  write_quoted_string(value);
  reset_color();
}

void
JsonWriter::set_color(const char* color)
{
  if (!m_use_colors)
    return;

  m_buffer.append("\x1b[0;");
  m_buffer.append(color);
  m_buffer.append("m");
}

void
JsonWriter::reset_color()
{
  if (!m_use_colors)
    return;

  m_buffer.append("\x1b[0m");
}

void
JsonWriter::write_indent()
{
  if (!m_pretty)
    return;

  int indent_level = m_indent_level;
  while (indent_level--) {
    m_buffer.append("  ");
  }
}

void
JsonWriter::write_comma()
{
  m_buffer.push_back(',');
  if (m_pretty)
    m_buffer.push_back('\n');
}

void
JsonWriter::write_quoted_string(std::string_view value)
{
  m_buffer.append("\"");

  for (size_t i = 0; i < value.size(); ++i) {
    const char ch = value[i];
    switch (ch) {
      case '"':
        m_buffer.append("\\\"");
        break;
      case '\\':
        m_buffer.append("\\\\");
        break;
      case '\n':
        m_buffer.append("\\n");
        break;
      case '\r':
        m_buffer.append("\\r");
        break;
      case '\t':
        m_buffer.append("\\t");
        break;
      case '\f':
        m_buffer.append("\\f");
        break;
      default:
        m_buffer.push_back(ch);
    }
  }

  m_buffer.append("\"");
}

void
JsonWriter::remove_trailing_comma()
{
  if (m_buffer.size() > 2 && m_buffer[m_buffer.size() - 2] == ',' && m_buffer[m_buffer.size() - 1] == '\n') {
    m_buffer.resize(m_buffer.size() - 1);
    m_buffer[m_buffer.size() - 1] = '\n';
  } else if (m_buffer.size() > 2 && m_buffer[m_buffer.size() - 1] == ',') {
    m_buffer.resize(m_buffer.size() - 1);
  }
}
#endif

#endif
