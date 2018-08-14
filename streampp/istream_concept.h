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
	template <typename T>
	void deserialize_user_type(T&);

	template <typename T>
	istream_concept<Impl>& operator>>(T& val);
};

template <typename Impl>
template <typename T>
inline void istream_concept<Impl>::deserialize_user_type(T&)
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

	constexpr_if(traits::is_fundamental<T>::value)
	{
		stream_impl.deserialize_fundamental_type(val);
	}
	constexpr_else_if(traits::is_container<T>::value)
	{
		constexpr_if(traits::is_contiguous<T>::value)
		{
			stream_impl.deserialize_contiguous_container(val);
		}
		constexpr_else_if(traits::is_associative<T>::value)
		{
			stream_impl.deserialize_associative_container(val);
		}
		constexpr_else
		{
			stream_impl.deserialize_container(val);
		}
		constexpr_end_if;
	}
	constexpr_else
	{
		stream_impl.deserialize_user_type(val);
	}
	constexpr_end_if;

	return *this;
}

} // namespace stream
