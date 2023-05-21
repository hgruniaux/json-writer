# Json-Writer

A simple single header file [json_writer.hpp](json_writer.hpp) to help writing [JSON](https://www.json.org/) code easily with pretty formatting and even colors in terminals !

Calling the demo program (the [main.cpp](main.cpp) file) gives :
```json
{
  "name": "Bob",
  "age": 42,
  "is_adult": true,
  "height": 175.6,
  "children": [
    {
      "name": "Alice",
      "age": 10,
      "is_adult": false
    },
    {
      "name": "Charlie",
      "age": 8,
      "is_adult": false
    }
  ],
  "extra": null
}
```

Json-Writer is able to output colors [(SGR colors)](https://en.wikipedia.org/wiki/ANSI_escape_code#Colors) for terminals if requested.

## License

This project is licensed under the terms of the MIT license.
