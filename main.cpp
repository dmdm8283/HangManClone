#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <iomanip>

int main()
{
	std::string fileName = "data.csv";
	int charCount;
	std::vector<std::string> wordList;
	std::string selectedWord;
	std::fstream file;

	/*std::cout << "Enter wordlist name: ";
	std::cin >> fileName;
	std::cout << '\n';
	*/
	std::cout << "How many letters do you want? ";
	std::cin >> charCount;
	std::cout << std::endl;


	file.open(fileName);
	if (!file.is_open()) {
		std::cout << "ERROR FILE INVALID" << std::endl;
		return 1;
	}
	std::string word;
	while (file >> word) {
		if (word.length() == charCount) {
			wordList.push_back(word);
		}
	}
	if (wordList.empty()) {
		std::cout << "ERROR INVALID CHAR SIZE" << std::endl;
		return 1;
	}
	file.close();

	std::srand(std::time(0));
	int random = std::rand() % wordList.size();
	selectedWord = wordList.at(random);


	//std::cout << selectedWord << std::endl;

	std::vector<char> guessedWord(selectedWord.length(), '_');
	std::vector<char> usedChars;
	int remainingGuesses = 6;
	bool win = false;


	//gameloop
	while (!win && remainingGuesses > 0)
	{
		std::cout << "\nCurrent word: ";
		for (char c : guessedWord) {
			std::cout << std::setfill('_') << c << ' ';
		}

		std::cout << "\nRemaining guesses: " << remainingGuesses << std::endl;

		char letter;
		std::cout << "Enter a letter: ";
		std::cin >> letter;

		if (std::find(usedChars.begin(), usedChars.end(), letter) != usedChars.end()) {
			std::cout << "You've already guessed that letter. Try again." << std::endl;
			continue;
		}
		usedChars.push_back(letter);

		bool correctGuess = false;
		for (size_t i = 0; i < selectedWord.length(); ++i) {
			if (selectedWord[i] == letter) {
				guessedWord[i] = letter;
				correctGuess = true;
			}
		}

		if (!correctGuess) {
			remainingGuesses--;
			std::cout << "Incorrect guess!" << std::endl;
		}

		if (std::find(guessedWord.begin(), guessedWord.end(), '_') == guessedWord.end()) {
			win = true;
		}
	}


	//results
	if (win) {
		std::cout << "\n you win. You guessed the word: " << selectedWord << std::endl;
	}
	else {
		std::cout << "\n game over. The word was: " << selectedWord << std::endl;
	}



	return 0;
}