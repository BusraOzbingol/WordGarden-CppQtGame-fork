#include "Word.h"
#include <cctype>
#include <set>
#include <string>

#include "CategoryEnum.h"

using namespace std;

Word::Word(string word, CategoryEnum category)
    : word(word), category(category), incorrectGuesses(0), guessed(false) {}

string Word::getWord() {
    return word;
}

CategoryEnum Word::getCategory() {
    return category;
}

bool Word::guessLetter(char letter) {
    letter = tolower(letter);
    guessedLetters.insert(letter);

    bool correct = false;
    for (char c : word) {
        if (tolower(c) == letter) {
            correct = true;
            break;
        }
    }

    if (!correct) {
        incorrectGuesses++;
        return false;
    }

    bool allGuessed = true;
    for (char c : word) {
        if (guessedLetters.find(tolower(c)) == guessedLetters.end()) {
            allGuessed = false;
            break;
        }
    }

    guessed = allGuessed;
    return true;
}

bool Word::isGuessed() {
    return guessed;
}

int Word::getIncorrectGuesses() {
    return incorrectGuesses;
}

void Word::setGuessed(bool guessed) {
    this->guessed = guessed;
}

bool Word::isLetterGuessed(char letter) {
    return guessedLetters.count(tolower(letter)) > 0;
}

double Word::getCompletionPercentage() {
    if (word.empty()) return 0.0;

    int total = word.size();
    int correct = 0;

    for (char c : word) {
        if (guessedLetters.count(tolower(c)) > 0) {
            correct++;
        }
    }

    return (correct * 100.0) / total;
}
