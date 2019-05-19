#ifndef OUNISTREAM_H
#define OUNISTREAM_H

#include "ostream_concept.h"

namespace stream
{
class ostream : public ostream_concept<ostream>
{
public:
	template <typename T>
	void serialize_fundamental(const T& val);

	template <typename T>
	void serialize_contiguous_container(const T& container);
	template <typename T>
	void serialize_contiguous_container_fundamental(const T& container);
	template <typename T>
	void serialize_contiguous_container_non_fundamental(const T& container);

	template <typename T>
	void serialize_container(const T& container);

	void serialize_container_size(size_t sz);

	template <typename T>
	void serialize_type();

	uint8_t* alloc_storage(size_t size);

private:
	template <typename T>
	static uint8_t encode_type();

	std::vector<uint8_t> storage_{};
	std::vector<uint8_t>* storage_ptr_ = nullptr; // non owning
	size_t front_idx_{};
	size_t end_idx_{}; // not indexable (last idx + 1)
	size_t payload_idx_{};
};

inline void ostream::serialize_container_size(size_t sz)
{
	// force uint32
	*this << uint32_t(sz);
}

template <typename T>
inline void ostream::serialize_fundamental(const T& val)
{
	serialize_type<T>();
}

template <typename T>
inline void ostream::serialize_type()
{
	*this << encode_type<T>();
}

template <typename T>
inline uint8_t ostream::encode_type()
{
	uint8_t encoded{};
	return encoded;
}

inline uint8_t* ostream::alloc_storage(size_t size)
{
	if((end_idx_ - payload_idx_) < size)
	{
		if(end_idx_ != storage_ptr_->size())
		{
			throw std::runtime_error("Probably bad using of inplaced streams");
		}
		size_t missing = size - (end_idx_ - payload_idx_);
		storage_ptr_->resize(storage_ptr_->size() * 2 + missing);
		end_idx_ = storage_ptr_->size();
	}
	uint8_t* ptr = storage_ptr_->data() + payload_idx_;
	payload_idx_ += size;
	return ptr;
}

template <typename T>
inline void ostream::serialize_contiguous_container(const T& container)
{

	using underlying_type = typename traits::range_underlying_value<T>::type;

	serialize_type<underlying_type>();
	const auto sz = hpp::size(container);
	serialize_container_size(sz);

	if_constexpr(traits::is_fundamental<underlying_type>::value)
	{
		serialize_contiguous_container_fundamental(container);
	}
	else_constexpr
	{
		serialize_contiguous_container_non_fundamental(container);
	}
	end_if_constexpr;
}

template <typename T>
inline void ostream::serialize_contiguous_container_fundamental(const T& container)
{
	using underlying_type = typename traits::range_underlying_value<T>::type;
	const auto sz = hpp::size(container);
	const auto data_sz = sz * sizeof(underlying_type);

	auto ptr = alloc_storage(data_sz);

	std::memcpy(ptr, hpp::data(container), data_sz);
}

template <typename T>
inline void ostream::serialize_contiguous_container_non_fundamental(const T& container)
{
	using underlying_type = typename traits::range_underlying_value<T>::type;
}

template <typename T>
inline void ostream::serialize_container(const T& container)
{
	const auto sz = hpp::size(container);
	serialize_container_size(sz);

	for(const auto& elem : container)
	{
		*this << elem;
	}
}

} // namespace stream

#endif

#include "ostream_overloads.hpp"
