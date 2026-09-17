# xewe::validate

`src/Validator/Validator.h` — parse a string into `T` and range-check it in one call.

```cpp
if (auto level = xewe::validate<uint8_t>(args[0], 0, 255)) {
    analogWrite(pin, *level);
} else {
    serial.print("Level must be 0-255.");
}
```

## validate

```cpp
template <typename T, typename LimitT>
std::optional<T> validate(std::string_view value, LimitT min, LimitT max);
```

Returns the parsed value, or `std::nullopt` if it does not parse or falls outside `[min, max]`.

`LimitT` is a separate template parameter so plain literals deduce naturally — `validate<uint8_t>(s, 0, 255)`
compiles without casting the bounds.

| `T` | What `min`/`max` mean | Parsed with |
|---|---|---|
| `std::string` | **string length**, inclusive | no parsing; the view is copied |
| signed integral | numeric range, inclusive | `std::stoll` |
| unsigned integral | numeric range, inclusive | `std::stoull` |
| `float`, `double` | numeric range, inclusive | `std::stod` |
| anything else, **including `bool`** | — | compile error |

An unsupported `T` fails with `static_assert`:
`"Unsupported Validator::validate<T>() type."`

## Notes

* **This function relies on C++ exceptions.** It calls `std::stoll`/`std::stoull`/`std::stod`
  inside a `try`/`catch (...)` and converts a throw into `std::nullopt`. On a build with
  exceptions disabled, a malformed input aborts instead of returning empty. The ESP32 Arduino core
  enables exceptions by default.
* **Trailing garbage is accepted for numbers.** `std::stoll` stops at the first non-numeric
  character, so `validate<int>("12abc", 0, 100)` returns `12`. When you need the whole string to be
  a number, use [`xewe::str::parse_int`](string.md#number-parsing), which rejects trailing characters.
  The same applies to leading `+`/`-`, whitespace and `0x` prefixes, which `stoll` handles on its
  own terms.
* **It allocates.** Each call copies the view into a `std::string` before parsing.
* `min` and `max` are **not** swapped if you pass them inverted — an inverted range simply matches
  nothing and every call returns `std::nullopt`. (The `SerialPort` numeric prompts do swap; this
  does not.)
* The header also exposes `template <typename> struct always_false : std::false_type {};`, used
  for the `static_assert` above.
