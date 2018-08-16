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

	std::string removeChars(const std::string & str, const CharVector & chars) {
		std::string res;
		res.reserve(str.size());

		std::copy_if(begin(str), end(str), back_inserter(res), [&](const char &c) {
			return (std::find(cbegin(chars), cend(chars), c) == cend(chars));
		});

		return res;
	}

	string trim(std::string & str, size_t newSize) {
		return head(str, newSize);
	}

	string toUpper(const string & str)
	{
		std::string res;
		transform(cbegin(str), cend(str), back_inserter(res), ::toupper);
		return res;
	}
}