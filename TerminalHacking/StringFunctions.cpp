#include "StringFunctions.h"
#include <algorithm>

// ConvertToUppercase: Converts a string's lowercase characters to uppercase
void StringFunctions::ConvertToUppercase(std::string& word) {
	for (char& character : word) {
		if (character >= 'a' && character <= 'z')
			character += 'A' - 'a';
	}
}

// GetWordMatchFactor: Takes two strings, testing where their characters match (up to maxLength), and returning the number of matching characters
int StringFunctions::GetWordMatchFactor(const std::string& guess, const std::string& secretWord, int maxLength) {
	// Only scan thruogh enough characters in both strings (up to maxLength)
	int largestMutualLength = std::min(std::min(guess.length(), secretWord.length()), static_cast<size_t>(maxLength));

	// Check which characters match and add to the counter if they do
	int matchCount = 0;
	for (int i = 0; i < largestMutualLength; ++i) {
		if (guess[i] == secretWord[i])
			++matchCount;
	}

	// Return number of matching characters
	return matchCount;
}