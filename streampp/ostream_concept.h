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
	template <typename T>
	void serialize_user_type(const T&);

    template <typename T>
    ostream_concept& operator<<(const T& val);
};

template <typename Impl>
template <typename T>
inline void ostream_concept<Impl>::serialize_user_type(const T&)
{
    using has_overloaded_operator = std::is_same<T, T>;
    static_assert(!has_overloaded_operator::value, "No overload of [operator<<] is found for this type. "
                                                   "Declaration should be visible at the call site.");
}

template <typename Impl>
template <typename T>
inline ostream_concept<Impl>& ostream_concept<Impl>::operator<<(const T& val)
{
	auto& stream_impl = static_cast<Impl&>(*this);

    if_constexpr(traits::is_fundamental<T>::value)
	{
		stream_impl.serialize_fundamental_type(val);
	}
	else_if_constexpr(traits::is_container<T>::value)
	{
		if_constexpr(traits::is_contiguous<T>::value)
		{
			stream_impl.serialize_contiguous_container(val);
		}
		else_constexpr
		{
			stream_impl.serialize_container(val);
		}
		end_if_constexpr;
	}
    else_if_constexpr(std::is_same<T, const char*>::value)
	{
        stream_impl.serialize_contiguous_container(val);
    }
	else_constexpr
	{
		stream_impl.serialize_user_type(val);
	}
	end_if_constexpr;

	return *this;
}

} // namespace stream
