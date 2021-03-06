#pragma once

#include "istream.h"
#include <iterator>
#include <tuple>
#include <vector>

namespace stream
{

inline istream& operator>>(istream& stream, std::vector<bool>& container)
{
	std::vector<uint8_t> vbytes;
	stream >> vbytes;

	container.reserve(vbytes.size());
	container = std::vector<bool>(vbytes.begin(), vbytes.end());

	return stream;
}

template <typename T1, typename T2>
inline istream& operator>>(istream& stream, std::pair<T1, T2>& p)
{
	std::cout << "begin pair type" << std::endl;

	stream >> p.first;
	stream >> p.second;

	std::cout << "end pair type" << std::endl;

	return stream;
}

template <typename... Args>
inline istream& operator>>(istream& stream, std::tuple<Args...>& container)
{
	std::cout << "begin tuple type" << std::endl;

	hpp::for_each(container, [&stream](auto& elem) { stream >> elem; });

	std::cout << "end tuple type" << std::endl;

	return stream;
}

} // namespace stream
