#ifndef LEADERBOARD_H
#define LEADERBOARD_H

#include "headerfiles.h"
#include "user.h"

class Leaderboard {
private:
    vector<User> users;
    vector<vector<string>> topScores;  // [username, score]

public:
    void displayUserScores(const string& username);
    void loadFromFile(const string& filename);
    void saveToFile(const string& filename);
    void saveLeaderboardToFile(const string& filename);
    void addScore(const string& username, int score);
    void updateLeaderboard(const string& username, int score);
    void displayLeaderboard();
    bool usersEmpty() const;
    User* findUser(const string& username);
    int getHighestGlobalScore() const;
    void displayAllUsers();
    void createUser(const string& username);
    void displayLastFiveScoresAllUsers();
};

#endif // LEADERBOARD_H
