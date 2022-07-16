// =============================================================================
//
// ztd.idk
// Copyright © 2022 JeanHeyd "ThePhD" Meneide and Shepherd's Oasis, LLC
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
// ============================================================================ //

#pragma once

#ifndef ZTD_RANGES_ADL_HPP
#define ZTD_RANGES_ADL_HPP

#include <ztd/ranges/version.hpp>

#include <ztd/idk/type_traits.hpp>
#include <ztd/idk/unwrap.hpp>

#include <iterator>
#include <limits>

#include <ztd/prologue.hpp>

namespace ztd { namespace ranges {
	ZTD_RANGES_INLINE_ABI_NAMESPACE_OPEN_I_

	namespace __rng_detail {

		template <typename _It, typename = void>
		struct __iterator_value_type_from_ref_or_void {
			//////
			/// @brief Deliberately undocumented.
			using type = void;
		};

		template <typename _It>
		struct __iterator_value_type_from_ref_or_void<_It, ::std::void_t<decltype(*::std::declval<_It&>())>> {
			//////
			/// @brief Deliberately undocumented.
			using type = ::std::remove_reference_t<decltype(*::std::declval<_It&>())>;
		};

		template <typename _It, typename = void>
		struct __iterator_value_type_or_fallback {
			//////
			/// @brief Deliberately undocumented.
			using type = typename __iterator_value_type_from_ref_or_void<_It>::type;
		};

		template <typename _It>
		struct __iterator_value_type_or_fallback<_It,
			::std::void_t<typename ::std::iterator_traits<::std::remove_reference_t<_It>>::value_type>> {
			//////
			/// @brief Deliberately undocumented.
			using type = typename ::std::iterator_traits<::std::remove_reference_t<_It>>::value_type;
		};

		template <typename _It, typename = void>
		struct __iterator_reference_or_fallback {
			//////
			/// @brief Deliberately undocumented.
			using type = decltype(*::std::declval<_It&>());
		};

		template <typename _It>
		struct __iterator_reference_or_fallback<_It,
			::std::void_t<typename ::std::iterator_traits<::std::remove_reference_t<_It>>::reference>> {
			//////
			/// @brief Deliberately undocumented.
			using type = typename ::std::iterator_traits<::std::remove_reference_t<_It>>::reference;
		};

		template <typename _It, typename = void>
		struct iterator_difference_type_or_fallback {
			//////
			/// @brief Deliberately undocumented.
			using type = ::std::ptrdiff_t;
		};

		template <typename _It>
		struct iterator_difference_type_or_fallback<_It,
			::std::void_t<typename ::std::iterator_traits<::std::remove_reference_t<_It>>::difference_type>> {
		private:
			//////
			/// @brief Deliberately undocumented.
			using __maybe_void_type =
				typename ::std::iterator_traits<::std::remove_reference_t<_It>>::difference_type;

		public:
			using type
				= ::std::conditional_t<::std::is_void_v<__maybe_void_type>, ::std::ptrdiff_t, __maybe_void_type>;
		};

		template <typename _It, typename = void>
		struct __iterator_value_type_interception {
#if ZTD_IS_ON(ZTD_STD_LIBRARY_RANGES)
			//////
			/// @brief Deliberately undocumented.
			using type = ::std::iter_value_t<_It>;
#else
			//////
			/// @brief Deliberately undocumented.
			using type = typename __iterator_value_type_or_fallback<::std::remove_reference_t<_It>>::type;
#endif
		};

		template <typename _Container>
		struct __iterator_value_type_interception<::std::back_insert_iterator<_Container>> {
			//////
			/// @brief Deliberately undocumented.
			using type = typename remove_cvref_t<unwrap_t<_Container>>::value_type;
		};
	} // namespace __rng_detail

#if ZTD_IS_ON(ZTD_STD_LIBRARY_RANGES)
	template <typename _It>
	using iterator_reference_t = ::std::iter_reference_t<_It>;

	template <typename _It>
	using iterator_difference_type_t = ::std::iter_difference_t<_It>;
#else
	template <typename _It>
	using iterator_reference_t =
		typename __rng_detail::__iterator_reference_or_fallback<::std::remove_reference_t<_It>>::type;

	template <typename _It>
	using iterator_difference_type_t =
		typename __rng_detail::iterator_difference_type_or_fallback<::std::remove_reference_t<_It>>::type;
#endif

	template <typename _It>
	using iterator_value_type_t = typename __rng_detail::__iterator_value_type_interception<_It>::type;

