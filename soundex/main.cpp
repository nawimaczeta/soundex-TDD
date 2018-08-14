// soundex.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <string>
#include <iostream>
#include <map>

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
				_encodeTail(StringUtils::tail(_phrase, 1)), 4))
		};
		return result;
	}

private:
	static const StringUtils::CharVector CHARS_TO_REMOVE;
	static const std::map<char, char> CONVERT_MAP;
	std::string _phrase;

	std::string _padding(std::string & phrase) const {
		size_t paddingSize = 0;
		if (phrase.size() < 4) {
			paddingSize = 4 - phrase.size();
		}
		return phrase + std::string(paddingSize, '0');
	}

	std::string _encodeTail(std::string tail) const {
		return _convertChars(tail);
	}

	std::string _convertChars(std::string & str) const {
		std::string res;
		res.reserve(str.size());

		for (const auto & s : str) {
			const auto & it = CONVERT_MAP.find(tolower(s));
			if (it != cend(CONVERT_MAP)) {
				res += (*it).second;
			}
		}

		return res;
	}
};

const vector<char> Soundex::CHARS_TO_REMOVE{ 'a', 'e', 'h', 'i', 'o', 'u', 'w', 'y' };
const std::map<char, char> Soundex::CONVERT_MAP{
	{ 'b', '1' },{ 'f', '1' },{ 'p', '1' },{ 'v', '1' },
	{ 'c', '2' },{ 'g', '2' },{ 'j', '2' },{ 'k', '2' },{ 'q', '2' },{ 's', '2' },{ 'x', '2' },{ 'z', '2' },
	{ 'd', '3' },{ 't', '3' },
	{ 'l', '4' },
	{ 'm', '5' },{ 'n', '5' },
	{ 'r', '6' }
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

TEST(ASoundex, ConvertsCharsToReferencedDigits) {
	Soundex soundex("ebcd");

	ASSERT_THAT(soundex.get(), StrEq("e123"));
}

TEST(ASoundex, AcceptsUpperCase) {
	Soundex soundex("fDLM");

	ASSERT_THAT(soundex.get(), StrEq("f345"));
}

TEST(ASoundex, OmitsNonAlphabetisc) {
	Soundex soundex("g!@#$%^&*()");

	ASSERT_THAT(soundex.get(), StrEq("g000"));
}



