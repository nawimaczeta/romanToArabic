// romanToArabic.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include "gmock/gmock.h"

#include <stdint.h>
#include <string>

using namespace std;

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
		return 1;
	}
private:
	string _roman;
};

TEST(ARomanToArabic, GeneratesArabic1WhenIIsGiven) {
	ASSERT_THAT(Roman("I").toArabic(), ::testing::Eq(1));
}