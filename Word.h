#ifndef WORD_H
#define WORD_H
#include <string>
#include <set>
#include "CategoryEnum.h"
class Word {
    private:
        std::string word;
        CategoryEnum category;
        int incorrectGuesses;
        bool guessed;
        std::set<char> guessedLetters;
    
    public:
        Word(std::string word, CategoryEnum category);
    
        std::string getWord();
        CategoryEnum getCategory();
        bool guessLetter(char letter);
        bool isGuessed();
        int getIncorrectGuesses();
        void setGuessed(bool guessed);
        bool isLetterGuessed(char letter);  // <<< burası eklenmeli
        double getCompletionPercentage();
    };
    #endif
    