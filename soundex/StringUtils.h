#pragma once

#include <string>
#include <vector>

using namespace std;

namespace StringUtils {
	string head(const string & str, size_t position);
	string tail(const string & str, size_t position);
	string removeChars(const std::string & str, const vector<char> & chars);
	string trim(std::string & str, size_t newSize);
}
