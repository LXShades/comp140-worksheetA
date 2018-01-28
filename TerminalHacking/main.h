#pragma once
#include <cstdlib>

const int wordLength = 5;
const int numberOfWords = 15;

int GetWordMatchFactor(const std::string& guess, const std::string& secretWord, int maxLength);
void ConvertToUppercase(std::string& word);