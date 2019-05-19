#ifndef IUNISTREAM_H
#define IUNISTREAM_H

#include "istream_concept.h"

namespace stream
{

struct istream : istream_concept<istream>
{
	template <typename T>
	void deserialize_fundamental(T& /*val*/);

	template <typename T>
	void deserialize_contiguous_container(T& container);

	template <typename T>
	void deserialize_contiguous_container_non_fundamental(T& container);

	template <typename T>
	void deserialize_contiguous_container_fundamental(T& container);

	template <typename T>
	void deserialize_associative_container(T& container);

	template <typename T>
	void deserialize_container(T& container);

	void deserialize_container_size(size_t& sz);
};

inline void istream::deserialize_container_size(size_t& sz)
{
	uint32_t s{};
	*this >> s;
	sz = size_t(s);
}

template <typename T>
inline void istream::deserialize_fundamental(T& /*val*/)
{
	// std::cout << "fundamental type" << std::endl;
}

template <typename T>
inline void istream::deserialize_contiguous_container(T& container)
{
	using underlying_type = typename traits::range_underlying_value<T>::type;
	if_constexpr(traits::is_fundamental<underlying_type>::value)
	{
		deserialize_contiguous_container_fundamental(container);
	}
	else_constexpr
	{
		deserialize_contiguous_container_non_fundamental(container);
	}
	end_if_constexpr;
}

template <typename T>
inline void istream::deserialize_contiguous_container_fundamental(T& container)
{
	using underlying_type = typename traits::range_underlying_value<T>::type;

	// read size
	size_t sz = 0;
	deserialize_container_size(sz);

	traits::container_helper<T>::resize(container, sz);
	// deserialize_contiguous(container.data(), sz * sizeof(T::value_type));
}

template <typename T>
inline void istream::deserialize_contiguous_container_non_fundamental(T& container)
{
	using underlying_type = typename traits::range_underlying_value<T>::type;

	// read size
	size_t sz = 0;
	deserialize_container_size(sz);

	traits::container_helper<T>::resize(container, sz);
	for(auto& element : container)
	{
		*this >> element;
	}
}

template <typename T>
inline void istream::deserialize_associative_container(T& container)
{
	size_t sz = 0;
	deserialize_container_size(sz);

	traits::container_helper<T>::clear(container);
	for(size_t i = 0; i < sz; ++i)
	{
		std::pair<typename T::key_type, typename T::mapped_type> element;

		*this >> element;

		container.emplace(std::move(element));
	}
}

template <typename T>
void istream::deserialize_container(T& container)
{
	size_t sz = 0;
	deserialize_container_size(sz);

	traits::container_helper<T>::resize(container, sz);
	for(auto& element : container)
	{
		*this >> element;
	}
}
} // namespace stream

#endif

#include "istream_overloads.hpp"
