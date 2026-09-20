# XeWeUtils documentation

Complete reference for the header-only helpers in this library. The
[README](../README.md) is the short version: what the library is and how to include it.

**[AGENTS.md](AGENTS.md) — read this first if you are a coding agent.** It applies to the whole
repository, not just this folder.

| Page | Covers |
|---|---|
| [string.md](string.md) | `xewe::str` — case, trim, split, wrap, box lines, `parse_int`, `parse_float`, `parse_time`, `parse_day`, `parse_gmt_offset`, `to_hex`, `format`/`vformat` |
| [validator.md](validator.md) | `xewe::validate<T>` — parse and range-check in one call |
| [async-timer.md](async-timer.md) | `AsyncTimer<T>` — non-blocking interpolation (**global namespace**) |
| [span.md](span.md) | `xewe::span<T>` — `std::span` on C++20, a C++17 stand-in elsewhere |
| [lock-guard.md](lock-guard.md) | `xewe::LockGuard` — RAII guard for a FreeRTOS mutex (FreeRTOS cores only) |
| [color.md](color.md) | `xewe::color` — HSV ⇄ RGB, all channels 0-255 |
| [debug.md](debug.md) | `DBG_PRINTLN` / `DBG_PRINTF` and the `DEBUG_<Class>` flag convention |

Everything is reachable through the entry header:

```cpp
#include <XeWeUtils.h>
```

## Things that surprise people

* `AsyncTimer` is **not** in `namespace xewe`, unlike everything else here.
* `xewe::validate` needs C++ exceptions and tolerates trailing garbage; `xewe::str::parse_int`
  needs neither and does not.
* `xewe::color` takes hue as `0-255`, not `0-360`.
* `xewe::LockGuard` blocks forever (`portMAX_DELAY`) and is not recursive.
* `xewe::str::split_lines_sv` returns views into its argument.

## Used by

[XeWeSerial](https://github.com/xewe-labs/xewe-library-serial),
[XeWeCli](https://github.com/xewe-labs/xewe-library-cli) and
[XeWeOS](https://github.com/xewe-labs/xewe-library-os) all depend on this library.

## Examples

Three sketches, in increasing order of scope:

| | | |
|---|---|---|
| low | [`01_StringHelpers`](../examples/01_StringHelpers) | `capitalize`, `parse_time`, `validate`, `wrap_words` |
| mid | [`02_TextLayout`](../examples/02_TextLayout) | box and rule lines, `align_into`, `compose_box_line`, `wrap_words` vs `wrap_fixed`, `to_hex` — the primitives XeWeSerial is built from |
| high | [`03_TimersAndColor`](../examples/03_TimersAndColor) | `AsyncTimer` fading an LED without blocking, `hsv_to_rgb`, and — on a FreeRTOS core — `LockGuard` sharing state with a second task |
