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
		uint32_t res;

		if (_roman.size() == 0) res = 0;
		else {
			char c = _roman.back();
			switch (c) {
			case 'I':
				res = 1;
				break;
			case 'V':
				res = 5;
				break;
			}
		}

		return res;
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

TEST(ARoman, GeneratesArabic5WhenRomanVIsGiven) {
	ASSERT_THAT(Roman("V").toArabic(), Eq(5));
}
