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
    void setTotalScore(int score);
};

#endif // SCORE_H
