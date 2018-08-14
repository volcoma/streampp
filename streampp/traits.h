#pragma once
#include "detail/type_traits.hpp"
#include "detail/utility.hpp"
#include <iostream>
#include <string>
#include <vector>

namespace nonstd
{

template <class C>
inline constexpr auto size(const C& c) -> decltype(c.size())
{
	return c.size();
}
template <class T, std::size_t N>
inline constexpr std::size_t size(const T (&)[N]) noexcept
{
	return N;
}

inline std::size_t size(const char* c) noexcept
{
	return std::strlen(c);
}
} // namespace nonstd

namespace traits
{

template <typename T>
struct has_contiguous_storage : std::false_type
{
};

template <typename T, typename U>
struct has_contiguous_storage<std::vector<T, U>> : std::true_type
{
};

template <typename T>
struct has_contiguous_storage<std::vector<bool, T>> : std::false_type
{
};

template <typename T, typename U, typename V>
struct has_contiguous_storage<std::basic_string<T, U, V>> : std::true_type
{
};

template <typename T, std::size_t N>
struct has_contiguous_storage<std::array<T, N>> : std::true_type
{
};

template <typename T>
struct has_contiguous_storage<T[]> : std::true_type
{
};

template <typename T, std::size_t N>
struct has_contiguous_storage<T[N]> : std::true_type
{
};

template <>
struct has_contiguous_storage<const char*> : std::true_type
{
};

template <typename T>
using has_begin = decltype(std::begin(std::declval<const T>()));
template <typename T>
using has_end = decltype(std::end(std::declval<const T>()));
template <typename T>
using has_size = decltype(nonstd::size(std::declval<const T>()));
template <typename T>
using has_clear = decltype(std::declval<T>().clear());
template <typename T>
using has_resize = decltype(std::declval<T>().resize(std::declval<size_t>()));

template <typename T>
using has_key_type = typename T::key_type;
template <typename T>
using has_mapped_type = typename T::mapped_type;

template <typename T>
using is_range = nonstd::conjunction<nonstd::is_detected<has_begin, T>, nonstd::is_detected<has_end, T>>;

template <typename T>
using is_container = nonstd::conjunction<is_range<T>, nonstd::is_detected<has_size, T>>;

template <typename T>
using is_contiguous = has_contiguous_storage<T>;

template <typename T>
using is_associative =
	nonstd::conjunction<nonstd::is_detected<has_key_type, T>, nonstd::is_detected<has_mapped_type, T>>;

template <typename T>
using is_clearable = nonstd::conjunction<is_container<T>, nonstd::is_detected<has_clear, T>>;

template <typename T>
using is_resizeable = nonstd::conjunction<is_container<T>, nonstd::is_detected<has_resize, T>>;

template <typename T>
using is_fundamental = nonstd::disjunction<std::is_fundamental<T>, std::is_enum<T>>;

template <typename T>
using is_integral = nonstd::disjunction<std::is_fundamental<T>, std::is_enum<T>>;


template <class Iterator>
struct iterator_value
{
	using type = typename std::iterator_traits<Iterator>::value_type;
};
template <class T>
struct range_underlying_value : iterator_value<decltype(std::cbegin(std::declval<T>()))>
{
};

template <>
struct range_underlying_value<const char*> : iterator_value<const char*>
{
};

template <typename T>
struct container_helper
{

	static void resize(T& val, size_t sz)
	{
		constexpr_if(traits::is_resizeable<T>::value)
		{
			val.resize(sz);
		}
		constexpr_end_if;
	}

	static void clear(T& val)
	{
		constexpr_if(traits::is_clearable<T>::value)
		{
			val.clear();
		}
		constexpr_end_if;
	}
};

} // namespace traits