	template <typename _It>
	using iterator_size_type_t = ::std::make_signed_t<iterator_difference_type_t<::std::remove_reference_t<_It>>>;

#if ZTD_IS_ON(ZTD_STD_LIBRARY_RANGES)
	namespace ranges_adl {
		template <typename _Range>
		constexpr auto adl_begin(_Range&& __range) noexcept(
			noexcept(::std::ranges::begin(::std::forward<_Range>(__range))))
			-> decltype(::std::ranges::begin(::std::forward<_Range>(__range))) {
			return ::std::ranges::begin(::std::forward<_Range>(__range));
		}

		template <typename _Range>
		constexpr auto adl_cbegin(_Range&& __range) noexcept(
			noexcept(::std::ranges::cbegin(::std::forward<_Range>(__range))))
			-> decltype(::std::ranges::cbegin(::std::forward<_Range>(__range))) {
			return ::std::ranges::cbegin(::std::forward<_Range>(__range));
		}

		template <typename _Range>
		constexpr auto adl_rbegin(_Range&& __range) noexcept(
			noexcept(::std::ranges::rbegin(::std::forward<_Range>(__range))))
			-> decltype(::std::ranges::rbegin(::std::forward<_Range>(__range))) {
			return ::std::ranges::rbegin(::std::forward<_Range>(__range));
		}

		template <typename _Range>
		constexpr auto adl_crbegin(_Range&& __range) noexcept(
			noexcept(::std::ranges::crbegin(::std::forward<_Range>(__range))))
			-> decltype(::std::ranges::crbegin(::std::forward<_Range>(__range))) {
			return ::std::ranges::crbegin(::std::forward<_Range>(__range));
		}

		template <typename _Range>
		constexpr auto adl_end(_Range&& __range) noexcept(
			noexcept(::std::ranges::end(::std::forward<_Range>(__range))))
			-> decltype(::std::ranges::end(::std::forward<_Range>(__range))) {
			return ::std::ranges::end(::std::forward<_Range>(__range));
		}

		template <typename _Range>
		constexpr auto adl_cend(_Range&& __range) noexcept(
			noexcept(::std::ranges::cend(::std::forward<_Range>(__range))))
			-> decltype(::std::ranges::cend(::std::forward<_Range>(__range))) {
			return ::std::ranges::cend(::std::forward<_Range>(__range));
		}

		template <typename _Range>
		constexpr auto adl_rend(_Range&& __range) noexcept(
			noexcept(::std::ranges::rend(::std::forward<_Range>(__range))))
			-> decltype(::std::ranges::rend(::std::forward<_Range>(__range))) {
			return ::std::ranges::rend(::std::forward<_Range>(__range));
		}

		template <typename _Range>
		constexpr auto adl_crend(_Range&& __range) noexcept(
			noexcept(::std::ranges::crend(::std::forward<_Range>(__range))))
			-> decltype(::std::ranges::crend(::std::forward<_Range>(__range))) {
			return ::std::ranges::crend(::std::forward<_Range>(__range));
		}

		template <typename _Range>
		constexpr auto adl_data(_Range&& __range) noexcept(
			noexcept(::std::ranges::data(::std::forward<_Range>(__range))))
			-> decltype(::std::ranges::data(::std::forward<_Range>(__range))) {
			return ::std::ranges::data(::std::forward<_Range>(__range));
		}

		template <typename _Range>
		constexpr auto adl_size(_Range&& __range) noexcept(
			noexcept(::std::ranges::size(::std::forward<_Range>(__range))))
			-> decltype(::std::ranges::size(::std::forward<_Range>(__range))) {
			return ::std::ranges::size(::std::forward<_Range>(__range));
		}

		template <typename _Range>
		constexpr auto adl_ssize(_Range&& __range) noexcept(
			noexcept(::std::ranges::ssize(::std::forward<_Range>(__range))))
			-> decltype(::std::ranges::ssize(::std::forward<_Range>(__range))) {
			return ::std::ranges::ssize(::std::forward<_Range>(__range));
		}

		template <typename _Range>
		constexpr auto adl_empty(_Range&& __range) noexcept(
			noexcept(::std::ranges::empty(::std::forward<_Range>(__range))))
			-> decltype(::std::ranges::empty(::std::forward<_Range>(__range))) {
			return ::std::ranges::empty(::std::forward<_Range>(__range));
		}

