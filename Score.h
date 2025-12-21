#ifndef SCORE_H
#define SCORE_H

class Score {
private:
    int totalScore;

public:
    Score();

    void correctGuess();
    void incorrectGuess();
    int getTotalScore() const;
    void resetScore();
};

#endif // SCORE_H