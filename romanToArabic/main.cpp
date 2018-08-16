// romanToArabic.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include "gmock/gmock.h"

#include <stdint.h>
#include <string>
#include <utility>
#include <vector>
#include <algorithm>

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
		int res = 0;
		uint32_t curArabic = 0;
		uint32_t prevArabic = 0;

		for (auto it = begin(_roman); it != end(_roman); ++it) {
			curArabic = _getArabic(toupper(*it));
			if (curArabic > prevArabic) {
				res = -res;
			}
			res += curArabic;
			prevArabic = curArabic;
		}

		return res;
	}

	uint32_t _getArabic(char roman) const {
		using RomanArabicConvertItem = pair<char, uint32_t>;
		using RomanArabicConvertVector = vector<RomanArabicConvertItem>;
		const RomanArabicConvertVector ROMAN_ARABIC_CONVERT_VECTOR{
			{ 'I', 1 },{ 'V', 5 }//, {'X', 10}, {'L', 50}, {'C', 100}, {'M', 1000}
		};

		auto it = find_if(
			begin(ROMAN_ARABIC_CONVERT_VECTOR),
			end(ROMAN_ARABIC_CONVERT_VECTOR),
			[&](const RomanArabicConvertItem & item) {
				return (item.first == roman);
			}
		);

		if (it == end(ROMAN_ARABIC_CONVERT_VECTOR)) throw IllegalSymbol(roman);
		else return (*it).second;
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

TEST(ARoman, GeneratesTheSameOutputForInputInUpperAndLowerCase) {
	EXPECT_THAT(Roman("V").toArabic(), Roman("v").toArabic());
	EXPECT_THAT(Roman("I").toArabic(), Roman("i").toArabic());
}

TEST(ARoman, GeneratesArabic4WhenRomanIVIsGiven) {
	ASSERT_THAT(Roman("IV").toArabic(), Eq(4));
}