		template <typename _It>
		constexpr auto adl_iter_move(_It&& __it) noexcept(
			noexcept(::std::ranges::iter_move(::std::forward<_It>(__it))))
			-> decltype(::std::ranges::iter_move(::std::forward<_It>(__it))) {
			return ::std::ranges::iter_move(::std::forward<_It>(__it));
		}

		template <typename _ItLeft, typename _ItRight>
		constexpr auto adl_iter_swap(_ItLeft&& __left, _ItRight&& __right) noexcept(
			noexcept(::std::ranges::iter_swap(::std::forward<_ItLeft>(__left), ::std::forward<_ItRight>(__right))))
			-> decltype(::std::ranges::iter_swap(
			     ::std::forward<_ItLeft>(__left), ::std::forward<_ItRight>(__right))) {
			::std::ranges::iter_swap(::std::forward<_ItLeft>(__left), ::std::forward<_ItRight>(__right));
		}

		template <typename _ItLeft, typename _ItRight>
		constexpr auto adl_swap(_ItLeft&& __left, _ItRight&& __right) noexcept(
			noexcept(::std::ranges::swap(::std::forward<_ItLeft>(__left), ::std::forward<_ItRight>(__right))))
			-> decltype(::std::ranges::swap(
			     ::std::forward<_ItLeft>(__left), ::std::forward<_ItRight>(__right))) {
			::std::ranges::swap(::std::forward<_ItLeft>(__left), ::std::forward<_ItRight>(__right));
		}
	} // namespace ranges_adl
#else
	// Blessed Overload Overlord Xeo,
	// may his name be praised.
	namespace ranges_adl {
		// using ::std::cdata;
		using ::std::data;
		using ::std::empty;
		using ::std::size;

		using ::std::begin;
		using ::std::cbegin;
		using ::std::crbegin;
		using ::std::rbegin;

		using ::std::cend;
		using ::std::crend;
		using ::std::end;
		using ::std::rend;

		using ::std::iter_swap;
		using ::std::swap;

		template <typename _Range,
			::std::enable_if_t<::std::is_rvalue_reference_v<_Range> && !::std::is_const_v<_Range>>* = nullptr>
		constexpr auto begin(_Range&& __range) -> decltype(::std::move(__range).begin()) {
			return ::std::move(__range).begin();
		}

		namespace __adl_detail {

			template <typename _Range>
			using __detect_begin = decltype(begin(::std::declval<_Range>()));

			template <typename _Range>
			using __detect_cbegin = decltype(rbegin(::std::declval<_Range>()));

			template <typename _Range>
			using __detect_rbegin = decltype(cbegin(::std::declval<_Range>()));

			template <typename _Range>
			using __detect_crbegin = decltype(crbegin(::std::declval<_Range>()));

			template <typename _Range>
			using __detect_end = decltype(end(::std::declval<_Range>()));

			template <typename _Range>
			using __detect_cend = decltype(rend(::std::declval<_Range>()));

			template <typename _Range>
			using __detect_rend = decltype(cend(::std::declval<_Range>()));

			template <typename _Range>
			using __detect_crend = decltype(crend(::std::declval<_Range>()));

			template <typename _Range>
			constexpr bool __begin_noexcept() noexcept {
				if constexpr (::std::is_array_v<remove_cvref_t<_Range>>) {
					return true;
				}
				else if constexpr (is_detected_v<__detect_begin, _Range>) {
					return noexcept(begin(::std::declval<_Range>()));
				}
				else {
					return noexcept(::std::declval<_Range>().begin());
				}
			}

			template <typename _Range>
			constexpr bool __cbegin_noexcept() noexcept {
				if constexpr (::std::is_array_v<remove_cvref_t<_Range>>) {
					return true;
				}
				else if constexpr (is_detected_v<__detect_cbegin, _Range>) {
					return noexcept(cbegin(::std::declval<_Range>()));
				}
				else {
					return noexcept(::std::declval<_Range>().cbegin());
				}
			}


			template <typename _Range>
			constexpr bool __rbegin_noexcept() noexcept {
				if constexpr (::std::is_array_v<remove_cvref_t<_Range>>) {
					return true;
				}
				else if constexpr (is_detected_v<__detect_rbegin, _Range>) {
					return noexcept(rbegin(::std::declval<_Range>()));
				}
				else {
					return noexcept(::std::declval<_Range>().rbegin());
				}
			}


