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
		std::string result{ _padding(_head() + _tail()) };
		return result;
	}

private:
	std::string _phrase;

	std::string _head() const {
		return _phrase.substr(0, 1);
	}

	std::string _tail() const {
		return _phrase.substr(1, 3);
	}

	std::string _padding(std::string & phrase) const {
		size_t paddingSize = 0;
		if (phrase.size() < 4) {
			paddingSize = 4 - phrase.size();
		}
		return phrase + std::string(paddingSize, '0');
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

TEST(ASoundex, AddsThreeZerosPaddingWhenOutputStringSizeIs1) {
	Soundex soundex("b");

	ASSERT_THAT(soundex.get(), EndsWith("000"));
}

TEST(ASoundex, AddsThreeZerosPaddingWhenOutputStringSizeIs2) {
	Soundex soundex("bf");

	ASSERT_THAT(soundex.get(), EndsWith("00"));
}

TEST(ASoundex, DISABLED_RemovesCharsAEHIOUWYFromOutput) {
	Soundex soundex("caehiouwy");

	ASSERT_THAT(soundex.get(), StrEq("c000"));
}



