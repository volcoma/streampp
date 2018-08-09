#pragma once
#include "traits.h"
#include <iostream>
#include <string>
#include <vector>

namespace stream
{

template <typename Impl>
struct ostream_concept
{
};

// clang-format off
template <typename Impl, typename T>
std::enable_if_t
<
traits::is_fundamental_v<T> == true,
ostream_concept<Impl>&
>
// clang-format on
operator<<(ostream_concept<Impl>& stream, const T&)
{
	std::cout << "fundamental type" << std::endl;

	return stream;
}

template <typename Impl, typename... Args>
ostream_concept<Impl>& operator<<(ostream_concept<Impl>& stream, const std::tuple<Args...>& container)
{
	std::cout << "begin tuple type" << std::endl;

	nonstd::for_each(container, [&stream](const auto& elem) { stream << elem; });

	std::cout << "end tuple type" << std::endl;

	return stream;
}
template <typename Impl, typename T1, typename T2>
ostream_concept<Impl>& operator<<(ostream_concept<Impl>& stream, const std::pair<T1, T2>& p)
{
	std::cout << "begin pair type" << std::endl;

	stream << p.first;
	stream << p.second;

	std::cout << "end pair type" << std::endl;

	return stream;
}

// clang-format off
template <typename Impl, typename T>
std::enable_if_t
<
traits::is_container_v<T> == true &&
traits::is_contiguous_v<T> == true,
ostream_concept<Impl>&
>
// clang-format on
operator<<(ostream_concept<Impl>& stream, const T& container)
{
	std::cout << "begin contiguous container" << std::endl;

	auto sz = nonstd::size(container);
	stream << sz;
	// serialize_sequential(stream, container.data(), sz * sizeof(T::value_type));
	std::cout << "memcpy" << std::endl;

	std::cout << "end contiguous container" << std::endl;

	return stream;
}

// clang-format off
template <typename Impl, typename T>
std::enable_if_t
<
traits::is_container_v<T> == true &&
traits::is_contiguous_v<T> == false,
ostream_concept<Impl>&
>
// clang-format on
operator<<(ostream_concept<Impl>& stream, const T& container)
{
	std::cout << "begin non contiguous container" << std::endl;

	auto sz = nonstd::size(container);
	stream << sz;
	for(const auto& elem : container)
	{
		stream << elem;
	}

	std::cout << "end non contiguous container" << std::endl;

	return stream;
}

// clang-format off
template <typename Impl, typename T>
std::enable_if_t
<
traits::is_custom_v<T> == true,
ostream_concept<Impl>&
>
// clang-format on
operator<<(ostream_concept<Impl>& stream, const T&)
{
	using has_overloaded_operator = std::is_same<T, T>;
	static_assert(!has_overloaded_operator::value, "No overload of [operator<<] is found for this type. "
												   "Declaration should be visible at the call site.");
	return stream;
}
}
