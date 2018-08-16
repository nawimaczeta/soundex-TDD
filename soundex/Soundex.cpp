#include "Soundex.h"
#include "StringUtils.h"

Soundex::Soundex(string phrase) :
	_phrase{ phrase }
{}

string Soundex::get() const {
	string result{
		_encodeHead(StringUtils::head(_phrase, 1)) +
		_encodeTail(StringUtils::tail(_phrase, 1))
	};
	return result;
}

string Soundex::_padding(const string & phrase) const {
	size_t paddingSize = 0;
	if (phrase.size() < 3) {
		paddingSize = 3 - phrase.size();
	}
	return phrase + string(paddingSize, '0');
}

string Soundex::_encodeHead(const string & head) const {
	return StringUtils::toUpper(head);
}

string Soundex::_encodeTail(const string & tail) const {
	return _padding(_convertInput(tail));
}

string Soundex::_convertInput(const string & str) const {
	string res;

	for (auto const & c : str) {
		if (_isConversionDone(res)) {
			break;
		}

		string digit = _convertChar(tolower(c));
		if (_isValid(digit, res)) {
			res += digit;
		}
	}

	return res;
}

bool Soundex::_isValid(const string & digit, const string & currentDigest) const {
	if ((digit.size() == 1) && !_isDuplicate(digit.at(0), currentDigest)) {
		return true;
	}
	else {
		return false;
	}
}

bool Soundex::_isDuplicate(char digit, const string & currentDigest) const {
	if (find(begin(currentDigest), end(currentDigest), digit) == end(currentDigest)) {
		return false;
	}
	else {
		return true;
	}
}

bool Soundex::_isConversionDone(const string & currentDigest) const {
	if (currentDigest.size() < 3) {
		return false;
	}
	else {
		return true;
	}
}

string Soundex::_convertChar(char c) const {
	string res;

	const auto it = CONVERT_MAP.find(c);
	if (it != cend(CONVERT_MAP)) {
		res = (*it).second;
	}
	return res;
}

const map<char, char> Soundex::CONVERT_MAP{
	{ 'b', '1' },{ 'f', '1' },{ 'p', '1' },{ 'v', '1' },
	{ 'c', '2' },{ 'g', '2' },{ 'j', '2' },{ 'k', '2' },{ 'q', '2' },{ 's', '2' },{ 'x', '2' },{ 'z', '2' },
	{ 'd', '3' },{ 't', '3' },
	{ 'l', '4' },
	{ 'm', '5' },{ 'n', '5' },
	{ 'r', '6' }
};