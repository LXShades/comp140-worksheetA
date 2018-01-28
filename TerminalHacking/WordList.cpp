#include "stdafx.h"
#include "WordList.h"
#include "main.h"

const std::string wordFileName("words.txt");

WordList::WordList(int wordLength)
{
	std::ifstream wordFile(wordFileName);
	std::string word;

	// Read past the copyright notice at the top of words.txt
	while (std::getline(wordFile, word) && word != "---")
	{
		// do nothing
	}

	// Read each line in the file
	while (std::getline(wordFile, word))
	{
		if (word.length() == wordLength)
		{
			// Scan through the line, converting each character to upper case.
			// If a non-alphabet character is encountered, reject the word.
			bool isValid = true;
			for (int i = 0; i < word.length(); i++)
			{
				if (isalpha(word[i]))
				{
					word[i] = toupper(word[i]);
				}
				else
				{
					isValid = false;
					break;
				}
			}

			// If it's a good word, add it to the list.
			if (isValid)
			{
				words.push_back(word);
			}
		}
	}
}

std::string WordList::getRandomWord()
{
	int index = rand() % words.size();
	return words[index];
}

std::set<std::string> WordList::generateOptionList(const std::string& secretWord, int wordCount, int wordLength) {
	// I tried to solve this game and failed--it might not be strictly possible to make a game that's guaranteed winnable when there's 15 word options
	// For now, do the next nicest thing and return an ordered list of words, from most similar to least similar to the secret word
	std::set<std::string> options;

	// Put the secret word in the set
	options.insert(secretWord);

	// Find words
	while (options.size() < wordCount) {
		// Find the next highest matching word by scanning the list from a random point

		int searchStartIndex = rand() * words.size() / RAND_MAX; // I like smooth random range scaling--pointless, but satisfying, and equally/more fast
		int maxSimilarity = -1;									 // Biggest match factor found in the list so far
		int mostSimilarIndex = 0;								 // Index of the word with that match factor

		for (int index = (searchStartIndex + 1) % words.size(); index != searchStartIndex; index++) {
			// Wrap around if the end of the list was reached
			if (index == words.size())
				index = 0;

			// Check if the similarity exceeds our current most similar word
			int similarity = GetWordMatchFactor(words[index], secretWord, wordLength);

			if (similarity > maxSimilarity) {
				if (similarity == wordLength)
					continue; // This is the secret word!! We can't add that!
				if (options.find(words[index]) != options.end())
					continue; // This is already in the option list!

				// Update the best index and similarity record
				maxSimilarity = similarity;
				mostSimilarIndex = index;
			}
		}

		// Add whatever we found
		options.insert(words[mostSimilarIndex]);
	}

	return options;
}