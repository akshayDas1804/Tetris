#ifndef USER_H
#define USER_H

#include "headerfiles.h"

class User {
public:
    string username;
    vector<int> scores;
    int highestScoreEver;

    User(const string& name);

    void addScore(int score);
    void displayScores() const;
};

#endif // USER_H
