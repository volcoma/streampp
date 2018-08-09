#pragma once
#include "detail/type_traits.hpp"
#include "detail/utility.hpp"
#include <iostream>
#include <string>
#include <vector>

namespace nonstd
{

template <class C>
constexpr auto size(const C& c) -> decltype(c.size())
{
	return c.size();
}
template <class T, std::size_t N>
constexpr std::size_t size(const T (&)[N]) noexcept
{
	return N;
}
}

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

template <class T>
static constexpr auto is_range_v = is_range<T>::value;

template <typename T>
using is_container = nonstd::conjunction<is_range<T>, nonstd::is_detected<has_size, T>>;

template <class T>
static constexpr auto is_container_v = is_container<T>::value;

template <typename T>
using is_contiguous = has_contiguous_storage<T>;

template <class T>
static constexpr auto is_contiguous_v = is_contiguous<T>::value;

template <typename T>
using is_associative =
	nonstd::conjunction<nonstd::is_detected<has_key_type, T>, nonstd::is_detected<has_mapped_type, T>>;

template <class T>
static constexpr auto is_associative_v = is_associative<T>::value;

template <typename T>
using is_clearable = nonstd::conjunction<is_container<T>, nonstd::is_detected<has_clear, T>>;

template <class T>
static constexpr auto is_clearable_v = is_clearable<T>::value;

template <typename T>
using is_resizeable = nonstd::conjunction<is_container<T>, nonstd::is_detected<has_resize, T>>;

template <class T>
static constexpr auto is_resizeable_v = is_resizeable<T>::value;

template <typename T>
using is_fundamental = nonstd::disjunction<std::is_fundamental<T>, std::is_enum<T>>;

template <class T>
static constexpr auto is_fundamental_v = is_fundamental<T>::value;

template <typename T>
using is_custom = nonstd::negation<nonstd::disjunction<is_fundamental<T>, is_container<T>>>;

template <class T>
static constexpr auto is_custom_v = is_custom<T>::value;



template <typename T>
struct container_helper
{

	static void resize(T& cont, size_t sz, std::true_type)
	{
		cont.resize(sz);
	}

	static void resize(T&, size_t, std::false_type)
	{
	}

	static void clear(T& cont, std::true_type)
	{
		cont.clear();
	}

	static void clear(T&, std::false_type)
	{
	}
};

}
