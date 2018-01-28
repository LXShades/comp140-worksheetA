// main.cpp: Defines the entry point for the console application.
//
#include "stdafx.h"
#include <algorithm>
#include "WordList.h"
#include "main.h"

struct PlayedOption {
	std::string word;
	int similarity;
};

void AIChooseWord(std::string& wordOut, const std::set<std::string>& optionsIn, const std::vector<PlayedOption>& playedOptionsIn);

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

	// Create a set of words that the user or AI has already played
	std::vector<PlayedOption> playedOptions;

	// Fill the set with words (including the secret word)
	// Using a set for options guarantees that the elements are all different
	options = words.generateOptionList(secret, numberOfWords, wordLength);

	/*while (options.size() < numberOfWords)
	{
		std::string word = words.getRandomWord();
		options.insert(word);
	}*/

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
		// Get the user or AI's guess
		std::string userGuess;

		if (aiAutoPlay) {
			AIChooseWord(userGuess, options, playedOptions);
		} else {
			std::cin >> userGuess;
		}

		// Convert the guess to uppercase characters
		ConvertToUppercase(userGuess);

		// Determine how much the word matches
		int matchFactor = GetWordMatchFactor(userGuess, secret, wordLength);

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
	ConvertToUppercase(lastWords);

	if (lastWords == secret) {
		// Lawl
		std::cout << "Ironically enough, the player's last word was the correct word. What a short, sad life they hadth livedeth.\n";
		std::cout << "Alas, as they knew deep down inside, they're still going to die anyway.\n";
		system("pause");
	}

	// Say bye and close
	std::cout << "Bye bye\n";

	return 0;
}

// GetWordMatchFactor: Takes two strings, testing where their characters match (up to maxLength), and returning the number of matching characters
int GetWordMatchFactor(const std::string& guess, const std::string& secretWord, int maxLength) {
	int matchCount = 0;
	int largestExistingLength = std::min(std::min(guess.length(), secretWord.length()), static_cast<size_t>(maxLength));

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

// AIChooseWord: Try to choose the next word (to confirm the game is winnable) (I GAVE UP--but left this function in to show my thought process)
void AIChooseWord(std::string& wordOut, const std::set<std::string>& optionsIn, const std::vector<PlayedOption>& playedOptionsIn) {
	/*
	This AI will be quite crude--there's a lot of ways to connect the dots between the words and work out what's what, but it's hard to think about
	For all played options:
	   If its match factor is 1, the rest of the letters can be eliminated
	   The secret word is ABCDE
	   If there is another word whose match factor is also 1, and it shares only 1 letter between both (e.g. GGCGG and XXCXX), the middle letter is definitely C
	   If there is another word whose match factor is also 1, but it shares multiple letters (e.g. GGCGG and GXCXX), -any of the shared letters- could be true, the question is which one?
	   A cool thing: SMAFF (3 similarity) and FLIRT (2 similarity) paints the word clearly. WHY AND HOW?? Because there are no overlaps
	   We could say that because there  was  similarity,  the  letters  SMAFF were 'candidates'
	   We could also say that because there was similarity, the letters FLIRT were 'candidates'
	   We want to give the highest potential score to one of the words by the contrasting letters we got
	   SMAFF(3) and FLIRT(2)... the candidate could be anything. FMIRF would have as high a score as SMART.
	   How do we get the score? Well, we make sure we can take a letter from the above word without running out of matching letters, and letters from the lower word without running out of matching letters
	   We know that it can't be SMIRT, because that would require that FLIRT have 3 matches
	   
		playedLen = playedOptionsList.length()
		for guessWord in unplayedOptionsList:

			array testWordIndex[numCharactersInWords] # For each character in the test word, this array will hold an index of a previously guessed word to take the character from
			for each word in playedOptionsList:
				
		       
		       

	   GGCGG - 1
	   GXCXX - 1
	   
	   Test word: ABCDE
	              00100 potential score: 1

	   GGCGG - 1
	   ABXGE - 3

	   Test word: ABCDE
	              11101
	   GGXGE - 1
	   ABXGE - 3

	   Test word: ABCDE
	              11101

				  NEVERMIND --- I GIVE UP!
	*/

	/*int useWord[5]; // Denotes which word index to use for each character
	const int matchFactor = 1;

	for (int c = 0; c < 5; c++) {

	}*/
}