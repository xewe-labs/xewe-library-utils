# AGENTS.md — xewe-library-utils

Rules for coding agents working **anywhere in this repository**, not only in `doc/`.
Organization-wide rules are in
[`.github/AGENTS.md`](https://github.com/xewe-labs/.github/blob/main/AGENTS.md) and win where this
file is silent: never publish, never tag or push, never commit unasked, never flash a board.

## This library

* **Header-only, and it must stay that way.** There is no `.cpp` in `src/`. Adding one changes how
  every dependent library links; do not introduce one to "tidy up" a large header.
* **No dependencies.** `library.properties` has no `depends=` line and must keep none — every
  other XeWe library depends on this one, so a dependency here is a dependency everywhere. Only
  `<Arduino.h>`, the C++ standard library, and FreeRTOS headers **behind
  `__has_include(<freertos/FreeRTOS.h>)`**. No header reachable unconditionally from
  `src/XeWeUtils.h` may include a FreeRTOS or vendor header — that is what lets this library
  compile on cores without an RTOS. `src/LockGuard/LockGuard.h` is the one exception, and the
  entry header includes it conditionally.
* **`src/` has exactly one top-level header,** `src/XeWeUtils.h`, which only includes the files in
  its subfolders. Everything else lives in a folder per class named exactly like the class
  (`src/AsyncTimer/AsyncTimer.h`). Arduino puts every library's `src/` on the include path, so a
  second top-level header here — especially one named `String.h` or `Timer.h` — collides with
  other libraries and with system headers on macOS and Windows.
* **Files include each other with relative quotes** (`#include "../Debug/Debug.h"`), never through
  the entry header.

## Do not break these

* **`AsyncTimer` is in the global namespace.** It is documented that way and dependent code says
  `AsyncTimer<uint8_t>`, not `xewe::AsyncTimer<uint8_t>`. Moving it into `xewe` is a breaking
  change across every repository in the organization, not a cleanup.
* **`lower` and `to_lower` are duplicates on purpose-by-accident.** Both are public and callers
  exist; remove one only as a deliberate, announced breaking change.
* **Debug flags default to `0`** behind `#ifndef DEBUG_<Class>`. Never enable one in the header;
  enable it from build flags.
* **`xewe::validate` must stay exception-free.** A malformed string is a normal input here, not
  an error path — but it is handled by delegating to `xewe::str::parse_int` / `parse_float`, which
  report failure by returning `false`. Never reintroduce `std::stoll`/`std::stod` or `try`/`catch`:
  most Arduino cores compile with `-fno-exceptions`, and the host portability check in
  `publish-arduino-library` fails the build if they come back.

## When changing this library

* `library.json` is **generated** from `library.properties` by
  [`publish-arduino-library`](https://github.com/xewe-labs/publish-arduino-library)
  (`python3 publish.py manifest`). Never hand-edit it; `publish.py check` fails when it is stale.
* Versions are **lockstep** across all XeWe libraries. Never bump this one alone.
* Source files start with the SPDX header from
  [`.github/guidelines/license-header.txt`](https://github.com/xewe-labs/.github/blob/main/guidelines/license-header.txt).
  Markdown files do not.
* **Documentation is part of the change.** A new or changed public function updates its page in
  `doc/` in the same breath — this reference is written to be exhaustive, so a gap is a bug.
* Check your work without publishing anything:

  ```bash
  python3 publish-arduino-library/publish.py check xewe-library-utils
  ```
