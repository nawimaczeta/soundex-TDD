#pragma once

#include <string>

using std::string;

namespace StringUtils {
	std::string head(string & str, size_t position) {
		return str.substr(0, position);
	}

	//std::string _tail() {
	//	return _phrase.substr(1, 3);
	//}

	//std::string _padding(std::string & phrase) {
	//	size_t paddingSize = 0;
	//	if (phrase.size() < 4) {
	//		paddingSize = 4 - phrase.size();
	//	}
	//	return phrase + std::string(paddingSize, '0');
	//}

	//std::string _removeChars(std::string & phrase) {
	//	std::string res;
	//	res.reserve(phrase.size());

	//	std::copy_if(begin(phrase), end(phrase), std::back_inserter(res), [](const char &c) {
	//		return !((c == 'a') || (c == 'e') || (c == 'h') || (c == 'i') ||
	//			(c == 'o') || (c == 'u') || (c == 'w') || (c == 'y'));
	//	});

	//	return res;
	//}
}
