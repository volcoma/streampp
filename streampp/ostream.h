#ifndef OUNISTREAM_H
#define OUNISTREAM_H

#include "ostream_concept.h"

namespace stream
{
class ostream : public ostream_concept<ostream>
{
public:
	template <typename T>
	void serialize_fundamental_type(const T& val);

	template <typename T>
	void serialize_contiguous_container(const T& container);

	template <typename T>
	void serialize_container(const T& container);

	void serialize_container_size(size_t sz);

private:
};

inline void ostream::serialize_container_size(size_t sz)
{
	// force uint32
	*this << uint32_t(sz);
}

template <typename T>
inline void ostream::serialize_fundamental_type(const T&)
{
}

template <typename T>
inline void ostream::serialize_contiguous_container(const T&)
{
	// const auto sz = nonstd::size(container);

	// serialize_container_size(sz);

	// serialize_sequential(stream, container.data(), sz * sizeof(T::value_type));

	// Fundamental array
}

template <typename T>
inline void ostream::serialize_container(const T& /*container*/)
{
	//	const auto sz = nonstd::size(container);

	//    serialize_container_size(sz);

	//	for(const auto& elem : container)
	//	{
	//		*this << elem;
	//	}
}

} // namespace stream

#endif

#include "ostream_overloads.hpp"