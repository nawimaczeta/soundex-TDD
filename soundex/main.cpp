// soundex.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <string>
#include <iostream>
#include <algorithm>
#include <vector>
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
		std::string result{ _padding(_head() + _removeChars(_tail())) };
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

	std::string _removeChars(std::string & phrase) const {
		const std::vector<char> CHARS_TO_DELATE{ 'a', 'e', 'h', 'i', 'o', 'u', 'w', 'y' };
		std::string res;
		res.reserve(phrase.size());

		std::copy_if(begin(phrase), end(phrase), std::back_inserter(res), [&](const char &c) {
			return (std::find(cbegin(CHARS_TO_DELATE), cend(CHARS_TO_DELATE), c) == cend(CHARS_TO_DELATE));
		});

		return res;
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
	Soundex soundex("cf");

	ASSERT_THAT(soundex.get(), EndsWith("00"));
}

TEST(ASoundex, RemovesCharsAEHIOUWYFromOutput) {
	Soundex soundex("daehiouwy");

	ASSERT_THAT(soundex.get(), StrEq("d000"));
}



