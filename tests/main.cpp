#include "streampp/streampp.h"
#include <array>
#include <cstdint>
#include <deque>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

template <typename T>
void check_os_type()
{
	T obj{};
	stream::ounistream os;
	os << obj;
}

template <typename T>
void check_is_type()
{
	T obj{};
	stream::iunistream is;
	is >> obj;
}


struct user_type
{
};

namespace stream
{
iunistream& operator>>(iunistream& stream, user_type&)
{
	return stream;
}

ounistream& operator<<(ounistream& stream, const user_type&)
{
	return stream;
}
} // namespace stream

int main()
{
	check_os_type<user_type>();
	check_is_type<user_type>();

	// fundamentals
	check_os_type<std::int8_t>();
	check_os_type<std::uint8_t>();
	check_os_type<std::int16_t>();
	check_os_type<std::uint16_t>();
	check_os_type<std::int32_t>();
	check_os_type<std::uint32_t>();
	check_os_type<std::int64_t>();
	check_os_type<std::uint64_t>();
	check_os_type<bool>();
	check_os_type<float>();
	check_os_type<double>();

	check_is_type<std::int8_t>();
	check_is_type<std::uint8_t>();
	check_is_type<std::int16_t>();
	check_is_type<std::uint16_t>();
	check_is_type<std::int32_t>();
	check_is_type<std::uint32_t>();
	check_is_type<std::int64_t>();
	check_is_type<std::uint64_t>();
	check_is_type<bool>();
	check_is_type<float>();
	check_is_type<double>();

    check_os_type<const char*>();
    //check_is_type<const char*>();

	// contiguous
	check_os_type<std::array<std::int8_t, 3>>();
	check_os_type<std::array<std::uint8_t, 3>>();
	check_os_type<std::array<std::int16_t, 3>>();
	check_os_type<std::array<std::uint16_t, 3>>();
	check_os_type<std::array<std::int32_t, 3>>();
	check_os_type<std::array<std::uint32_t, 3>>();
	check_os_type<std::array<std::int64_t, 3>>();
	check_os_type<std::array<std::uint64_t, 3>>();
	check_os_type<std::array<bool, 3>>();
	check_os_type<std::array<float, 3>>();
	check_os_type<std::array<double, 3>>();

	check_is_type<std::array<std::int8_t, 3>>();
	check_is_type<std::array<std::uint8_t, 3>>();
	check_is_type<std::array<std::int16_t, 3>>();
	check_is_type<std::array<std::uint16_t, 3>>();
	check_is_type<std::array<std::int32_t, 3>>();
	check_is_type<std::array<std::uint32_t, 3>>();
	check_is_type<std::array<std::int64_t, 3>>();
	check_is_type<std::array<std::uint64_t, 3>>();
	check_is_type<std::array<bool, 3>>();
	check_is_type<std::array<float, 3>>();
	check_is_type<std::array<double, 3>>();

	check_os_type<std::vector<std::int8_t>>();
	check_os_type<std::vector<std::uint8_t>>();
	check_os_type<std::vector<std::int16_t>>();
	check_os_type<std::vector<std::uint16_t>>();
	check_os_type<std::vector<std::int32_t>>();
	check_os_type<std::vector<std::uint32_t>>();
	check_os_type<std::vector<std::int64_t>>();
	check_os_type<std::vector<std::uint64_t>>();
	check_os_type<std::vector<bool>>();
	check_os_type<std::vector<float>>();
	check_os_type<std::vector<double>>();

	check_is_type<std::vector<std::int8_t>>();
	check_is_type<std::vector<std::uint8_t>>();
	check_is_type<std::vector<std::int16_t>>();
	check_is_type<std::vector<std::uint16_t>>();
	check_is_type<std::vector<std::int32_t>>();
	check_is_type<std::vector<std::uint32_t>>();
	check_is_type<std::vector<std::int64_t>>();
	check_is_type<std::vector<std::uint64_t>>();
	check_is_type<std::vector<bool>>();
	check_is_type<std::vector<float>>();
	check_is_type<std::vector<double>>();

	check_os_type<std::list<std::int8_t>>();
	check_os_type<std::list<std::uint8_t>>();
	check_os_type<std::list<std::int16_t>>();
	check_os_type<std::list<std::uint16_t>>();
	check_os_type<std::list<std::int32_t>>();
	check_os_type<std::list<std::uint32_t>>();
	check_os_type<std::list<std::int64_t>>();
	check_os_type<std::list<std::uint64_t>>();
	check_os_type<std::list<bool>>();
	check_os_type<std::list<float>>();
	check_os_type<std::list<double>>();

	check_is_type<std::list<std::int8_t>>();
	check_is_type<std::list<std::uint8_t>>();
	check_is_type<std::list<std::int16_t>>();
	check_is_type<std::list<std::uint16_t>>();
	check_is_type<std::list<std::int32_t>>();
	check_is_type<std::list<std::uint32_t>>();
	check_is_type<std::list<std::int64_t>>();
	check_is_type<std::list<std::uint64_t>>();
	check_is_type<std::list<bool>>();
	check_is_type<std::list<float>>();
	check_is_type<std::list<double>>();

	check_os_type<std::set<std::int8_t>>();
	check_os_type<std::set<std::uint8_t>>();
	check_os_type<std::set<std::int16_t>>();
	check_os_type<std::set<std::uint16_t>>();
	check_os_type<std::set<std::int32_t>>();
	check_os_type<std::set<std::uint32_t>>();
	check_os_type<std::set<std::int64_t>>();
	check_os_type<std::set<std::uint64_t>>();
	check_os_type<std::set<bool>>();
	check_os_type<std::set<float>>();
	check_os_type<std::set<double>>();

	check_is_type<std::set<std::int8_t>>();
	check_is_type<std::set<std::uint8_t>>();
	check_is_type<std::set<std::int16_t>>();
	check_is_type<std::set<std::uint16_t>>();
	check_is_type<std::set<std::int32_t>>();
	check_is_type<std::set<std::uint32_t>>();
	check_is_type<std::set<std::int64_t>>();
	check_is_type<std::set<std::uint64_t>>();
	check_is_type<std::set<bool>>();
	check_is_type<std::set<float>>();
	check_is_type<std::set<double>>();

	check_os_type<std::unordered_set<std::int8_t>>();
	check_os_type<std::unordered_set<std::uint8_t>>();
	check_os_type<std::unordered_set<std::int16_t>>();
	check_os_type<std::unordered_set<std::uint16_t>>();
	check_os_type<std::unordered_set<std::int32_t>>();
	check_os_type<std::unordered_set<std::uint32_t>>();
	check_os_type<std::unordered_set<std::int64_t>>();
	check_os_type<std::unordered_set<std::uint64_t>>();
	check_os_type<std::unordered_set<bool>>();
	check_os_type<std::unordered_set<float>>();
	check_os_type<std::unordered_set<double>>();

	check_is_type<std::unordered_set<std::int8_t>>();
	check_is_type<std::unordered_set<std::uint8_t>>();
	check_is_type<std::unordered_set<std::int16_t>>();
	check_is_type<std::unordered_set<std::uint16_t>>();
	check_is_type<std::unordered_set<std::int32_t>>();
	check_is_type<std::unordered_set<std::uint32_t>>();
	check_is_type<std::unordered_set<std::int64_t>>();
	check_is_type<std::unordered_set<std::uint64_t>>();
	check_is_type<std::unordered_set<bool>>();
	check_is_type<std::unordered_set<float>>();
	check_is_type<std::unordered_set<double>>();

	//    check_is_type<std::queue<std::int8_t>>();
	//	check_is_type<std::queue<std::uint8_t>>();
	//	check_is_type<std::queue<std::int16_t>>();
	//	check_is_type<std::queue<std::uint16_t>>();
	//	check_is_type<std::queue<std::int32_t>>();
	//	check_is_type<std::queue<std::uint32_t>>();
	//	check_is_type<std::queue<std::int64_t>>();
	//	check_is_type<std::queue<std::uint64_t>>();
	//	check_is_type<std::queue<bool>>();
	//	check_is_type<std::queue<float>>();
	//	check_is_type<std::queue<double>>();

	check_os_type<std::deque<std::int8_t>>();
	check_os_type<std::deque<std::uint8_t>>();
	check_os_type<std::deque<std::int16_t>>();
	check_os_type<std::deque<std::uint16_t>>();
	check_os_type<std::deque<std::int32_t>>();
	check_os_type<std::deque<std::uint32_t>>();
	check_os_type<std::deque<std::int64_t>>();
	check_os_type<std::deque<std::uint64_t>>();
	check_os_type<std::deque<bool>>();
	check_os_type<std::deque<float>>();
	check_os_type<std::deque<double>>();

	check_is_type<std::deque<std::int8_t>>();
	check_is_type<std::deque<std::uint8_t>>();
	check_is_type<std::deque<std::int16_t>>();
	check_is_type<std::deque<std::uint16_t>>();
	check_is_type<std::deque<std::int32_t>>();
	check_is_type<std::deque<std::uint32_t>>();
	check_is_type<std::deque<std::int64_t>>();
	check_is_type<std::deque<std::uint64_t>>();
	check_is_type<std::deque<bool>>();
	check_is_type<std::deque<float>>();
	check_is_type<std::deque<double>>();
	return 0;
}
