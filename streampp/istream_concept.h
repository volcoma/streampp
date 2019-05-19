#pragma once
#include "concepts.h"
#include <iostream>
#include <string>
#include <vector>

namespace stream
{

template <typename Impl>
struct istream_concept
{
	template <typename T>
	void deserialize_custom(T&);

	template <typename T>
	istream_concept<Impl>& operator>>(T& val);
};

template <typename Impl>
template <typename T>
inline void istream_concept<Impl>::deserialize_custom(T&)
{
	using has_overloaded_operator = std::is_same<T, T>;
	static_assert(!has_overloaded_operator::value, "No overload of [operator>>] is found for this type. "
												   "Declaration should be visible at the call site.");
}


template <typename Impl>
template <typename T>
inline istream_concept<Impl>& istream_concept<Impl>::operator>>(T& val)
{
	auto& stream_impl = static_cast<Impl&>(*this);

	if_constexpr(traits::is_fundamental<T>::value)
	{
		stream_impl.deserialize_fundamental(val);
	}
	else_if_constexpr(traits::is_container<T>::value)
	{
		if_constexpr(traits::is_contiguous<T>::value)
		{
			stream_impl.deserialize_contiguous_container(val);
		}
		else_if_constexpr(traits::is_associative<T>::value)
		{
			stream_impl.deserialize_associative_container(val);
		}
		else_constexpr
		{
			stream_impl.deserialize_container(val);
		}
		end_if_constexpr;
	}
	else_constexpr
	{
		stream_impl.deserialize_custom(val);
	}
	end_if_constexpr;

	return *this;
}

} // namespace stream
