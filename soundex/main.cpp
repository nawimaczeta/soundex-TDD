// soundex.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <string>
#include <iostream>
#include "gmock/gmock.h"

int main(int argc, char** argv)
{
	::testing::InitGoogleMock(&argc, argv);
	auto res = RUN_ALL_TESTS();
	getchar();
    return res;
}

using namespace testing;

class Soundex {
public:
	Soundex(std::string phrase) :
		_phrase{ phrase }
	{}

	std::string get() const	{
		return _head() + "000";
	}

private:
	std::string _phrase;

	std::string _head() const {
		return _phrase.substr(0, 1);
	}
};

TEST(ASoundex, GeneratesOutputThatHasFourCharacter) {
	Soundex soundex("asdfghjkl");

	ASSERT_THAT(soundex.get(), SizeIs(4));
}

TEST(ASoundex, GeneratesOutputThatFirstLeterOfInputIsTheSameAsFirstLetterInInput) {
	Soundex soundex("qwer");

	ASSERT_THAT(soundex.get(), StartsWith("q"));
}

TEST(ASoundex, AddsZeroPaddingWhenOutputStringSizeIsSmallerThen4) {
	Soundex soundex("b");

	ASSERT_THAT(soundex.get(), StrEq("b000"));
}



