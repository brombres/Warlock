#ifndef BALEFIRE_TYPES_H
#define BALEFIRE_TYPES_H

#pragma once

// Set up C conditional compilation defines
#if defined(__EMSCRIPTEN__)
  #define BALEFIRE_PLATFORM_WEB 1
  #define BALEFIRE_PLATFORM_DETERMINED 1
#elif defined(BALEFIRE_PLATFORM_PLAYDATE)
  #define BALEFIRE_PLATFORM_DETERMINED 1
#endif

#if !defined(BALEFIRE_PLATFORM_DETERMINED)
  // Handle Apple's wonky defines which used to ALWAYS be defined as 0 or 1 and
  // are now only defined if the platform is active.

  #if defined(__APPLE__)
    #if defined(TARGET_IPHONE_SIMULATOR)
      #if TARGET_IPHONE_SIMULATOR
        #define BALEFIRE_PLATFORM_IOS 1
      #endif
    #endif

    #if !defined(BALEFIRE_PLATFORM_IOS)
      #if defined(TARGET_OS_IPHONE)
        #if TARGET_OS_IPHONE
          #define BALEFIRE_PLATFORM_IOS 1
        #endif
      #endif
    #endif

    #if !defined(BALEFIRE_PLATFORM_IOS)
      #define BALEFIRE_PLATFORM_MACOS 1
    #endif

    #define BALEFIRE_PLATFORM_DETERMINED 1
  #endif
#endif

#if !defined(BALEFIRE_PLATFORM_DETERMINED)
  #if defined(_WIN32)
  #  define BALEFIRE_PLATFORM_WINDOWS 1
  #elif defined(__ANDROID__)
  #  define BALEFIRE_PLATFORM_ANDROID 1
  #elif defined(__linux__)
  #  define BALEFIRE_PLATFORM_LINUX 1
  #elif defined(__CYGWIN__)
  #  define BALEFIRE_PLATFORM_LINUX  1
  #  define BALEFIRE_PLATFORM_CYGWIN 1
  #else
  #  define BALEFIRE_PLATFORM_GENERIC 1
  #endif
#endif

#if defined(BALEFIRE_PLATFORM_WINDOWS)
  #pragma warning(disable: 4297) /* unexpected throw warnings */
  #if !defined(UNICODE)
    #define UNICODE
  #endif
  #include <windows.h>
  #include <signal.h>
#else
  #define BALEFIRE_PLATFORM_UNIX_COMPATIBLE 1
  #include <limits.h>
  #include <stdint.h>
#endif

#include <math.h>
#include <stdlib.h>
#include <string.h>

//------------------------------------------------------------------------------
// Logging
//------------------------------------------------------------------------------
#ifdef __ANDROID__
  #include <android/log.h>
  #define BALEFIRE_LOG(...)       __android_log_print( ANDROID_LOG_INFO,  "Rogue", __VA_ARGS__ )
  #define BALEFIRE_LOG_ERROR(...) __android_log_print( ANDROID_LOG_ERROR, "Rogue", __VA_ARGS__ )
#else
  #define BALEFIRE_LOG(...)       printf( __VA_ARGS__ )
  #define BALEFIRE_LOG_ERROR(...) printf( __VA_ARGS__ )
#endif

//------------------------------------------------------------------------------
// Primitive Types
//------------------------------------------------------------------------------
#if defined(BALEFIRE_PLATFORM_WINDOWS)
  typedef double           Real64;
  typedef float            Real32;
  typedef __int64          Int64;
  typedef __int32          Int32;
  typedef __int32          Character;
  typedef unsigned __int16 Word;
  typedef unsigned char    Byte;
  typedef int              Logical;
  typedef unsigned __int64 UInt64;
  typedef unsigned __int32 UInt32;
#else
  typedef double           Real64;
  typedef float            Real32;
  typedef int64_t          Int64;
  typedef int32_t          Int32;
  typedef int32_t          Character;
  typedef uint16_t         Word;
  typedef uint8_t          Byte;
  typedef int              Logical;
  typedef uint64_t         UInt64;
  typedef uint32_t         UInt32;
#endif

#endif // BALEFIRE_TYPES_H
