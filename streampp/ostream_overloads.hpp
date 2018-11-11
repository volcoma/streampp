#pragma once
#include "ostream.h"

namespace stream
{

inline ostream& operator<<(ostream& stream, const std::vector<bool>& container)
{
	std::vector<uint8_t> vbytes(container.begin(), container.end());
	stream << vbytes;
	return stream;
}

template <typename... Args>
ostream& operator<<(ostream& stream, const std::tuple<Args...>& container)
{
	std::cout << "begin tuple type" << std::endl;
	hpp::for_each(container, [&stream](const auto& elem) { stream << elem; });
	std::cout << "end tuple type" << std::endl;
	return stream;
}

template <typename T1, typename T2>
ostream& operator<<(ostream& stream, const std::pair<T1, T2>& p)
{
	std::cout << "begin pair type" << std::endl;
	stream << p.first;
	stream << p.second;
	std::cout << "end pair type" << std::endl;
	return stream;
}

} // namespace stream
