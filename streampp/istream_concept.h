#pragma once
#include "traits.h"
#include <iostream>
#include <string>
#include <vector>

namespace stream
{

template <typename Impl>
struct istream_concept
{
};

// clang-format off
template <typename Impl, typename T>
std::enable_if_t
<
traits::is_fundamental_v<T> == true,
istream_concept<Impl>&
>
// clang-format on
operator>>(istream_concept<Impl>& stream, T&)
{
	std::cout << "fundamental type" << std::endl;
	return stream;
}

template <typename Impl, typename T1, typename T2>
istream_concept<Impl>& operator>>(istream_concept<Impl>& stream, std::pair<T1, T2>& p)
{
	std::cout << "begin pair type" << std::endl;

	stream >> p.first;
	stream >> p.second;

	std::cout << "end pair type" << std::endl;

	return stream;
}

template <typename Impl, typename... Args>
istream_concept<Impl>& operator>>(istream_concept<Impl>& stream, std::tuple<Args...>& container)
{
	std::cout << "begin tuple type" << std::endl;

	nonstd::for_each(container, [&stream](auto& elem) { stream >> elem; });

	std::cout << "end tuple type" << std::endl;

	return stream;
}

// clang-format off
template <typename Impl, typename T>
std::enable_if_t
<
traits::is_container_v<T> == true &&
traits::is_contiguous_v<T> == true,
istream_concept<Impl>&
>
// clang-format on
operator>>(istream_concept<Impl>& stream, T& container)
{
	std::cout << "begin contiguous container" << std::endl;
	size_t sz = 0;
	stream >> sz;
	// assert(sz >= std::size(container));
	traits::container_helper<T>::resize(container, sz, traits::is_resizeable<T>());
	// deserialize_contiguous(container.data(), sz * sizeof(T::value_type));
	std::cout << "memcpy data" << std::endl;

	std::cout << "end contiguous container" << std::endl;

	return stream;
}

// clang-format off
template <typename Impl, typename T>
std::enable_if_t
<
traits::is_container<T>::value == true &&
traits::is_contiguous<T>::value == false &&
traits::is_associative<T>::value == false,
istream_concept<Impl>&
>
// clang-format on
operator>>(istream_concept<Impl>& stream, T& container)
{
	std::cout << "begin non contiguous non associative container" << std::endl;
	size_t sz = 0;
	stream >> sz;
	traits::container_helper<T>::resize(container, sz, traits::is_resizeable<T>());
	for(auto& element : container)
	{
		stream >> element;
	}
	std::cout << "end non contiguous non associative container" << std::endl;

	return stream;
}

// clang-format off
template <typename Impl, typename T>
std::enable_if_t
<
traits::is_container_v<T> == true &&
traits::is_contiguous_v<T> == false &&
traits::is_associative_v<T> == true,
istream_concept<Impl>&
>
// clang-format on
operator>>(istream_concept<Impl>& stream, T& container)
{
	std::cout << "begin associative container" << std::endl;

	size_t sz = 0;
	stream >> sz;
	traits::container_helper<T>::clear(container, traits::is_clearable<T>());
	for(size_t i = 0; i < sz; ++i)
	{
		std::pair<typename T::key_type, typename T::mapped_type> element;
		stream >> element;

		container.emplace(std::move(element));
	}
	std::cout << "end associative container" << std::endl;

	return stream;
}

// clang-format off
template <typename Impl, typename T>
std::enable_if_t
<
traits::is_custom_v<T> == true,
istream_concept<Impl>&
>
// clang-format on
operator>>(istream_concept<Impl>& stream, T&)
{
	using has_overloaded_operator = std::is_same<T, T>;
	static_assert(!has_overloaded_operator::value, "No overload of [operator>>] is found for this type. "
												   "Declaration should be visible at the call site.");
	return stream;
}
}
