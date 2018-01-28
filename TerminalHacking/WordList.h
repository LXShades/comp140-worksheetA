#pragma once

class WordList
{
public:
	WordList(int wordLength);

	std::string getRandomWord();
	std::set<std::string> WordList::generateOptionList(const std::string& secretWord, int wordCount, int wordLength);

private:
	std::vector<std::string> words;
};