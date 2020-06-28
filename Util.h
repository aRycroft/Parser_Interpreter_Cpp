#pragma once
#include <string>
#include <algorithm>

inline std::string removeQuotes(std::string str) {
	std::string newString = str;
	newString.erase(std::remove(newString.begin(), newString.end(), '\"'), newString.end());
	return newString;
}

inline bool strVar(std::string str) {
	unsigned i;
	if (str[0] != '$') {
		return false;
	}
	for (i = 1; i < str.length(); i++) {
		if (!isupper(str[i])) {
			return false;
		}
	}
	return true;
}

inline bool numVar(std::string str) {
	unsigned i;
	if (str[0] != '%') {
		return false;
	}
	for (i = 1; i < str.length(); i++) {
		if (!isupper(str[i])) {
			return false;
		}
	}
	return true;
}


