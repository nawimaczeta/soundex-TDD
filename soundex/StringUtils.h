#pragma once

#include <string>
#include <vector>

using namespace std;

namespace StringUtils {
	using CharVector = vector<char>;
	string head(const string & str, size_t position);
	string tail(const string & str, size_t position);
	string removeChars(const std::string & str, const CharVector & chars);
	string trim(string & str, size_t newSize);
}
