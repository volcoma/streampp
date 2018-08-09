#pragma once
#include "ostream_concept.h"
#include "istream_concept.h"

namespace stream
{
struct ounistream : ostream_concept<ounistream>
{

};


ounistream& operator>>(ounistream& stream, const std::vector<bool>& container)
{
    std::vector<uint8_t> vbytes(container.begin(), container.end());
    stream << vbytes;
    return stream;
}


struct iunistream : istream_concept<iunistream>
{

};


iunistream& operator>>(iunistream& stream, std::vector<bool>& container)
{
    std::vector<uint8_t> vbytes(container.begin(), container.end());
    stream >> vbytes;
    return stream;
}

}
