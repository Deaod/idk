// =============================================================================
//
// ztd.idk
// Copyright © 2021 JeanHeyd "ThePhD" Meneide and Shepherd's Oasis, LLC
// Contact: opensource@soasis.org
//
// Commercial License Usage
// Licensees holding valid commercial ztd.idk licenses may use this file in
// accordance with the commercial license agreement provided with the
// Software or, alternatively, in accordance with the terms contained in
// a written agreement between you and Shepherd's Oasis, LLC.
// For licensing terms and conditions see your agreement. For
// further information contact opensource@soasis.org.
//
// Apache License Version 2 Usage
// Alternatively, this file may be used under the terms of Apache License
// Version 2.0 (the "License") for non-commercial use; you may not use this
// file except in compliance with the License. You may obtain a copy of the
// License at
//
//		http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// ============================================================================>

#pragma once

#ifndef ZTD_VERSION_VERSION_HPP
#define ZTD_VERSION_VERSION_HPP

#include <cstddef>
#include <cstdint>
#include <climits>
#include <type_traits>

#define ZTD_VERSION_MAJOR 0
#define ZTD_VERSION_MINOR 0
#define ZTD_VERSION_PATCH 0
#define ZTD_VERSION_STRING "0.0.0"
#define ZTD_VERSION \
	((ZTD_VERSION_MAJOR * 100'000) + (ZTD_VERSION_MINOR * 100) + (ZTD_VERSION_PATCH))

#define ZTD_IS_ON(OP_SYMBOL) ((3 OP_SYMBOL 3) != 0)
#define ZTD_IS_OFF(OP_SYMBOL) ((3 OP_SYMBOL 3) == 0)
#define ZTD_IS_DEFAULT_ON(OP_SYMBOL) ((3 OP_SYMBOL 3) > 3)
#define ZTD_IS_DEFAULT_OFF(OP_SYMBOL) ((3 OP_SYMBOL 3 OP_SYMBOL 3) < 0)

#define ZTD_ON |
#define ZTD_OFF ^
#define ZTD_DEFAULT_ON +
#define ZTD_DEFAULT_OFF -

// clang-format off

#if defined(__has_include)
	#define ZTD_COMPILER_WITH_HAS_INCLUDE_I_ ZTD_ON
	#define ZTD_HAS_INCLUDE_I_(...) __has_include(__VA_ARGS__)
#else
	#define ZTD_COMPILER_WITH_HAS_INCLUDE_I_ ZTD_OFF
	#define ZTD_HAS_INCLUDE_I_(...) 0
#endif

#define ZTD_TOKEN_TO_STRING_POST_EXPANSION_I_(__TOK) #__TOK
#define ZTD_TOKEN_TO_STRING_I_(__TOK) ZTD_TOKEN_TO_STRING_POST_EXPANSION_I_(__TOK)

#if ZTD_HAS_INCLUDE_I_(<version>)
	// Can check __has_include and we have the C++20 <version> header
	#include <version>
#endif

#if defined(__clang__)
	#define ZTD_COMPILER_CLANG_I_ ZTD_ON
#else
	#define ZTD_COMPILER_CLANG_I_ ZTD_OFF
#endif

#if defined(__GNUC__)
	#define ZTD_COMPILER_GCC_I_ ZTD_ON
#else
	#define ZTD_COMPILER_GCC_I_ ZTD_OFF
#endif

#if defined (_MSC_VER)
	#define ZTD_COMPILER_VCXX_I_ ZTD_ON
#else
	#define ZTD_COMPILER_VCXX_I_ ZTD_OFF
#endif

#if ZTD_IS_ON(ZTD_COMPILER_VCXX_I_) && ZTD_IS_ON(ZTD_COMPILER_CLANG_I_)
	#define ZTD_COMPILER_VCXX_CLANG_I_ ZTD_ON
#else
	#define ZTD_COMPILER_VCXX_CLANG_I_ ZTD_OFF
#endif

#if defined(__MINGW32__)
	#define ZTD_COMPILER_MINGW_I_ ZTD_ON
#else
	#define ZTD_COMPILER_MINGW_I_ ZTD_OFF
#endif

#if defined(__GLIBCXX__)
	#define ZTD_LIBSTDCXX_I_ ZTD_ON
#else
	#define ZTD_LIBSTDCXX_I_ ZTD_OFF
#endif

#if defined(_LIBCPP_VERSION)
	#define ZTD_LIBCXX_I_ ZTD_ON
#else
	#define ZTD_LIBCXX_I_ ZTD_OFF
#endif

#if defined (_YVALS_CORE_H_) // Volatile definition; would be nice if VC++ exposed some documented macros...
	#define ZTD_LIBVCXX_I_ ZTD_ON
#else
	#define ZTD_LIBVCXX_I_ ZTD_OFF
#endif

#if defined(_WIN32)
	#define ZTD_PLATFORM_WINDOWS_I_ ZTD_ON
#else
	#define ZTD_PLATFORM_WINDOWS_I_ ZTD_OFF
#endif // Windows

#if defined(__CYGWIN__)
	#define ZTD_PLATFORM_CYGWIN_I_ ZTD_ON
#else
	#define ZTD_PLATFORM_CYGWIN_I_ ZTD_OFF
#endif // Cygwin shenanigans

#if defined(__MVS__)
	#define ZTD_PLATFORM_ZEDOS_I_ ZTD_ON
#else
	#define ZTD_PLATFORM_ZEDOS_I_ ZTD_OFF
#endif // IBM's Z/OS

#if defined(__STDC_HOSTED__)
	#define ZTD_PLATFORM_FREESTANDING_I_ ZTD_OFF
#else
	#define ZTD_PLATFORM_FREESTANDING_I_ ZTD_ON
#endif

#if defined(_AIX)
	// We are on the AIX platform
	#define ZTD_PLATFORM_AIX_I_ ZTD_ON
#else
	// We are not on the AIX platform
	#define ZTD_PLATFORM_AIX_I_ ZTD_OFF
#endif // IBM's AIX

#if defined(ZTD_PLATFORM_UNKNOWN_CHECK)
	#if (ZTD_PLATFORM_UNKNOWN_CHECK != 0)
		#define ZTD_PLATFORM_UNKNOWN_CHECK_I_ ZTD_ON
	#else
		#define ZTD_PLATFORM_UNKNOWN_CHECK_I_ ZTD_OFF
	#endif
#else
	#define ZTD_PLATFORM_UNKNOWN_CHECK_I_ ZTD_OFF
#endif

#if defined(sun) || defined(__sun)
	#if defined(__SVR4) || defined(__svr4__)
		// Solaris
		#define ZTD_PLATFORM_SUNOS_I_ ZTD_DEFAULT_OFF
		#define ZTD_PLATFORM_SOLARIS_I_ ZTD_DEFAULT_ON
	#else
		// SunOS
		#define ZTD_PLATFORM_SUNOS_I_ ZTD_DEFAULT_ON
		#define ZTD_PLATFORM_SOLARIS_I_ ZTD_DEFAULT_OFF
	#endif
#else
	#define ZTD_PLATFORM_SUNOS_I_ ZTD_DEFAULT_OFF
	#define ZTD_PLATFORM_SOLARIS_I_ ZTD_DEFAULT_OFF
#endif // SunOS and Solaris

#if defined(__unix) || defined(__unix__)
	#define ZTD_PLATFORM_UNIX_I_ ZTD_ON
#else
	#define ZTD_PLATFORM_UNIX_I_ ZTD_DEFAULT_OFF
#endif // UNIX platforms

#if defined(__linux) || defined(__linux__) || defined(linux)
	#define ZTD_PLATFORM_LINUX_I_ ZTD_ON
#else
	#define ZTD_PLATFORM_LINUX_I_ ZTD_DEFAULT_OFF
#endif // Linux platforms

#if defined(__STDC_ISO_10646__) && (__STDC_ISO_10646__ != 0)
	#define ZTD_WCHAR_T_UTF32_COMPATIBLE_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_WCHAR_T_UTF32_COMPATIBLE_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_CHAR8_T)
	#define ZTD_USE_USER_CHAR8_T_I_ ZTD_ON
	#define ZTD_CHAR8_T_I_ ZTD_CHAR8_T
#elif defined(__cpp_char8_t)
	#define ZTD_USE_USER_CHAR8_T_I_ ZTD_DEFAULT_OFF
	#define ZTD_CHAR8_T_I_ char8_t
#else
	#define ZTD_USE_USER_CHAR8_T_I_ ZTD_DEFAULT_OFF
	#define ZTD_CHAR8_T_I_ unsigned char
#endif // char8_t defined by the user

#if defined(__cpp_char8_t)
	#define ZTD_NATIVE_CHAR8_T_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_NATIVE_CHAR8_T_I_ ZTD_DEFAULT_OFF
#endif // char8_t exists natively (C++) - C proposal in WG14 still in progress

#if defined(ZTD_BUILD)
	#if (ZTD_BUILD != 0)
		#define ZTD_BUILD_I_ ZTD_ON
	#else
		#define ZTD_BUILD_I_ ZTD_OFF
	#endif
#else
	#define ZTD_BUILD_I_ ZTD_DEFAULT_OFF
#endif // Building or not

#if defined(ZTD_DLL) && (ZTD_DLL != 0)
	#define ZTD_DLL_I_ ZTD_ON
#else
	#define ZTD_DLL_I_ ZTD_OFF
#endif // Building or not

#if defined(ZTD_HEADER_ONLY)
	#if (ZTD_HEADER_ONLY != 0)
		#define ZTD_HEADER_ONLY_I_ ZTD_ON
	#else
		#define ZTD_HEADER_ONLY_I_ ZTD_OFF
	#endif
#else
	#define ZTD_HEADER_ONLY_I_ ZTD_DEFAULT_OFF
#endif // Header only library

#if defined(ZTD_INLINE_BUILD)
	#if (ZTD_INLINE_BUILD != 0)
		#define ZTD_INLINE_BUILD_I_ ZTD_ON
	#else
		#define ZTD_INLINE_BUILD_I_ ZTD_OFF
	#endif
#else
	#define ZTD_INLINE_BUILD_I_ ZTD_DEFAULT_OFF
#endif // Header only library

#if !defined(ZTD_FUNCTION_LINKAGE)
	#if defined(__cplusplus)
		// C++
		#define ZTD_FUNCTION_LINKAGE_I_ extern "C"
	#else
		// normal
		#define ZTD_FUNCTION_LINKAGE_I_
	#endif // C++ or not
#else
	#define ZTD_FUNCTION_LINKAGE_I_ ZTD_FUNCTION_LINKAGE
#endif // Linkage specification

#if defined(ZTD_API_LINKAGE)
	#define ZTD_API_LINKAGE_I_ ZTD_API_LINKAGE
#else
	#if ZTD_IS_ON(ZTD_DLL_I_)
		#if ZTD_IS_ON(ZTD_COMPILER_VCXX_I_) || ZTD_IS_ON(ZTD_PLATFORM_WINDOWS_I_) || ZTD_IS_ON(ZTD_PLATFORM_CYGWIN_I_)
			// MSVC Compiler; or, Windows, or Cygwin platforms
			#if ZTD_IS_ON(ZTD_BUILD_I_)
				// Building the library
				#if ZTD_IS_ON(ZTD_COMPILER_GCC_I_)
					// Using GCC
					#define ZTD_API_LINKAGE_I_ __attribute__((dllexport))
				#else
					// Using Clang, MSVC, etc...
					#define ZTD_API_LINKAGE_I_ __declspec(dllexport)
				#endif
			#else
				#if ZTD_IS_ON(ZTD_PLATFORM_GCC_I_)
					#define ZTD_API_LINKAGE_I_ __attribute__((dllimport))
				#else
					#define ZTD_API_LINKAGE_I_ __declspec(dllimport)
				#endif
			#endif
		#else
			// extern if building normally on non-MSVC
			#define ZTD_API_LINKAGE_I_ extern
		#endif
	#elif ZTD_IS_ON(ZTD_INLINE_BUILD_I_)
		// Built-in library, like how stb typical works
		#if ZTD_IS_ON(ZTD_HEADER_ONLY_I_)
			// Header only, so functions are defined "inline"
			#define ZTD_API_LINKAGE_I_ inline
		#else
			// Not header only, so seperately compiled files
			#define ZTD_API_LINKAGE_I_ extern
		#endif
	#else
		// Normal static library
		#if defined(__cplusplus)
			#define ZTD_API_LINKAGE_I_
		#else
			#define ZTD_API_LINKAGE_I_ extern
		#endif
	#endif // DLL or not
#endif // Build definitions

#if defined (ZTD_ALIGNED_OPERATOR_NEW)
	#if (ZTD_ALIGNED_OPERATOR_NEW != 0)
		#define ZTD_ALIGNED_OPERATOR_NEW_I_ ZTD_ON
	#else
		#define ZTD_ALIGNED_OPERATOR_NEW_I_ ZTD_OFF
	#endif
#elif defined(__cpp_aligned_new)
	#define ZTD_ALIGNED_OPERATOR_NEW_I_ ZTD_DEFAULT_ON
#elif defined(__cplusplus) && __cplusplus > 201603L
	#define ZTD_ALIGNED_OPERATOR_NEW_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_ALIGNED_OPERATOR_NEW_I_ ZTD_DEFAULT_OFF
#endif // C++ operator new, with alignment parameter

#if defined(ZTD_CONCEPTS)
	#if (ZTD_CONCEPTS != 0)
		#define ZTD_CONCEPTS_I_ ZTD_ON
	#else
		#define ZTD_CONCEPTS_I_ ZTD_OFF
	#endif
#elif ZTD_IS_ON(ZTD_COMPILER_CLANG_I_)
	// clang is busted right now!
	// taking bets: Clang 14 is when it'll get fixed!
	#if (__clang_major__ > 14)
		#define ZTD_CONCEPTS_I_ ZTD_DEFAULT_ON
	#else
		#define ZTD_CONCEPTS_I_ ZTD_DEFAULT_OFF
	#endif
#elif defined(__cpp_concepts) && (__cpp_concepts >= 201907LL)
	#define ZTD_CONCEPTS_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_CONCEPTS_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_LANGINFO)
	#if (ZTD_LANGINFO != 0)
		#define ZTD_LANGINFO_I_ ZTD_ON
	#else
		#define ZTD_LANGINFO_I_ ZTD_OFF
	#endif
#else
	#if ZTD_HAS_INCLUDE_I_(<langinfo.h>)
		#define ZTD_LANGINFO_I_ ZTD_ON
	#else
		#define ZTD_LANGINFO_I_ ZTD_DEFAULT_OFF
	#endif
#endif // langinfo POSIX

#if defined(ZTD_NL_LANGINFO)
	#if (ZTD_NL_LANGINFO != 0)
		#define ZTD_NL_LANGINFO_I_ ZTD_ON
	#else
		#define ZTD_NL_LANGINFO_I_ ZTD_OFF
	#endif
#else
	#if ZTD_HAS_INCLUDE_I_(<nl_langinfo.h>)
		#define ZTD_NL_LANGINFO_I_ ZTD_ON
	#else
		#define ZTD_NL_LANGINFO_I_ ZTD_DEFAULT_OFF
	#endif
#endif // nl_langinfo POSIX

#if defined(ZTD_DEFAULT_HANDLER_THROWS)
	#if (ZTD_DEFAULT_HANDLER_THROWS != 0)
		#define ZTD_DEFAULT_HANDLER_THROWS_I_ ZTD_ON
	#else
		#define ZTD_DEFAULT_HANDLER_THROWS_I_ ZTD_OFF
	#endif
#else
	#define ZTD_DEFAULT_HANDLER_THROWS_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_LOCALE_DEPENDENT_WIDE_EXECUTION)
	#if (ZTD_LOCALE_DEPENDENT_WIDE_EXECUTION != 0)
		#define ZTD_LOCALE_DEPENDENT_WIDE_EXECUTION_I_ ZTD_ON
	#else
		#define ZTD_LOCALE_DEPENDENT_WIDE_EXECUTION_I_ ZTD_OFF
	#endif
#elif ZTD_IS_ON(ZTD_NL_LANGINFO_I_) && (ZTD_IS_ON(ZTD_PLATFORM_ZEDOS_I_) || ZTD_IS_ON(ZTD_PLATFORM_AIX_I_))
	#define ZTD_LOCALE_DEPENDENT_WIDE_EXECUTION_I_ ZTD_ON
#else
	#define ZTD_LOCALE_DEPENDENT_WIDE_EXECUTION_I_ ZTD_DEFAULT_OFF
#endif // Locale-dependent wchar_t detection

#if defined (__has_cpp_attribute) && (__has_cpp_attribute(nodiscard) != 0L)
	#if __has_cpp_attribute(nodiscard) >= 201907L
		#define ZTD_NODISCARD_MESSAGE_I_(__message) [[nodiscard(__message)]]
		#define ZTD_NODISCARD_I_ [[nodiscard]]
	#else
		#define ZTD_NODISCARD_MESSAGE_I_(__message) [[nodiscard]]
		#define ZTD_NODISCARD_I_ [[nodiscard]]
	#endif
#elif defined (__has_c_attribute) && (__has_c_attribute(nodiscard) != 0L)
	#define ZTD_NODISCARD_MESSAGE_I_(__message) [[nodiscard(__message)]]
	#define ZTD_NODISCARD_I_ [[nodiscard]]
#else
	#if ZTD_IS_ON(ZTD_COMPILER_VCXX_I_) && defined(_Check_return_)
		#define ZTD_NODISCARD_MESSAGE_I_(__message) _Check_return_
		#define ZTD_NODISCARD_I_ _Check_return_
	#elif ZTD_IS_ON(ZTD_COMPILER_CLANG_I_) || ZTD_IS_ON(ZTD_COMPILER_GCC_I_)
		#define ZTD_NODISCARD_MESSAGE_I_(__message) __attribute__((warn_unused_result))
		#define ZTD_NODISCARD_I_ __attribute__((warn_unused_result))
	#else
		// :c
		#define ZTD_NODSICARD_I_(__message)
		#define ZTD_NODISCARD_I_
	#endif
#endif

#if defined(ZTD_STD_TEXT_ENCODING_ID)
	#if (ZTD_STD_TEXT_ENCODING_ID != 0)
		#define ZTD_STD_TEXT_ENCODING_ID_I_ ZTD_ON
	#else
		#define ZTD_STD_TEXT_ENCODING_ID_I_ ZTD_OFF
	#endif
#elif defined(__cpp_lib_text_encoding_id)
	#define ZTD_STD_TEXT_ENCODING_ID_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_STD_TEXT_ENCODING_ID_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_STD_LIBRARY_CONSTEXPR_ALGORITHMS)
	#if (ZTD_STD_LIBRARY_CONSTEXPR_ALGORITHMS != 0)
		#define ZTD_STD_LIBRARY_CONSTEXPR_ALGORITHMS_I_ ZTD_ON
	#else
		#define ZTD_STD_LIBRARY_CONSTEXPR_ALGORITHMS_I_ ZTD_OFF
	#endif
#elif defined(__cpp_lib_constexpr_algorithms)
	#define ZTD_STD_LIBRARY_CONSTEXPR_ALGORITHMS_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_STD_LIBRARY_CONSTEXPR_ALGORITHMS_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_STD_LIBRARY_RANGES)
	#if (ZTD_STD_LIBRARY_RANGES != 0)
		#define ZTD_STD_LIBRARY_RANGES_I_ ZTD_ON
	#else
		#define ZTD_STD_LIBRARY_RANGES_I_ ZTD_OFF
	#endif
#elif ZTD_IS_ON(ZTD_COMPILER_CLANG_I_)
	#if 0
		#define ZTD_STD_LIBRARY_RANGES_I_ ZTD_DEFAULT_ON
	#else
		// clang's concepts implementation, which powers ranges, is busted!
		#define ZTD_STD_LIBRARY_RANGES_I_ ZTD_DEFAULT_OFF
	#endif
#elif defined(__cpp_lib_ranges)
	#define ZTD_STD_LIBRARY_RANGES_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_STD_LIBRARY_RANGES_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_STD_LIBRARY_ENDIAN)
	#if (ZTD_STD_LIBRARY_ENDIAN != 0)
		#define ZTD_STD_LIBRARY_ENDIAN_I_ ZTD_ON
	#else
		#define ZTD_STD_LIBRARY_ENDIAN_I_ ZTD_OFF
	#endif
#elif defined(__cpp_lib_endian)
	#define ZTD_STD_LIBRARY_ENDIAN_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_STD_LIBRARY_ENDIAN_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_STD_LIBRARY_CONCEPTS)
	#if (ZTD_STD_LIBRARY_CONCEPTS_I_ != 0)
		#define ZTD_STD_LIBRARY_CONCEPTS_I_ ZTD_ON
	#else
		#define ZTD_STD_LIBRARY_CONCEPTS_I_ ZTD_OFF
	#endif
#elif defined(__cpp_lib_concepts)
	#define ZTD_STD_LIBRARY_CONCEPTS_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_STD_LIBRARY_CONCEPTS_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_COMPILE_TIME_ENCODING_NAME)
	#define ZTD_COMPILE_TIME_ENCODING_NAME_GET_I_()         ZTD_COMPILE_TIME_ENCODING_NAME
	#define ZTD_COMPILE_TIME_ENCODING_NAME_DESCRIPTION_I_() "set by the user with ZTD_COMPILE_TIME_ENCODING_NAME as (" ZTD_TOKEN_TO_STRING_I_(ZTD_COMPILE_TIME_ENCODING_NAME) ")"
	#define ZTD_COMPILE_TIME_ENCODING_NAME_I_               ZTD_DEFAULT_ON
#elif ZTD_IS_ON(ZTD_STD_TEXT_ENCODING_ID_I_)
	#define ZTD_COMPILE_TIME_ENCODING_NAME_GET_I_()         ::std::text_encoding::literal().name()
	#define ZTD_COMPILE_TIME_ENCODING_NAME_DESCRIPTION_I_() "from std::text_encoding::literal().name()"
	#define ZTD_COMPILE_TIME_ENCODING_NAME                  ZTD_DEFAULT_ON
#elif defined(__GNUC_EXECUTION_CHARSET_NAME)
	#define ZTD_COMPILE_TIME_ENCODING_NAME_GET_I_()         __GNUC_EXECUTION_CHARSET_NAME
	#define ZTD_COMPILE_TIME_ENCODING_NAME_DESCRIPTION_I_() __GNUC_EXECUTION_CHARSET_NAME
	#define ZTD_COMPILE_TIME_ENCODING_NAME_I_               ZTD_DEFAULT_ON
#elif defined(__clang_literal_encoding__)
	#define ZTD_COMPILE_TIME_ENCODING_NAME_GET_I_()         __clang_literal_encoding__
	#define ZTD_COMPILE_TIME_ENCODING_NAME_DESCRIPTION_I_() __clang_literal_encoding__
	#define ZTD_COMPILE_TIME_ENCODING_NAME_I_               ZTD_DEFAULT_ON
#elif ZTD_IS_ON(ZTD_COMPILER_CLANG_I_)
	#define ZTD_COMPILE_TIME_ENCODING_NAME_GET_I_()         "UTF-8"
	#define ZTD_COMPILE_TIME_ENCODING_NAME_DESCRIPTION_I_() "UTF-8"
	#define ZTD_COMPILE_TIME_ENCODING_NAME_I_               ZTD_DEFAULT_ON
#else
	#define ZTD_COMPILE_TIME_ENCODING_NAME_GET_I_()         "UTF-8"
	#define ZTD_COMPILE_TIME_ENCODING_NAME_DESCRIPTION_I_() "UTF-8"
	#define ZTD_COMPILE_TIME_ENCODING_NAME_I_               ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_COMPILE_TIME_WIDE_ENCODING_NAME)
	#define ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_GET_I_()         ZTD_COMPILE_TIME_WIDE_ENCODING_NAME
	#define ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_DESCRIPTION_I_() "set by the user with ZTD_COMPILE_TIME_ENCODING_NAME as (" ZTD_TOKEN_TO_STRING_I_(ZTD_COMPILE_TIME_WIDE_ENCODING_NAME) ")"
	#define ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_I_               ZTD_ON
#elif ZTD_IS_ON(ZTD_STD_TEXT_ENCODING_ID_I_)
	#define ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_GET_I_()         ::std::text_encoding::wide_literal().name()
	#define ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_DESCRIPTION_I_() "from ::std::text_encoding::wide_literal().name()"
	#define ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_I_               ZTD_DEFAULT_ON
#elif defined(__GNUC_WIDE_EXECUTION_CHARSET_NAME)
	#define ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_GET_I_()         __GNUC_WIDE_EXECUTION_CHARSET_NAME
	#define ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_DESCRIPTION_I_() ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_GET_I_()
	#define ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_I_               ZTD_DEFAULT_ON
#elif defined(__clang_wide_literal_encoding__)
	#define ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_GET_I_()         __clang_wide_literal_encoding__
	#define ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_DESCRIPTION_I_() ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_GET_I_()
	#define ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_I_               ZTD_DEFAULT_ON
#elif ZTD_IS_ON(ZTD_PLATFORM_WINDOWS_I_)
	#define ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_GET_I_()         "UTF-16"
	#define ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_DESCRIPTION_I_() "UTF-16"
	#define ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_I_               ZTD_DEFAULT_ON
#elif (WCHAR_MAX >= 0x001FFFFF) && ZTD_IS_ON(ZTD_WCHAR_T_UTF32_COMPATIBLE_I_)
	#define ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_GET_I_()         "UTF-32"
	#define ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_DESCRIPTION_I_() "UTF-32"
	#define ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_I_               ZTD_DEFAULT_ON
#elif (WCHAR_MAX >= 0xFFFF)
	#define ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_GET_I_()         "UTF-16"
	#define ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_DESCRIPTION_I_() "UTF-16"
	#define ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_I_               ZTD_DEFAULT_ON
#elif (WCHAR_MAX >= 0xFF)
	#define ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_GET_I_()         "UTF-8"
	#define ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_DESCRIPTION_I_() "UTF-8"
	#define ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_I_               ZTD_DEFAULT_ON
#else
	#define ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_GET_I_()         "UTF-32"
	#define ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_DESCRIPTION_I_() "UTF-32"
	#define ZTD_COMPILE_TIME_WIDE_ENCODING_NAME_I_               ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_YES_PLEASE_DESTROY_MY_LITERALS_UTTERLY_I_MEAN_IT)
	#if (ZTD_YES_PLEASE_DESTROY_MY_LITERALS_UTTERLY_I_MEAN_IT != 0)
		#define ZTD_YES_PLEASE_DESTROY_MY_LITERALS_UTTERLY_I_MEAN_IT_I_ ZTD_ON
	#else
		#define ZTD_YES_PLEASE_DESTROY_MY_LITERALS_UTTERLY_I_MEAN_IT_I_ ZTD_OFF
	#endif
#else
	#define ZTD_YES_PLEASE_DESTROY_MY_LITERALS_UTTERLY_I_MEAN_IT_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_YES_PLEASE_DESTROY_MY_WIDE_LITERALS_UTTERLY_I_MEAN_IT)
	#if (ZTD_YES_PLEASE_DESTROY_MY_WIDE_LITERALS_UTTERLY_I_MEAN_IT != 0)
		#define ZTD_YES_PLEASE_DESTROY_MY_WIDE_LITERALS_UTTERLY_I_MEAN_IT_I_ ZTD_ON
	#else
		#define ZTD_YES_PLEASE_DESTROY_MY_WIDE_LITERALS_UTTERLY_I_MEAN_IT_I_ ZTD_OFF
	#endif
#else
	#define ZTD_YES_PLEASE_DESTROY_MY_WIDE_LITERALS_UTTERLY_I_MEAN_IT_I_ ZTD_DEFAULT_OFF
#endif

#if defined (__has_cpp_attribute) && (__has_cpp_attribute(deprecated) != 0L)
	#define ZTD_DEPRECATED_I_(__message) [[deprecated(__message)]]
#elif defined (__has_c_attribute) && (__has_c_attribute(deprecated) != 0L)
	#define ZTD_DEPRECATED_I_(__message) [[deprecated(__message)]]
#else
	#if ZTD_IS_ON(ZTD_COMPILER_VCXX_I_)
		#define ZTD_DEPRECATED_I_(__message) declspec(deprecated)
	#elif ZTD_IS_ON(ZTD_COMPILER_CLANG_I_) || ZTD_IS_ON(ZTD_COMPILER_GCC_I_)
		#define ZTD_DEPRECATED_I_(__message) __attribute__((warn_unused_result))
	#else
		// :c
		#define ZTD_DEPRECATED_I_(__message)
	#endif
#endif

#if defined(ZTD_STD_LIBRARY_IS_CONSTANT_EVALUATED)
	#if (ZTD_STD_LIBRARY_IS_CONSTANT_EVALUATED != 0)
		#define ZTD_STD_LIBRARY_IS_CONSTANT_EVALUATED_I_ ZTD_ON
	#else
		#define ZTD_STD_LIBRARY_IS_CONSTANT_EVALUATED_I_ ZTD_OFF
	#endif
#elif defined(__cpp_lib_is_constant_evaluated)
	#define ZTD_STD_LIBRARY_IS_CONSTANT_EVALUATED_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_STD_LIBRARY_IS_CONSTANT_EVALUATED_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_STD_LIBRARY_TO_ADDRESS)
	#if (ZTD_STD_LIBRARY_TO_ADDRESS != 0)
		#define ZTD_STD_LIBRARY_TO_ADDRESS_I_ ZTD_ON
	#else
		#define ZTD_STD_LIBRARY_TO_ADDRESS_I_ ZTD_OFF
	#endif
#elif defined(__cpp_lib_to_address)
	#define ZTD_STD_LIBRARY_TO_ADDRESS_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_STD_LIBRARY_TO_ADDRESS_I_ ZTD_DEFAULT_OFF
#endif

#if defined (ZTD_CONSTEXPR_IF_CONSTANT_EVALUATED)
	#if (ZTD_CONSTEXPR_IF_CONSTANT_EVALUATED != 0)
		#define ZTD_CONSTEXPR_IF_CONSTANT_EVALUATED_I_ constexpr
	#else
		#define ZTD_CONSTEXPR_IF_CONSTANT_EVALUATED_I_ 
	#endif
#elif ZTD_IS_ON(ZTD_STD_LIBRARY_IS_CONSTANT_EVALUATED_I_)
		#define ZTD_CONSTEXPR_IF_CONSTANT_EVALUATED_I_ constexpr
#else
		#define ZTD_CONSTEXPR_IF_CONSTANT_EVALUATED_I_ 
#endif


#if defined(ZTD_STD_LIBRARY_SPACESHIP_COMPARE)
	#if (ZTD_STD_LIBRARY_SPACESHIP_COMPARE != 0)
		#define ZTD_STD_LIBRARY_SPACESHIP_COMPARE_I_ ZTD_ON
	#else
		#define ZTD_STD_LIBRARY_SPACESHIP_COMPARE_I_ ZTD_OFF
	#endif
#elif defined(__cpp_lib_three_way_comparison)
	#define ZTD_STD_LIBRARY_SPACESHIP_COMPARE_I_ ZTD_ON
#else
	#define ZTD_STD_LIBRARY_SPACESHIP_COMPARE_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_STD_LIBRARY_STARTS_ENDS_WITH)
	#if (ZTD_STD_LIBRARY_STARTS_ENDS_WITH != 0)
		#define ZTD_STD_LIBRARY_STARTS_ENDS_WITH_I_ ZTD_ON
	#else
		#define ZTD_STD_LIBRARY_STARTS_ENDS_WITH_I_ ZTD_ON
	#endif
#elif defined(__cpp_lib_starts_ends_with)
	#define ZTD_STD_LIBRARY_STARTS_ENDS_WITH_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_STD_LIBRARY_STARTS_ENDS_WITH_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_STD_LIBRARY_STRING_CONTAINS)
	#if (ZTD_STD_LIBRARY_STRING_CONTAINS != 0)
		#define ZTD_STD_LIBRARY_STRING_CONTAINS_I_ ZTD_ON
	#else
		#define ZTD_STD_LIBRARY_STRING_CONTAINS_I_ ZTD_ON
	#endif
#elif defined(__cpp_lib_string_contains)
	#define ZTD_STD_LIBRARY_STRING_CONTAINS_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_STD_LIBRARY_STRING_CONTAINS_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_STD_LIBRARY_SPAN)
	#if (ZTD_STD_LIBRARY_SPAN != 0)
		#define ZTD_STD_LIBRARY_SPAN_I_ ZTD_ON
	#else
		#define ZTD_STD_LIBRARY_SPAN_I_ ZTD_ON
	#endif
#elif defined(__cpp_lib_span)
	#define ZTD_STD_LIBRARY_SPAN_I_ ZTD_DEFAULT_ON
#else
	#define ZTD_STD_LIBRARY_SPAN_I_ ZTD_DEFAULT_OFF
#endif

#if defined (ZTD_UNICODE_CODE_POINT_DISTINCT_TYPE)
	#if (ZTD_UNICODE_CODE_POINT_DISTINCT_TYPE != 0)
		#define ZTD_UNICODE_CODE_POINT_DISTINCT_TYPE_I_ ZTD_ON
	#else
		#define ZTD_UNICODE_CODE_POINT_DISTINCT_TYPE_I_ ZTD_OFF
	#endif
#else
	#define ZTD_UNICODE_CODE_POINT_DISTINCT_TYPE_I_ ZTD_DEFAULT_OFF
#endif

#if defined(ZTD_UNICODE_CODE_POINT_INVARIANT_ABORT)
	#if (ZTD_UNICODE_CODE_POINT_INVARIANT_ABORT != 0)
		#define ZTD_UNICODE_CODE_POINT_INVARIANT_ABORT_I_ ZTD_ON
	#else
		#define ZTD_UNICODE_CODE_POINT_INVARIANT_ABORT_I_ ZTD_OFF
	#endif
#else
	#define ZTD_UNICODE_CODE_POINT_INVARIANT_ABORT_I_ ZTD_OFF
#endif

#if defined (ZTD_UNICODE_SCALAR_VALUE_DISTINCT_TYPE)
	#if (ZTD_UNICODE_CODE_POINT_DISTINCT_TYPE != 0)
		#define ZTD_UNICODE_SCALAR_VALUE_DISTINCT_TYPE_I_ ZTD_ON
	#else
		#define ZTD_UNICODE_SCALAR_VALUE_DISTINCT_TYPE_I_ ZTD_OFF
	#endif
#else
	#define ZTD_UNICODE_SCALAR_VALUE_DISTINCT_TYPE_I_ ZTD_DEFAULT_ON
#endif

#if defined(ZTD_UNICODE_SCALAR_VALUE_INVARIANT_ABORT)
	#if (ZTD_UNICODE_SCALAR_VALUE_INVARIANT_ABORT != 0)
		#define ZTD_UNICODE_SCALAR_VALUE_INVARIANT_ABORT_I_ ZTD_ON
	#else
		#define ZTD_UNICODE_SCALAR_VALUE_INVARIANT_ABORT_I_ ZTD_OFF
	#endif
#else
	#define ZTD_UNICODE_SCALAR_VALUE_INVARIANT_ABORT_I_ ZTD_OFF
#endif

#include <ztd/prologue.hpp>
#include <ztd/epilogue.hpp>

#endif // ZTD_VERSION_VERSION_HPP
