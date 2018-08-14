#include "StringUtils.h"

#include <iterator>
#include <algorithm>

namespace StringUtils {
	std::string head(const string & str, size_t position) {
		return str.substr(0, position);
	}

	std::string tail(const string & str, size_t position) {
		return str.substr(position);
	}

	std::string removeChars(const std::string & phrase, const vector<char> & chars) {
		std::string res;
		res.reserve(phrase.size());

		std::copy_if(begin(phrase), end(phrase), back_inserter(res), [&](const char &c) {
			return (std::find(cbegin(chars), cend(chars), c) == cend(chars));
		});

		return res;
	}
}