#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include <vector>
#include <string>
#include "user.h"

class Leaderboard {
private:
    std::vector<User> users;
    std::vector<std::vector<std::string>> topScores;  // [username, score]

public:
    void displayUserScores(const std::string& username);
    void loadFromFile(const std::string& filename);
    void saveToFile(const std::string& filename);
    void saveLeaderboardToFile(const std::string& filename);
    void addScore(const std::string& username, int score);
    void updateLeaderboard(const std::string& username, int score);
    void displayLeaderboard();
    bool usersEmpty() const;
    User* findUser(const std::string& username);
    int getHighestGlobalScore() const;
    void displayAllUsers();
    void createUser(const std::string& username);
    void displayLastFiveScoresAllUsers();
};

#endif // LEADERBOARD_H
