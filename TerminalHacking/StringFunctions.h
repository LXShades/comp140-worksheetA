#pragma once
#include <string>

namespace StringFunctions {
	void ConvertToUppercase(std::string& word);

	int GetWordMatchFactor(const std::string& guess, const std::string& secretWord, int maxLength);
};