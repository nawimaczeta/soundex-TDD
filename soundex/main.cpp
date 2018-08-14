// soundex.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <string>
#include <iostream>

#include "gmock/gmock.h"
#include "StringUtils.h"

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
		std::string result{ 
			_padding(StringUtils::trim(
				StringUtils::head(_phrase, 1) + 
				StringUtils::removeChars(StringUtils::tail(_phrase, 1), CHARS_TO_REMOVE), 4)) 
		};
		return result;
	}

private:
	static const vector<char> CHARS_TO_REMOVE;
	std::string _phrase;

	std::string _padding(std::string & phrase) const {
		size_t paddingSize = 0;
		if (phrase.size() < 4) {
			paddingSize = 4 - phrase.size();
		}
		return phrase + std::string(paddingSize, '0');
	}
};

const vector<char> Soundex::CHARS_TO_REMOVE{ 'a', 'e', 'h', 'i', 'o', 'u', 'w', 'y' };

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
	Soundex soundex("cf");

	ASSERT_THAT(soundex.get(), EndsWith("00"));
}

TEST(ASoundex, RemovesCharsAEHIOUWYFromOutput) {
	Soundex soundex("daehiouwy");

	ASSERT_THAT(soundex.get(), StrEq("d000"));
}



