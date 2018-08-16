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
		return _padding(_convertInput(tail));
	}

	std::string _convertInput(const std::string & str) const {
		std::string res;

		for (auto const & c : str) {
			if (_isConversionDone(res)) {
				break;
			}

			std::string digit = _convertChar(tolower(c));
			if (_isValid(digit, res)) {
				res += digit;
			}
		}

		return res;
	}

	bool _isValid(const std::string & digit, const std::string & currentDigest) const {
		if ((digit.size() == 1) && !_isDuplicate(digit.at(0), currentDigest)) {
			return true;
		}
		else {
			return false;
		}
	}

	bool _isDuplicate(char digit, const std::string & currentDigest) const {
		if (std::find(begin(currentDigest), end(currentDigest), digit) == end(currentDigest)) {
			return false;
		}
		else {
			return true;
		}
	}

	bool _isConversionDone(const std::string & currentDigest) const {
		if (currentDigest.size() < 3) {
			return false;
		}
		else {
			return true;
		}
	}

	std::string _convertChar(char c) const {
		std::string res;

		const auto it = CONVERT_MAP.find(c);
		if (it != cend(CONVERT_MAP)) {
			res = (*it).second;
		}
		return res;
	}
};

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
