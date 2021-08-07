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

#include <ztd/idk/detail/encoding_name.hpp>

#include <catch2/catch.hpp>

TEST_CASE("text/detail/encoding_name", "Ensure that basic usages of the encoding_name comparison works") {
	static_assert(ztd::__idk_detail::__is_unicode_encoding_name("UTF-8"));
	static_assert(ztd::__idk_detail::__is_unicode_encoding_name("UTF-16"));
	static_assert(ztd::__idk_detail::__is_unicode_encoding_name("UTF-32"));
	static_assert(ztd::__idk_detail::__is_unicode_encoding_name("UTF8"));
	static_assert(ztd::__idk_detail::__is_unicode_encoding_name("UTF16"));
	static_assert(ztd::__idk_detail::__is_unicode_encoding_name("UTF32"));
	static_assert(ztd::__idk_detail::__is_unicode_encoding_name("utf8"));
	static_assert(ztd::__idk_detail::__is_unicode_encoding_name("utf16"));
	static_assert(ztd::__idk_detail::__is_unicode_encoding_name("utf32"));
	static_assert(ztd::__idk_detail::__is_unicode_encoding_name("    _-  utf8"));
	static_assert(ztd::__idk_detail::__is_unicode_encoding_name("   utf16    "));
	static_assert(ztd::__idk_detail::__is_unicode_encoding_name("    _--   utf32"));
	static_assert(ztd::__idk_detail::__is_unicode_encoding_name("uTF8"));
	static_assert(ztd::__idk_detail::__is_unicode_encoding_name("--UtF-_-16"));
	static_assert(ztd::__idk_detail::__is_unicode_encoding_name("UTf____32"));
	static_assert(ztd::__idk_detail::__is_unicode_encoding_name("UTF7IMAP"));
	static_assert(ztd::__idk_detail::__is_unicode_encoding_name("UTF-16-BE"));
	static_assert(ztd::__idk_detail::__is_unicode_encoding_name("UTF-32_LE"));
	static_assert(ztd::__idk_detail::__is_unicode_encoding_name("UTF-16-BE"));
	static_assert(ztd::__idk_detail::__is_unicode_encoding_name("GB18030"));
	static_assert(ztd::__idk_detail::__is_unicode_encoding_name("gb18030"));
	static_assert(ztd::__idk_detail::__is_unicode_encoding_name("Mutf____8"));
	static_assert(ztd::__idk_detail::__is_unicode_encoding_name("Mutf__8"));
	static_assert(ztd::__idk_detail::__is_unicode_encoding_name("Mutf    8            "));
	static_assert(ztd::__idk_detail::__is_unicode_encoding_name("gb18030"));
	static_assert(ztd::__idk_detail::__is_unicode_encoding_name("utf\t\t\t\n\r\n\r\nebcdic"));
	static_assert(ztd::__idk_detail::__is_unicode_encoding_name("gb18030"));
	static_assert(ztd::__idk_detail::__is_unicode_encoding_name("g    B     18  ____0 30"));
	static_assert(ztd::__idk_detail::__is_unicode_encoding_name("cesu8"));
	static_assert(ztd::__idk_detail::__is_unicode_encoding_name("UTF---------1"));
	static_assert(!ztd::__idk_detail::__is_unicode_encoding_name("ascii"));
	static_assert(!ztd::__idk_detail::__is_unicode_encoding_name("tatar"));
	static_assert(!ztd::__idk_detail::__is_unicode_encoding_name("latin-1"));
	static_assert(!ztd::__idk_detail::__is_unicode_encoding_name("UTF-8-not-really"));
	static_assert(!ztd::__idk_detail::__is_unicode_encoding_name("UTF-7-not-really"));
	static_assert(!ztd::__idk_detail::__is_unicode_encoding_name("UTF69"));

	REQUIRE(ztd::__idk_detail::__is_unicode_encoding_name("UTF-8"));
	REQUIRE(ztd::__idk_detail::__is_unicode_encoding_name("UTF-16"));
	REQUIRE(ztd::__idk_detail::__is_unicode_encoding_name("UTF-32"));
	REQUIRE(ztd::__idk_detail::__is_unicode_encoding_name("UTF8"));
	REQUIRE(ztd::__idk_detail::__is_unicode_encoding_name("UTF16"));
	REQUIRE(ztd::__idk_detail::__is_unicode_encoding_name("UTF32"));
	REQUIRE(ztd::__idk_detail::__is_unicode_encoding_name("utf8"));
	REQUIRE(ztd::__idk_detail::__is_unicode_encoding_name("utf16"));
	REQUIRE(ztd::__idk_detail::__is_unicode_encoding_name("utf32"));
	REQUIRE(ztd::__idk_detail::__is_unicode_encoding_name("    _-  utf8"));
	REQUIRE(ztd::__idk_detail::__is_unicode_encoding_name("   utf16    "));
	REQUIRE(ztd::__idk_detail::__is_unicode_encoding_name("    _--   utf32"));
	REQUIRE(ztd::__idk_detail::__is_unicode_encoding_name("uTF8"));
	REQUIRE(ztd::__idk_detail::__is_unicode_encoding_name("--UtF-_-16"));
	REQUIRE(ztd::__idk_detail::__is_unicode_encoding_name("UTf____32"));
	REQUIRE(ztd::__idk_detail::__is_unicode_encoding_name("UTF7IMAP"));
	REQUIRE(ztd::__idk_detail::__is_unicode_encoding_name("UTF-16-BE"));
	REQUIRE(ztd::__idk_detail::__is_unicode_encoding_name("UTF-32_LE"));
	REQUIRE(ztd::__idk_detail::__is_unicode_encoding_name("UTF-16-BE"));
	REQUIRE(ztd::__idk_detail::__is_unicode_encoding_name("GB18030"));
	REQUIRE(ztd::__idk_detail::__is_unicode_encoding_name("gb18030"));
	REQUIRE(ztd::__idk_detail::__is_unicode_encoding_name("Mutf____8"));
	REQUIRE(ztd::__idk_detail::__is_unicode_encoding_name("Mutf__8"));
	REQUIRE(ztd::__idk_detail::__is_unicode_encoding_name("Mutf    8            "));
	REQUIRE(ztd::__idk_detail::__is_unicode_encoding_name("gb18030"));
	REQUIRE(ztd::__idk_detail::__is_unicode_encoding_name("utf\t\t\t\n\r\n\r\nebcdic"));
	REQUIRE(ztd::__idk_detail::__is_unicode_encoding_name("gb18030"));
	REQUIRE(ztd::__idk_detail::__is_unicode_encoding_name("g    B     18  ____0 30"));
	REQUIRE(ztd::__idk_detail::__is_unicode_encoding_name("cesu8"));
	REQUIRE(ztd::__idk_detail::__is_unicode_encoding_name("UTF---------1"));
	REQUIRE(!ztd::__idk_detail::__is_unicode_encoding_name("ascii"));
	REQUIRE(!ztd::__idk_detail::__is_unicode_encoding_name("tatar"));
	REQUIRE(!ztd::__idk_detail::__is_unicode_encoding_name("latin-1"));
	REQUIRE(!ztd::__idk_detail::__is_unicode_encoding_name("UTF-8-not-really"));
	REQUIRE(!ztd::__idk_detail::__is_unicode_encoding_name("UTF-7-not-really"));
	REQUIRE(!ztd::__idk_detail::__is_unicode_encoding_name("UTF69"));
}
