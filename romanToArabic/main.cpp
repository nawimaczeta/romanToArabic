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

	int toArabic() {
		auto res = _toArabicRecursive(cbegin(_roman), cend(_roman), 0);
		if (res < 0) throw ConversionError{};
		else return static_cast<uint32_t>(res);
	}

	class IllegalSymbol : public invalid_argument {
	public:
		IllegalSymbol(char symbol) :
			invalid_argument{ "Illegal roman symbol " + symbol } {}
	};

	class ConversionError : public runtime_error {
	public:
		ConversionError() :
			runtime_error{ "Conversion failed" } {}
	};
private:
	string _roman;

	int _processRomanSymbol(uint32_t value, uint32_t & previousArabic) const {
		int res;
		if (value > previousArabic) res = _negative(previousArabic);
		else res = _positive(previousArabic);
		previousArabic = value;
		return res;
	}

	int _toArabicRecursive(string::const_iterator begin, string::const_iterator end, uint32_t previousValue) const {
		if (begin != end) {
			auto res = _processRomanSymbol(_getArabic(*begin), previousValue);
			return res + _toArabicRecursive(++begin, end, previousValue);
		}
		else return _processRomanSymbol(0, previousValue);
	}

	int _negative(uint32_t num) const {
		return -_positive(num);
	}

	int _positive(uint32_t num) const {
		return static_cast<int>(num);
	}

	uint32_t _getArabic(char roman) const {
		using RomanArabicConvertItem = pair<char, uint32_t>;
		const vector<RomanArabicConvertItem> ROMAN_ARABIC_CONVERT_VECTOR{
			{ 'I', 1 },{ 'V', 5 }, {'X', 10}, {'L', 50}, {'C', 100},{ 'D', 500}, {'M', 1000}
		};

		roman = toupper(roman);
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
};

TEST(ARoman, Generates0WhenEmptyStringIsGiven) {
	ASSERT_THAT(Roman("").toArabic(), Eq(0));
}


TEST(ARoman, ThrowsWhenIllegalSymbolDetected) {
	ASSERT_THROW(Roman("a").toArabic(), Roman::IllegalSymbol);
}

TEST(ARoman, GeneratesTheSameOutputForInputInUpperAndLowerCase) {
	EXPECT_THAT(Roman("V").toArabic(), Roman("v").toArabic());
	EXPECT_THAT(Roman("MDXIII").toArabic(), Roman("mdXIiI").toArabic());
}

TEST(ARoman, GeneratesCorrectArabicFromRoman) {
	EXPECT_THAT(Roman("I").toArabic(), Eq(1));
	EXPECT_THAT(Roman("II").toArabic(), Eq(2));
	EXPECT_THAT(Roman("III").toArabic(), Eq(3));
	EXPECT_THAT(Roman("IV").toArabic(), Eq(4));
	EXPECT_THAT(Roman("V").toArabic(), Eq(5));
	EXPECT_THAT(Roman("VI").toArabic(), Eq(6));
	EXPECT_THAT(Roman("VII").toArabic(), Eq(7));
	EXPECT_THAT(Roman("VIII").toArabic(), Eq(8));
	EXPECT_THAT(Roman("IX").toArabic(), Eq(9));
	EXPECT_THAT(Roman("X").toArabic(), Eq(10));
	EXPECT_THAT(Roman("XI").toArabic(), Eq(11));
	EXPECT_THAT(Roman("XII").toArabic(), Eq(12));
	EXPECT_THAT(Roman("XIII").toArabic(), Eq(13));
	EXPECT_THAT(Roman("XIV").toArabic(), Eq(14));
	EXPECT_THAT(Roman("XV").toArabic(), Eq(15));
	EXPECT_THAT(Roman("XVI").toArabic(), Eq(16));
	EXPECT_THAT(Roman("XVII").toArabic(), Eq(17));
	EXPECT_THAT(Roman("XVIII").toArabic(), Eq(18));
	EXPECT_THAT(Roman("XIX").toArabic(), Eq(19));
	EXPECT_THAT(Roman("XX").toArabic(), Eq(20));
	EXPECT_THAT(Roman("XXI").toArabic(), Eq(21));
	EXPECT_THAT(Roman("CCLXXXVIII").toArabic(), Eq(288));
	EXPECT_THAT(Roman("MMCMXCIX").toArabic(), Eq(2999));
	EXPECT_THAT(Roman("MMMCDXLVII").toArabic(), Eq(3447));
	EXPECT_THAT(Roman("MDXIII").toArabic(), Eq(1513));
}