			template <typename _Range>
			constexpr bool __crbegin_noexcept() noexcept {
				if constexpr (::std::is_array_v<remove_cvref_t<_Range>>) {
					return true;
				}
				else if constexpr (is_detected_v<__detect_crbegin, _Range>) {
					return noexcept(crbegin(::std::declval<_Range>()));
				}
				else {
					return noexcept(::std::declval<_Range>().crbegin());
				}
			}

			template <typename _Range>
			constexpr bool __end_noexcept() noexcept {
				if constexpr (::std::is_array_v<remove_cvref_t<_Range>>) {
					return true;
				}
				else if constexpr (is_detected_v<__detect_end, _Range>) {
					return noexcept(end(::std::declval<_Range>()));
				}
				else {
					return noexcept(::std::declval<_Range>().end());
				}
			}

			template <typename _Range>
			constexpr bool __cend_noexcept() noexcept {
				if constexpr (::std::is_array_v<remove_cvref_t<_Range>>) {
					return true;
				}
				else if constexpr (is_detected_v<__detect_cend, _Range>) {
					return noexcept(cend(::std::declval<_Range>()));
				}
				else {
					return noexcept(::std::declval<_Range>().cend());
				}
			}


			template <typename _Range>
			constexpr bool __rend_noexcept() noexcept {
				if constexpr (::std::is_array_v<remove_cvref_t<_Range>>) {
					return true;
				}
				else if constexpr (is_detected_v<__detect_rend, _Range>) {
					return noexcept(rend(::std::declval<_Range>()));
				}
				else {
					return noexcept(::std::declval<_Range>().rend());
				}
			}


			template <typename _Range>
			constexpr bool __crend_noexcept() noexcept {
				if constexpr (::std::is_array_v<remove_cvref_t<_Range>>) {
					return true;
				}
				else if constexpr (is_detected_v<__detect_crend, _Range>) {
					return noexcept(crend(::std::declval<_Range>()));
				}
				else {
					return noexcept(::std::declval<_Range>().crend());
				}
			}

			template <typename _It>
			constexpr bool __iter_move_noexcept() noexcept {
				if constexpr (::std::is_lvalue_reference_v<decltype(*::std::declval<_It>())>) {
					return noexcept(::std::move(*::std::declval<_It>()));
				}
				else {
					return noexcept(*::std::declval<_It>());
				}
			}
		} // namespace __adl_detail

		template <typename _It>
		constexpr auto iter_move(_It&& __it) noexcept(__adl_detail::__iter_move_noexcept<_It>())
			-> ::std::conditional_t<::std::is_lvalue_reference_v<decltype(*::std::forward<_It>(__it))>,
			     decltype(::std::move(*::std::forward<_It>(__it))), decltype(*::std::forward<_It>(__it))> {
			if constexpr (::std::is_lvalue_reference_v<decltype(*::std::forward<_It>(__it))>) {
				return ::std::move(*::std::forward<_It>(__it));
			}
			else {
				return *::std::forward<_It>(__it);
			}
		}

		template <typename _Range>
		constexpr decltype(auto) adl_begin(_Range&& __range) noexcept(__adl_detail::__begin_noexcept<_Range>()) {
			if constexpr (::std::is_array_v<remove_cvref_t<_Range>>) {
				return (__range + 0);
			}
			else if constexpr (is_detected_v<__adl_detail::__detect_begin, _Range>) {
				return begin(::std::forward<_Range>(__range));
			}
			else {
				return ::std::forward<_Range>(__range).begin();
			}
		}

		template <typename _Range>
		constexpr decltype(auto) adl_cbegin(_Range&& __range) noexcept(__adl_detail::__cbegin_noexcept<_Range>()) {
			if constexpr (::std::is_array_v<remove_cvref_t<_Range>>) {
				return (__range + 0);
			}
			else if constexpr (is_detected_v<__adl_detail::__detect_cbegin, _Range>) {
				return cbegin(::std::forward<_Range>(__range));
			}
			else {
				return ::std::forward<_Range>(__range).cbegin();
			}
		}

		template <typename _Range>
		constexpr decltype(auto) adl_rbegin(_Range&& __range) noexcept(__adl_detail::__rbegin_noexcept<_Range>()) {
			if constexpr (::std::is_array_v<remove_cvref_t<_Range>>) {
				return ::std::make_reverse_iterator(__range + ::std::extent_v<remove_cvref_t<_Range>>);
			}
			else if constexpr (is_detected_v<__adl_detail::__detect_rbegin, _Range>) {
				return rbegin(::std::forward<_Range>(__range));
			}
			else {
				return ::std::forward<_Range>(__range).rbegin();
			}
		}

