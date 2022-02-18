#pragma once

#include <unistd.h>

// detect if we're on Linux
#ifdef __linux__
#define LINUX
#endif

// detect if we're on Windows
#if defined(_WIN32) || defined(_WIN64)
#define WINDOWS
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#endif

// make sure we're either on Linux or on Windows
#if (!defined(LINUX) && !defined(WINDOWS)) || (defined(LINUX) && defined(WINDOWS))
#error Unsupported platform!
#endif

// detect Linux system architecture
#if defined(LINUX)
#if defined(__GNUC__)

// 64-bit
#if defined(__x86_64__) || defined(__ppc64__)
#define x86_64
// 32-bit
#else
#define x86
#endif

#else
#error Unable to detect system architecture!
#endif
#endif

// detect Windows system architecture
#if defined(WINDOWS)
#if (defined(_WIN32) || defined(_WIN64))

// 64-bit
#if _WIN64
#define x86_64
// 32-bit
#else
#define x86
#endif

#else
#error Unable to detect system architecture!
#endif
#endif
