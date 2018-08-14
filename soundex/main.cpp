// soundex.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <string>
#include "gmock/gmock.h"

int main(int argc, char** argv)
{
	::testing::InitGoogleMock(&argc, argv);
	auto res = RUN_ALL_TESTS();
	getchar();
    return res;
}

class Soundex {
public:
	Soundex(std::string phrase) :
		_phrase{ phrase }
	{}

	std::string get() const	{
		return "asbc";
	}

private:
	std::string _phrase;
};

TEST(ASoundex, GeneratesOutputHasFourCharacter) {
	Soundex soundex("asdfghjkl");

	ASSERT_THAT(soundex.get(), ::testing::SizeIs(4));
}