		template <typename _Range>
		constexpr decltype(auto) adl_crbegin(_Range&& __range) noexcept(__adl_detail::__crbegin_noexcept<_Range>()) {
			if constexpr (::std::is_array_v<remove_cvref_t<_Range>>) {
				return ::std::make_reverse_iterator(__range + ::std::extent_v<remove_cvref_t<_Range>>);
			}
			else if constexpr (is_detected_v<__adl_detail::__detect_crbegin, _Range>) {
				return crbegin(::std::forward<_Range>(__range));
			}
			else {
				return ::std::forward<_Range>(__range).crbegin();
			}
		}

		template <typename _Range>
		constexpr decltype(auto) adl_end(_Range&& __range) noexcept(__adl_detail::__end_noexcept<_Range>()) {
			if constexpr (::std::is_array_v<remove_cvref_t<_Range>>) {
				return (__range + ::std::extent_v<remove_cvref_t<_Range>>);
			}
			else if constexpr (is_detected_v<__adl_detail::__detect_end, _Range>) {
				return end(::std::forward<_Range>(__range));
			}
			else {
				return ::std::forward<_Range>(__range).end();
			}
		}

		template <typename _Range>
		constexpr decltype(auto) adl_cend(_Range&& __range) noexcept(__adl_detail::__cend_noexcept<_Range>()) {
			if constexpr (::std::is_array_v<remove_cvref_t<_Range>>) {
				return (__range + ::std::extent_v<remove_cvref_t<_Range>>);
			}
			else if constexpr (is_detected_v<__adl_detail::__detect_cend, _Range>) {
				return cend(::std::forward<_Range>(__range));
			}
			else {
				return ::std::forward<_Range>(__range).cend();
			}
		}

		template <typename _Range>
		constexpr decltype(auto) adl_rend(_Range&& __range) noexcept(__adl_detail::__rend_noexcept<_Range>()) {
			if constexpr (::std::is_array_v<remove_cvref_t<_Range>>) {
				return ::std::make_reverse_iterator(__range + 0);
			}
			else if constexpr (is_detected_v<__adl_detail::__detect_rend, _Range>) {
				return rend(::std::forward<_Range>(__range));
			}
			else {
				return ::std::forward<_Range>(__range).rend();
			}
		}

		template <typename _Range>
		constexpr decltype(auto) adl_crend(_Range&& __range) noexcept(__adl_detail::__crend_noexcept<_Range>()) {
			if constexpr (::std::is_array_v<remove_cvref_t<_Range>>) {
				return ::std::make_reverse_iterator(__range + 0);
			}
			else if constexpr (is_detected_v<__adl_detail::__detect_crend, _Range>) {
				return crend(::std::forward<_Range>(__range));
			}
			else {
				return ::std::forward<_Range>(__range).crend();
			}
		}

		template <typename _Range>
		constexpr auto adl_data(_Range&& __range) noexcept(noexcept(data(::std::forward<_Range>(__range))))
			-> decltype(data(::std::forward<_Range>(__range))) {
			return data(::std::forward<_Range>(__range));
		}

		template <typename _Range>
		constexpr auto adl_size(_Range&& __range) noexcept(noexcept(size(::std::forward<_Range>(__range))))
			-> decltype(size(::std::forward<_Range>(__range))) {
			return size(::std::forward<_Range>(__range));
		}

		template <typename _Range>
		constexpr auto adl_ssize(_Range&& __range) noexcept(
			noexcept(static_cast<iterator_difference_type_t<_Range>>(size(::std::forward<_Range>(__range)))))
			-> ::std::enable_if_t<::std::numeric_limits<iterator_difference_type_t<_Range>>::digits
			          >= ::std::numeric_limits<::std::ptrdiff_t>::digits,
			     decltype(static_cast<iterator_difference_type_t<_Range>>(size(::std::forward<_Range>(__range))))> {
			return static_cast<iterator_difference_type_t<_Range>>(size(::std::forward<_Range>(__range)));
		}

		template <typename _Range>
		constexpr auto adl_ssize(_Range&& __range) noexcept(
			noexcept(static_cast<::std::ptrdiff_t>(adl_size(::std::forward<_Range>(__range)))))
			-> ::std::enable_if_t<(::std::numeric_limits<iterator_difference_type_t<_Range>>::digits
			                           < ::std::numeric_limits<::std::ptrdiff_t>::digits),
			     decltype(static_cast<::std::ptrdiff_t>(adl_size(::std::forward<_Range>(__range))))> {
			return static_cast<::std::ptrdiff_t>(adl_size(::std::forward<_Range>(__range)));
		}

