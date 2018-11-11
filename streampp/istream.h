#ifndef IUNISTREAM_H
#define IUNISTREAM_H

#include "istream_concept.h"

namespace stream
{

struct istream : istream_concept<istream>
{
	template <typename T>
	void deserialize_fundamental_type(T& /*val*/);

	template <typename T>
	void deserialize_contiguous_container(T& container);

	template <typename T>
	void deserialize_associative_container(T& container);

	template <typename T>
	void deserialize_container(T& container);

	void deserialize_container_size(size_t& sz);
};

inline void istream::deserialize_container_size(size_t& sz)
{
	uint32_t s = 0;
	*this >> s;

	sz = size_t(s);
}

template <typename T>
inline void istream::deserialize_fundamental_type(T& /*val*/)
{
	//std::cout << "fundamental type" << std::endl;
}

template <typename T>
inline void istream::deserialize_contiguous_container(T& container)
{
	// read size
	size_t sz = 0;
	deserialize_container_size(sz);

	traits::container_helper<T>::resize(container, sz);
	// deserialize_contiguous(container.data(), sz * sizeof(T::value_type));
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
