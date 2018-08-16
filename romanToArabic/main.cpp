// romanToArabic.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include "gmock/gmock.h"

#include <stdint.h>
#include <string>

using namespace std;

using ::testing::Eq;

int main(int argc, char **argv)
{
	::testing::InitGoogleMock(&argc, argv);
	auto res = RUN_ALL_TESTS();
	getchar();
    return res;
}

class Roman {
public:
	Roman(const string & roman) : _roman{ roman } {}
	uint32_t toArabic() const {
		if (_roman.size() == 0) return 0;
		else return 1;
	}
private:
	string _roman;
};

TEST(ARoman, GeneratesArabic1WhenRomanIIsGiven) {
	ASSERT_THAT(Roman("I").toArabic(), Eq(1));
}

TEST(ARoman, Generates0WhenEmptyStringIsGiven) {
	ASSERT_THAT(Roman("").toArabic(), Eq(0));
}