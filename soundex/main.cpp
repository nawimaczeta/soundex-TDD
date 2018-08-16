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
				_encodeHead(StringUtils::head(_phrase, 1)) +
				_encodeTail(StringUtils::tail(_phrase, 1))
		};
		return result;
	}

private:
	static const StringUtils::CharVector CHARS_TO_REMOVE;
	static const std::map<char, char> CONVERT_MAP;
	std::string _phrase;

	std::string _padding(const std::string & phrase) const {
		size_t paddingSize = 0;
		if (phrase.size() < 3) {
			paddingSize = 3 - phrase.size();
		}
		return phrase + std::string(paddingSize, '0');
	}

	std::string _encodeHead(const std::string & head) const {
		return StringUtils::toUpper(head);
	}

	std::string _encodeTail(const std::string & tail) const {
		return _padding(_convertChars(tail));
	}

	std::string _convertChars(const std::string & str) const {
		std::string res;
		res.reserve(str.size());
		StringUtils::CharVector usedDigits;

		for (const auto & c : str) {
			const auto & it = CONVERT_MAP.find(tolower(c));
			if (it != cend(CONVERT_MAP)) {
				res += _ommitDuplicated(_convertChar(tolower(c)), usedDigits);
			}
		}

		return res;
	}

	std::string _ommitDuplicated(char digit, StringUtils::CharVector & usedDigits) const {
		std::string res;
		if (std::find(begin(usedDigits), end(usedDigits), digit) == end(usedDigits)) {
			res = digit;
			usedDigits.push_back(digit);
		}
		return res;
	}

	char _convertChar(char c) const {
		char res = 0;

		const auto & it = CONVERT_MAP.find(c);
		if (it != cend(CONVERT_MAP)) {
			res = (*it).second;
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

TEST(ASoundex, DISABLED_GeneratesOutputThatHasFourCharacter) {
	Soundex soundex("asdfghjkl");

	ASSERT_THAT(soundex.get(), SizeIs(4));
}

TEST(ASoundex, GeneratesOutputThatFirstLeterOfInputIsTheSameAsFirstLetterInInput) {
	Soundex soundex("qwer");

	ASSERT_THAT(soundex.get(), StartsWith("Q"));
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

	ASSERT_THAT(soundex.get(), StrEq("D000"));
}

TEST(ASoundex, ConvertsCharsToReferencedDigits) {
	Soundex soundex("ebcd");

	ASSERT_THAT(soundex.get(), StrEq("E123"));
}

TEST(ASoundex, AcceptsUpperCase) {
	Soundex soundex("fDLM");

	ASSERT_THAT(soundex.get(), StrEq("F345"));
}

TEST(ASoundex, OmitsNonAlphabetisc) {
	Soundex soundex("g!@#$%t^&*q(n)");

	ASSERT_THAT(soundex.get(), StrEq("G325"));
}

TEST(ASoundex, ReturnsFirstCharacterUpperCase) {
	Soundex soundex("hnar");

	ASSERT_THAT(soundex.get(), StrEq("H560"));
}

TEST(ASoundex, RemovesDuplicateddigitsFromOutput) {
	Soundex soundex("ilNnaArRL");

	ASSERT_THAT(soundex.get(), StrEq("I456"));
}
