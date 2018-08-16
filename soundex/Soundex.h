#pragma once

#include <string>
#include <map>

using namespace std;

class Soundex {
public:
	Soundex(string phrase);
	string get() const;

private:
	const char NOT_A_DIGIT = '*';
	const size_t TAIL_SIZE = 3;
	string _phrase;

	string _padding(const string & phrase) const;
	string _encodeHead(const string & head) const;
	string _encodeTail(const string & tail) const;
	string _convertInput(const string & str) const;
	bool _isValid(char currentDigit, char previousDigit) const;
	bool _isDuplicate(char currentDigit, char previousDigit) const;
	bool _isConversionDone(const string & currentDigest) const;
	char _convertChar(char c) const;
};
