// [CppLog](https://jaynakum.github.io/CppLog/)
/*
Copyright 2022 Jay Nakum

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#ifndef CppLog
#define CppLog

#include <stdio.h>
#include <time.h>
#include <string.h>

static inline char* timenow();

#define _FILE strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__
#define LOG_FORMAT      "%s | %-15s | %s:%d | "
#define LOG_ARGS        timenow(), _FILE, __FUNCTION__, __LINE__

#define DEBUG_COLOR     "\x1B[37m"
#define INFO_COLOR      "\x1B[32m"
#define WARNING_COLOR   "\x1B[33m"
#define ERROR_COLOR     "\x1B[31m"
#define CRITICAL_COLOR  "\x1B[43m\x1B[30m"
#define ASSERT_COLOR    "\x1B[41m\x1B[30m"
#define END_LOG         "\x1B[00m\n"

#define NO_LOG          0x00
#define ASSERT_LEVEL    0x01
#define CRITICAL_LEVEL  0x02
#define ERROR_LEVEL     0x03
#define WARNING_LEVEL   0x04
#define INFO_LEVEL      0x05
#define DEBUG_LEVEL     0x06

#ifndef LOG_LEVEL
#define LOG_LEVEL       DEBUG_LEVEL
#endif

#define PRINTFUNCTION(stream, format, ...)  fprintf(stream, format, __VA_ARGS__)

#if LOG_LEVEL >= DEBUG_LEVEL
#define LOG_DEBUG(message, ...)     PRINTFUNCTION(stdout, DEBUG_COLOR LOG_FORMAT message END_LOG, LOG_ARGS, ##__VA_ARGS__)
#else
#define LOG_DEBUG(message, ...)
#endif

#if LOG_LEVEL >= INFO_LEVEL
#define LOG_INFO(message, ...)      PRINTFUNCTION(stdout, INFO_COLOR LOG_FORMAT message END_LOG, LOG_ARGS, ##__VA_ARGS__)
#else
#define LOG_INFO(message, ...)
#endif

#if LOG_LEVEL >= WARNING_LEVEL
#define LOG_WARNING(message, ...)   PRINTFUNCTION(stderr, WARNING_COLOR LOG_FORMAT message END_LOG, LOG_ARGS, ##__VA_ARGS__)
#else
#define LOG_WARNING(message, ...)
#endif

#if LOG_LEVEL >= ERROR_LEVEL
#define LOG_ERROR(message, ...)     PRINTFUNCTION(stderr, ERROR_COLOR LOG_FORMAT message END_LOG, LOG_ARGS, ##__VA_ARGS__)
#else
#define LOG_ERROR(message, ...)
#endif

#if LOG_LEVEL >= CRITICAL_LEVEL
#define LOG_CRITICAL(message, ...)  PRINTFUNCTION(stderr, CRITICAL_COLOR LOG_FORMAT message END_LOG, LOG_ARGS, ##__VA_ARGS__)
#else
#define LOG_CRITICAL(message, ...)
#endif

#if LOG_LEVEL >= ASSERT_LEVEL
#define ASSERT(condition, message, ...) if (condition) PRINTFUNCTION(stderr, ASSERT_COLOR LOG_FORMAT message END_LOG, LOG_ARGS, ##__VA_ARGS__); __debugbreak()
#else
#define ASSERT(condition, message, ...)
#endif

static inline char* timenow() {
    static char buffer[64];

    time_t m_time = time(NULL);
    struct tm now = {};

    localtime_s(&now, &m_time);

    strftime(buffer, 64, "%Y-%m-%d %H:%M:%S", &now);

    return buffer;
}

#endif
