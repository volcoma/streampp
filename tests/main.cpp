#include <array>
#include <cstdint>
#include <deque>
#include <list>
#include <map>
#include <queue>
#include <set>
#include <streampp/streampp.h>
#include <string>
#include <suitepp/suitepp/suitepp.hpp>
#include <unordered_map>
#include <unordered_set>
#include <vector>

template <typename T>
void check_os_type()
{
	T obj{};
	stream::ostream os;
	os << obj;
}

template <typename T>
void check_is_type()
{
	T obj{};
	stream::istream is;
	is >> obj;
}

struct user_type
{
};

namespace stream
{
istream& operator>>(istream& stream, user_type&)
{
	return stream;
}

ostream& operator<<(ostream& stream, const user_type&)
{
	return stream;
}
} // namespace stream

void test_traits()
{

    enum class my_enum : std::uint32_t
    {
        one,
        two
    };

	suitepp::test("test traits", [&]() {

		EXPECT(traits::is_fundamental<std::int8_t>::value == true);
		EXPECT(traits::is_fundamental<std::uint8_t>::value == true);
		EXPECT(traits::is_fundamental<std::int16_t>::value == true);
		EXPECT(traits::is_fundamental<std::uint16_t>::value == true);
		EXPECT(traits::is_fundamental<std::int32_t>::value == true);
		EXPECT(traits::is_fundamental<std::uint32_t>::value == true);
		EXPECT(traits::is_fundamental<std::int64_t>::value == true);
		EXPECT(traits::is_fundamental<std::uint64_t>::value == true);
		EXPECT(traits::is_fundamental<bool>::value == true);
		EXPECT(traits::is_fundamental<float>::value == true);
		EXPECT(traits::is_fundamental<double>::value == true);
        EXPECT(traits::is_fundamental<my_enum>::value == true);

        EXPECT(traits::is_fundamental<std::string>::value == false);

        EXPECT(traits::is_integral<std::int8_t>::value == true);
		EXPECT(traits::is_integral<std::uint8_t>::value == true);
		EXPECT(traits::is_integral<std::int16_t>::value == true);
		EXPECT(traits::is_integral<std::uint16_t>::value == true);
		EXPECT(traits::is_integral<std::int32_t>::value == true);
		EXPECT(traits::is_integral<std::uint32_t>::value == true);
		EXPECT(traits::is_integral<std::int64_t>::value == true);
		EXPECT(traits::is_integral<std::uint64_t>::value == true);
		EXPECT(traits::is_integral<bool>::value == true);
		EXPECT(traits::is_integral<float>::value == false);
		EXPECT(traits::is_integral<double>::value == false);
        EXPECT(traits::is_integral<my_enum>::value == true);

        EXPECT(traits::is_fundamental<std::string>::value == false);

        EXPECT(traits::is_container<std::vector<std::int8_t>>::value == true);
        EXPECT((traits::is_container<std::array<std::int8_t, 2>>::value == true));
        EXPECT(traits::is_container<std::list<std::int8_t>>::value == true);
        EXPECT(traits::is_container<std::set<std::int8_t>>::value == true);
        EXPECT(traits::is_container<std::unordered_set<std::int8_t>>::value == true);
        //EXPECT(traits::is_container<std::queue<std::int8_t>>::value == true);
        EXPECT(traits::is_container<std::deque<std::int8_t>>::value == true);
        EXPECT((traits::is_container<std::map<std::int8_t, std::int8_t>>::value == true));
        EXPECT((traits::is_container<std::unordered_map<std::int8_t, std::int8_t>>::value == true));

        EXPECT(traits::is_container<std::int8_t>::value == false);


        EXPECT(traits::is_contiguous<const char*>::value == true);
        EXPECT(traits::is_contiguous<std::vector<std::int8_t>>::value == true);
        EXPECT((traits::is_contiguous<std::array<std::int8_t, 2>>::value == true));

        EXPECT(traits::is_contiguous<std::list<std::int8_t>>::value == false);
        EXPECT(traits::is_contiguous<std::set<std::int8_t>>::value == false);
        EXPECT(traits::is_contiguous<std::unordered_set<std::int8_t>>::value == false);
        EXPECT(traits::is_contiguous<std::queue<std::int8_t>>::value == false);
        EXPECT(traits::is_contiguous<std::deque<std::int8_t>>::value == false);
        EXPECT((traits::is_contiguous<std::map<std::int8_t, std::int8_t>>::value == false));
        EXPECT((traits::is_contiguous<std::unordered_map<std::int8_t, std::int8_t>>::value == false));
        EXPECT(traits::is_contiguous<std::int8_t>::value == false);


        EXPECT((traits::is_associative<std::map<std::int8_t, std::int8_t>>::value == true));
        EXPECT((traits::is_associative<std::unordered_map<std::int8_t, std::int8_t>>::value == true));

        EXPECT(traits::is_associative<const char*>::value == false);
        EXPECT(traits::is_associative<std::vector<std::int8_t>>::value == false);
        EXPECT((traits::is_associative<std::array<std::int8_t, 2>>::value == false));
        EXPECT(traits::is_associative<std::list<std::int8_t>>::value == false);
        EXPECT(traits::is_associative<std::set<std::int8_t>>::value == false);
        EXPECT(traits::is_associative<std::unordered_set<std::int8_t>>::value == false);
        EXPECT(traits::is_associative<std::queue<std::int8_t>>::value == false);
        EXPECT(traits::is_associative<std::deque<std::int8_t>>::value == false);
        EXPECT(traits::is_associative<std::int8_t>::value == false);

        EXPECT((std::is_same<traits::range_underlying_value<const char*>::type, char>::value == true));
        EXPECT((std::is_same<traits::range_underlying_value<std::array<std::int8_t, 2>>::type, std::int8_t>::value == true));
        EXPECT((std::is_same<traits::range_underlying_value<std::list<std::int8_t>>::type, std::int8_t>::value == true));
        EXPECT((std::is_same<traits::range_underlying_value<std::set<std::int8_t>>::type, std::int8_t>::value == true));
        EXPECT((std::is_same<traits::range_underlying_value<std::unordered_set<std::int8_t>>::type, std::int8_t>::value == true));
        EXPECT((std::is_same<traits::range_underlying_value<std::deque<std::int8_t>>::type, std::int8_t>::value == true));

    });
}

int main()
{
    test_traits();

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
	// check_is_type<const char*>();

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

	//  check_is_type<std::queue<std::int8_t>>();
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
