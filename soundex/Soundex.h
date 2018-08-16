#pragma once

#include <string>
#include <map>

using namespace std;

class Soundex {
public:
	Soundex(string phrase);
	string get() const;

private:
	static const map<char, char> CONVERT_MAP;
	string _phrase;

	string _padding(const string & phrase) const;
	string _encodeHead(const string & head) const;
	string _encodeTail(const string & tail) const;
	string _convertInput(const string & str) const;
	bool _isValid(const string & digit, const string & currentDigest) const;
	bool _isDuplicate(char digit, const string & currentDigest) const;
	bool _isConversionDone(const string & currentDigest) const;
	string _convertChar(char c) const;
};
