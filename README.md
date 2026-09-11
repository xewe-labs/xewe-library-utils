# XeWeUtils

Header-only helpers used across the XeWe libraries. No dependencies.

| File (under `src/`) | Contents |
|---|---|
| `String/String.h` | `xewe::str`: case, trim, split, word/fixed wrap, box/rule lines, `parse_int`, `parse_time`, `parse_day`, `parse_gmt_offset`, `to_hex` |
| `Validator/Validator.h` | `xewe::validate<T>(text, min, max)` → `std::optional<T>` for strings (length), integers and floats (range) |
| `AsyncTimer/AsyncTimer.h` | `AsyncTimer<T>`: non-blocking interpolation between two values over time |
| `LockGuard/LockGuard.h` | `xewe::LockGuard`: RAII guard for a FreeRTOS mutex |
| `Color/Color.h` | `xewe::color`: HSV ⇄ RGB |
| `Debug/Debug.h` | `DBG_PRINTLN` / `DBG_PRINTF`, enabled per class with `-DDEBUG_<Class>=1` |

Include everything with `#include <XeWeUtils.h>`. See `examples/StringHelpers`.
