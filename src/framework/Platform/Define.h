/*
 * Copyright (C) 2005-2011 MaNGOS <http://getmangos.com/>
 * Copyright (C) 2009-2011 MaNGOSZero <https://github.com/mangos/zero>
 * Copyright (C) 2011-2016 Nostalrius <https://nostalrius.org>
 * Copyright (C) 2016-2017 Elysium Project <https://github.com/elysium-project>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef MANGOS_DEFINE_H
#define MANGOS_DEFINE_H

#include <sys/types.h>

#include <ace/Basic_Types.h>
#include <ace/Default_Constants.h>
#include <ace/OS_NS_dlfcn.h>
#include <ace/ACE_export.h>

#include "Platform/CompilerDefs.h"

#define MANGOS_LITTLEENDIAN 0
#define MANGOS_BIGENDIAN    1

#if !defined(MANGOS_ENDIAN)
#  if defined (ACE_BIG_ENDIAN)
#    define MANGOS_ENDIAN MANGOS_BIGENDIAN
#  else //ACE_BYTE_ORDER != ACE_BIG_ENDIAN
#    define MANGOS_ENDIAN MANGOS_LITTLEENDIAN
#  endif //ACE_BYTE_ORDER
#endif //MANGOS_ENDIAN

typedef ACE_SHLIB_HANDLE MANGOS_LIBRARY_HANDLE;

#define MANGOS_SCRIPT_NAME "mangosscript"
#define MANGOS_SCRIPT_SUFFIX ACE_DLL_SUFFIX
#define MANGOS_SCRIPT_PREFIX ACE_DLL_PREFIX
#define MANGOS_LOAD_LIBRARY(libname)    ACE_OS::dlopen(libname)
#define MANGOS_CLOSE_LIBRARY(hlib)      ACE_OS::dlclose(hlib)
#define MANGOS_GET_PROC_ADDR(hlib,name) ACE_OS::dlsym(hlib,name)

#define MANGOS_PATH_MAX PATH_MAX                            // ace/os_include/os_limits.h -> ace/Basic_Types.h

#if PLATFORM == PLATFORM_WINDOWS
#  define MANGOS_EXPORT __declspec(dllexport)
#  define MANGOS_IMPORT __cdecl
#else //PLATFORM != PLATFORM_WINDOWS
#  define MANGOS_EXPORT export
#  if defined(__APPLE_CC__) && defined(BIG_ENDIAN)
#    define MANGOS_IMPORT __attribute__ ((longcall))
#  elif defined(__x86_64__)
#    define MANGOS_IMPORT
#  else
#    define MANGOS_IMPORT __attribute__ ((cdecl))
#  endif //__APPLE_CC__ && BIG_ENDIAN
#endif //PLATFORM

#if PLATFORM == PLATFORM_WINDOWS
#  ifdef MANGOS_WIN32_DLL_IMPORT
#    define MANGOS_DLL_DECL __declspec(dllimport)
#  else //!MANGOS_WIN32_DLL_IMPORT
#    ifdef MANGOS_WIND_DLL_EXPORT
#      define MANGOS_DLL_DECL __declspec(dllexport)
#    else //!MANGOS_WIND_DLL_EXPORT
#      define MANGOS_DLL_DECL
#    endif //MANGOS_WIND_DLL_EXPORT
#  endif //MANGOS_WIN32_DLL_IMPORT
#else //PLATFORM != PLATFORM_WINDOWS
#  define MANGOS_DLL_DECL
#endif //PLATFORM

#if PLATFORM == PLATFORM_WINDOWS
#  define MANGOS_DLL_SPEC __declspec(dllexport)
#  ifndef DECLSPEC_NORETURN
#    define DECLSPEC_NORETURN __declspec(noreturn)
#  endif //DECLSPEC_NORETURN
#else //PLATFORM != PLATFORM_WINDOWS
#  define MANGOS_DLL_SPEC
#  define DECLSPEC_NORETURN
#endif //PLATFORM

#if defined(__clang__) || defined (__GNUC__)
# define ATTRIBUTE_NO_SANITIZE_ADDRESS __attribute__((no_sanitize("address")))
# define ATTRIBUTE_NO_SANITIZE_VPTR    __attribute__((no_sanitize("vptr")))
# define ATTRIBUTE_NO_SANITIZE_BOUNDS  __attribute__((no_sanitize("bounds")))
# define ATTRIBUTE_NO_SANITIZE_SHIFT   __attribute__((no_sanitize("shift")))
# define ATTRIBUTE_NO_SANITIZE_RETURN  __attribute__((no_sanitize("return")))
#else
# define ATTRIBUTE_NO_SANITIZE_ADDRESS
# define ATTRIBUTE_NO_SANITIZE_VPTR
# define ATTRIBUTE_NO_SANITIZE_BOUNDS
# define ATTRIBUTE_NO_SANITIZE_SHIFT
# define ATTRIBUTE_NO_SANITIZE_RETURN
#endif

#if !defined(DEBUG)
#  define MANGOS_INLINE inline
#else //DEBUG
#  if !defined(MANGOS_DEBUG)
#    define MANGOS_DEBUG
#  endif //MANGOS_DEBUG
#  define MANGOS_INLINE
#endif //!DEBUG

#if COMPILER == COMPILER_GNU
#  define ATTR_NORETURN __attribute__((noreturn))
#  define ATTR_PRINTF(F,V) __attribute__ ((format (printf, F, V)))
#else //COMPILER != COMPILER_GNU
#  define ATTR_NORETURN
#  define ATTR_PRINTF(F,V)
#endif //COMPILER == COMPILER_GNU

typedef int64_t int64;
typedef int32_t int32;
typedef int16_t int16;
typedef int8_t int8;
typedef uint64_t uint64;
typedef uint32_t uint32;
typedef uint16_t uint16;
typedef uint8_t uint8;

#if COMPILER != COMPILER_MICROSOFT
typedef uint16      WORD;
typedef uint32      DWORD;
#endif //COMPILER

#if COMPILER == COMPILER_GNU
#  if !defined(__GXX_EXPERIMENTAL_CXX0X__) || (__GNUC__ < 4) || (__GNUC__ == 4) && (__GNUC_MINOR__ < 7)
#    define override
#  endif
#endif

typedef uint64 OBJECT_HANDLE;

#endif //MANGOS_DEFINE_H
