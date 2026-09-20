// SPDX-FileCopyrightText: 2026 Maxim Dokukin (maxdokukin.com)
// SPDX-License-Identifier: GPL-3.0-only
// xewe-library-utils/src/XeWeUtils.h
#pragma once

#include "Debug/Debug.h"
#include "String/String.h"
#include "Validator/Validator.h"
#include "AsyncTimer/AsyncTimer.h"
#include "Span/Span.h"
#include "Color/Color.h"

// LockGuard wraps a FreeRTOS mutex, so it is only pulled in where FreeRTOS
// exists. Include "LockGuard/LockGuard.h" directly if you want a hard error on a
// platform without it.
#if defined(__has_include)
#  if __has_include(<freertos/FreeRTOS.h>)
#    include "LockGuard/LockGuard.h"
#  endif
#else
#  include "LockGuard/LockGuard.h"
#endif
