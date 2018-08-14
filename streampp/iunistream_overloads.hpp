#pragma once

#include "iunistream.h"
#include <vector>
#include <tuple>
#include <iterator>

namespace stream
{

inline iunistream& operator>>(iunistream& stream, std::vector<bool>& container)
{
	std::vector<uint8_t> vbytes;
	stream >> vbytes;

    container.reserve(vbytes.size());
    //std::copy(std::begin(vbytes), std::end(vbytes), std::back_inserter(container));
    //container = std::vector<bool>(vbytes.begin(), vbytes.end());

	return stream;
}

template <typename T1, typename T2>
inline iunistream& operator>>(iunistream& stream, std::pair<T1, T2>& p)
{
	std::cout << "begin pair type" << std::endl;

	stream >> p.first;
	stream >> p.second;

	std::cout << "end pair type" << std::endl;

	return stream;
}

template <typename... Args>
inline iunistream& operator>>(iunistream& stream, std::tuple<Args...>& container)
{
	std::cout << "begin tuple type" << std::endl;

	nonstd::for_each(container, [&stream](auto& elem) { stream >> elem; });

	std::cout << "end tuple type" << std::endl;

	return stream;
}

} // namespace stream
