// main.cpp: Defines the entry point for the console application.
//
#include "stdafx.h"
#include <algorithm>
#include "WordList.h"

const int wordLength = 5;
const int numberOfWords = 15;

int GetWordMatchFactor(const std::string& guess, const std::string& secretWord, int maxLength);
void ConvertToUppercase(std::string& word);

int main()
{
	// Seed the random number generator with the current time,
	// to ensure different results each time the program is run
	srand(static_cast<unsigned int>(time(nullptr)));
	
	// Initialise word list
	WordList words(wordLength);

	// Choose secret word
	std::string secret = words.getRandomWord();

	// Create a set to hold the list of options
	std::set<std::string> options;

	// Put the secret word in the set
	options.insert(secret);

	// Fill the set with more words
	// Using a set for options guarantees that the elements are all different
	while (options.size() < numberOfWords)
	{
		std::string word = words.getRandomWord();
		options.insert(word);
	}

	// Display all words
	for each (std::string word in options)
	{
		std::cout << word << std::endl;
	}

	// TODO: implement the rest of the game
	// Make word list and display
	std::cout << "See before you a plentiful list of chosen words. You must choose the correct word before you die.\n";
	std::cout << "You have only four chances...so choose wisely.\n";
	std::cout << "Tell us your first guess.\n";

	int numLives = 4;
	while (numLives >= 0) {
		// Get the user's guess
		std::string userGuess;

		std::cin >> userGuess;

		// Convert the guess to uppercase characters
		ConvertToUppercase(userGuess);

		// Determine how much the word matches
		int matchFactor = GetWordMatchFactor(userGuess, secret, wordLength);

		if (options.find(userGuess) == options.end()) {
			std::cout << "You fool... that word is not an option!\n";
		} else if (matchFactor == wordLength) {
			std::cout << "Congratulations, you win!!!\n";
			std::cout << "Your death has been postponed to the time of your actual death.\n";

			// Allow the user to see their death postponement message before the window closes
			system("pause");
			return 0;
		} else {
			std::cout << "Not quite...that word only has " << matchFactor << " matching characters...\n";
			--numLives;

			if (numLives >= 0)
				std::cout << "You now have lost a life and have only " << numLives << " remaining. Please choose more wisely or die.\n";
		}
	}

	std::cout << "Congratulations, you die!!!\n";

	// Give the user a chance to say their last words
	std::cout << "Any last words?\n";

	std::string lastWords;
	std::cin >> lastWords;

	std::cout << "Bye bye\n";

	return 0;
}

// GetWordMatchFactor: Takes two strings, testing where their characters match (up to maxLength), and returning the number of matching characters
int GetWordMatchFactor(const std::string& guess, const std::string& secretWord, int maxLength) {
	int matchCount = 0;
	int largestExistingLength = std::min(guess.length(), secretWord.length(), maxLength);

	// Check which characters match and add to the counter if they do
	for (int i = 0; i < largestExistingLength; ++i) {
		if (guess[i] == secretWord[i])
			++matchCount;
	}

	// Return number of matching characters
	return matchCount;
}

// ConvertToUppercase: Converts a string's lowercase characters to uppercase
void ConvertToUppercase(std::string& word) {
	for (char& character : word) {
		if (character >= 'a' && character <= 'z')
			character += 'A' - 'a';
	}
}