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
		uint32_t res = 0;

		if (!(_roman.size() == 0)) {
			char c = _roman.back();
			switch (c) {
			case 'I':
				res = 1;
				break;
			case 'V':
				res = 5;
				break;
			default:
				throw IllegalSymbol(c);
			}
		}

		return res;
	}

	class IllegalSymbol : public invalid_argument {
	public:
		IllegalSymbol(char symbol) : 
			invalid_argument{ "Illegal roman symbol " + symbol } {}
	};
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

TEST(ARoman, ThrowsWhenIllegalSymbolDetected) {
	ASSERT_THROW(Roman("a").toArabic(), Roman::IllegalSymbol);
}