		template <typename _Range>
		constexpr auto adl_empty(_Range&& __range) noexcept(noexcept(empty(::std::forward<_Range>(__range))))
			-> decltype(empty(::std::forward<_Range>(__range))) {
			return empty(::std::forward<_Range>(__range));
		}

		template <typename _It>
		constexpr auto adl_iter_move(_It&& __it) noexcept(noexcept(::std::move(*::std::forward<_It>(__it))))
			-> decltype(::std::move(*::std::forward<_It>(__it))) {
			return ::std::move(*::std::forward<_It>(__it));
		}

		template <typename _ItLeft, typename _ItRight>
		constexpr auto adl_iter_swap(_ItLeft&& __left, _ItRight&& __right) noexcept(
			noexcept(iter_swap(::std::forward<_ItLeft>(__left), ::std::forward<_ItRight>(__right))))
			-> decltype(iter_swap(::std::forward<_ItLeft>(__left), ::std::forward<_ItRight>(__right))) {
			iter_swap(::std::forward<_ItLeft>(__left), ::std::forward<_ItRight>(__right));
		}

		template <typename _ItLeft, typename _ItRight>
		constexpr auto adl_swap(_ItLeft&& __left, _ItRight&& __right) noexcept(
			noexcept(swap(::std::forward<_ItLeft>(__left), ::std::forward<_ItRight>(__right))))
			-> decltype(swap(::std::forward<_ItLeft>(__left), ::std::forward<_ItRight>(__right))) {
			swap(::std::forward<_ItLeft>(__left), ::std::forward<_ItRight>(__right));
		}
	} // namespace ranges_adl
#endif

	template <typename _Range>
	using detect_adl_size = decltype(ranges_adl::adl_size(::std::declval<::std::add_lvalue_reference_t<_Range>>()));

	template <typename _Range>
	using detect_adl_empty = decltype(ranges_adl::adl_empty(::std::declval<::std::add_lvalue_reference_t<_Range>>()));

	template <typename _Range>
	using detect_adl_begin = decltype(ranges_adl::adl_begin(::std::declval<_Range>()));

	template <typename _Range>
	using detect_adl_end = decltype(ranges_adl::adl_end(::std::declval<_Range>()));

	template <typename _Ty>
	struct is_range
	: ::std::integral_constant<bool, is_detected_v<detect_adl_begin, _Ty> && is_detected_v<detect_adl_end, _Ty>> { };

	template <typename _Ty>
	inline constexpr bool is_range_v = is_range<_Ty>::value;

	ZTD_RANGES_INLINE_ABI_NAMESPACE_CLOSE_I_
}} // namespace ztd::ranges


#if ZTD_IS_OFF(ZTD_STD_LIBRARY_BORROWED_RANGE)

namespace ztd { namespace ranges {
	// NOTE: we do not open the ABI namespace here because this is meant to be specialized without it.

	//////
	/// @brief A trait specialized by downstream classes to determine whether or not the type is a borrowed range.
	///
	/// @tparam _Range The range type that may or may not be a borrowed range.
	//////
	template <typename _Range>
	inline constexpr bool enable_borrowed_range = false;

}} // namespace ztd::ranges

#endif

namespace ztd { namespace ranges {
	ZTD_RANGES_INLINE_ABI_NAMESPACE_OPEN_I_

	//////
	/// @brief Whether or not a given type is a borrowed range or not. Used as a proxy over the standard's
	/// borrowed_range, if it exists.
	///
	/// @tparam _Range The range type that may or may not be a borrowed range.
	///
	/// @remarks This is placed in the low-level IDK library because it has to be used in multiple places, including
	/// the std::span shim if necessary.
	//////
	template <typename _Range>
	inline constexpr bool borrowed_range_v =
#if ZTD_IS_ON(ZTD_STD_LIBRARY_BORROWED_RANGE)
		::std::ranges::borrowed_range<_Range>
#else
		::ztd::ranges::is_range_v<_Range> // must have begin/end, at least!
		&& (::std::is_lvalue_reference_v<
		         _Range> || ::ztd::ranges::enable_borrowed_range<::ztd::remove_cvref_t<_Range>>)
#endif
		;

	ZTD_RANGES_INLINE_ABI_NAMESPACE_CLOSE_I_
}} // namespace ztd::ranges

#include <ztd/epilogue.hpp>

#endif // ZTD_RANGES_ADL_HPP
