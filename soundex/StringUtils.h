#pragma once

#include <string>
#include <vector>

using namespace std;

namespace StringUtils {
	string head(const string & str, size_t position);
	string tail(const string & str, size_t position);
	string removeChars(const std::string & phrase, const vector<char> & chars);
}
