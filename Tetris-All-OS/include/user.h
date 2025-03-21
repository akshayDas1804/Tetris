#ifndef USER_H
#define USER_H

#include <vector>
#include <string>

class User {
public:
    std::string username;
    std::vector<int> scores;
    int highestScoreEver;

    User(const std::string& name);

    void addScore(int score);
    void displayScores() const;
};

#endif // USER_H
