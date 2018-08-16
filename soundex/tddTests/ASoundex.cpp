#include "gmock/gmock.h"
#include "Soundex.h"

using namespace testing;

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

TEST(ASoundex, DoesNotCombineDuplicateEncodingsSeparatedByVowels) {
	Soundex soundex("jbob");

	ASSERT_THAT(soundex.get(), StrEq("J110"));
}
