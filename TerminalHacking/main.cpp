// main.cpp: Defines the entry point for the console application.
//
#include "stdafx.h"

#include "StringFunctions.h"
#include "WordList.h"
#include "main.h"

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

	// Fill the set with words (including the secret word)
	options = words.generateOptionList(secret, numberOfWords, wordLength);

	// Display all words
	for each (std::string word in options)
	{
		std::cout << word << std::endl;
	}

	// TODO: implement the rest of the game
	// Make word list and display
	std::cout << "See before you a plentiful list of words. You must choose the correct word before you die.\n";
	std::cout << "You have only four chances...so choose wisely.\n";
	std::cout << "Tell us your first guess.\n";

	int numLives = 4;
	const bool aiAutoPlay = false; // For debugging

	while (numLives > 0) {
		// Get the user's guess
		std::string userGuess;

		std::cin >> userGuess;

		// Convert the guess to uppercase characters
		StringFunctions::ConvertToUppercase(userGuess);

		// Determine how much the word matches
		int matchFactor = StringFunctions::GetWordMatchFactor(userGuess, secret, wordLength);

		if (options.find(userGuess) == options.end()) {
			// Word wasn't in the word list
			std::cout << "You fool... that word is not an option!\n";
		} else if (matchFactor == wordLength) {
			// Word matched the secret word!
			std::cout << "Congratulations, you win!!!\n";
			std::cout << "Your death has been postponed to the time of your actual death.\n";

			// Allow the user to see their death postponement message before the window closes
			system("pause");
			return 0;
		} else {
			// Word didn't match the secret word
			std::cout << "Not quite...that word only has " << matchFactor << " matching characters...\n";
			--numLives;

			if (numLives > 0)
				std::cout << "You now have lost a life and have only " << numLives << " remaining. Please choose more wisely or die.\n";
		}
	}

	std::cout << "Congratulations, you die!!!\n";

	// Give the user a chance to say their last words
	std::cout << "Any last words?\n";

	// Let the user say some final words
	std::string lastWords;
	std::cin >> lastWords;
	StringFunctions::ConvertToUppercase(lastWords);

	if (lastWords == secret) {
		// Lawl
		std::cout << "Ironically enough, the player's last word was the correct word. What a tragic irony.\n";
		std::cout << "Alas, like they knew deep down inside, they were still going to die anyway.\n";
		system("pause");
	}

	// Say bye and close
	std::cout << "Bye bye\n";

	return 0;
}