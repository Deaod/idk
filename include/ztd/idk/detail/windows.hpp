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

#ifndef ZTD_IDK_DETAIL_WINDOWS_HPP
#define ZTD_IDK_DETAIL_WINDOWS_HPP

#include <ztd/idk/version.hpp>

#if ZTD_IS_ON(ZTD_PLATFORM_WINDOWS_I_)

#pragma push_macro("NOMINMAX")
#pragma push_macro("WIN32_LEAN_AND_MEAN")
#pragma push_macro("VC_EXTRALEAN")

#define NOMINMAX 1
#define WIN32_LEAN_AND_MEAN 1
#define VC_EXTRALEAN 1

#ifdef _MSC_VER
#include <cstddef>
#include <ciso646>
#include <cwchar>
#include <locale>
#else
#endif

extern "C" {
#include <Windows.h>
}

#include <ztd/prologue.hpp>

namespace ztd { namespace idk {
	ZTD_IDK_INLINE_ABI_NAMESPACE_OPEN_I_
	namespace __idk_detail { namespace __windows {

	}} // namespace __idk_detail::__windows
	ZTD_IDK_INLINE_ABI_NAMESPACE_CLOSE_I_
}} // namespace ztd::idk

#pragma pop_macro("VC_EXTRALEAN")
#pragma pop_macro("WIN32_LEAN_AND_MEAN")
#pragma pop_macro("NOMINMAX")

#endif // Windows nightmare

#include <ztd/epilogue.hpp>

#endif // ZTD_IDK_DETAIL_WINDOWS_HPP
