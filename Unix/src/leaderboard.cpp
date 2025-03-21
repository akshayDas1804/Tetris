#include "leaderboard.h"
#include <fstream>
#include <sstream>
#include <algorithm>
#include <ncurses.h>

void Leaderboard::displayUserScores(const std::string& username) {
    clear();
    bool userFound = false;

    for (size_t i = 0; i < users.size(); i++) {
        if (users[i].username == username) {
            users[i].displayScores();
            userFound = true;
            break;
        }
    }

    if (!userFound) {
        mvprintw(0, 0, "User not found.");
        refresh();
    }
}



void Leaderboard::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) return;

    users.clear();
    topScores.clear();

    std::string line;
    while (getline(file, line)) {
        std::stringstream ss(line);
        std::string item;
        std::vector<std::string> tokens;

        while (getline(ss, item, ',')) {
            tokens.push_back(item);
        }

        if (tokens.size() < 2) continue;

        User user(tokens[0]);
        user.highestScoreEver = std::stoi(tokens[1]);

        // Load all last 5 scores and update the leaderboard with EACH score
        for (size_t i = 2; i < tokens.size(); ++i) {
            int score = std::stoi(tokens[i]);
            user.scores.push_back(score);

            // Add each individual score into the global leaderboard
            updateLeaderboard(user.username, score);
        }

        users.push_back(user);
    }
    file.close();
}




void Leaderboard::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    for (auto& user : users) {
        file << user.username << "," << user.highestScoreEver;
        for (int score : user.scores) {
            file << "," << score;
        }
        file << "\n";
    }
    file.close();
}

void Leaderboard::saveLeaderboardToFile(const std::string& filename) {
    std::ofstream file(filename);
    for (auto& entry : topScores) {
        file << entry[0] << "," << entry[1] << "\n";
    }
    file.close();
}

void Leaderboard::addScore(const std::string& username, int score) {
    bool userFound = false;
    for (size_t i = 0; i < users.size(); i++) {
        if (users[i].username == username) {
            users[i].addScore(score);
            userFound = true;
            break;
        }
    }

    if (!userFound) {
        User newUser(username);
        newUser.addScore(score);
        users.push_back(newUser);
    }
    updateLeaderboard(username, score);
}


void Leaderboard::updateLeaderboard(const std::string& username, int score) {
    // Add the new score directly to the leaderboard
    topScores.push_back({username, std::to_string(score)});

    // Sort leaderboard strictly by descending scores (including 0)
    std::sort(topScores.begin(), topScores.end(),
        [](const std::vector<std::string>& a, const std::vector<std::string>& b) {
            return std::stoi(a[1]) > std::stoi(b[1]);
        });

    // Keep only the global top 5 scores regardless of duplicates or zeros
    if (topScores.size() > 5) {
        topScores.resize(5);
    }
}



void Leaderboard::displayLeaderboard() {
    clear();
    int termHeight, termWidth;
    getmaxyx(stdscr, termHeight, termWidth);

    int startRow = termHeight / 2 - (topScores.size() / 2);
    mvprintw(startRow - 2, (termWidth / 2) - 6, "Top Scores:");

    for (size_t i = 0; i < topScores.size(); ++i) {
        std::string line = topScores[i][0] + ": " + topScores[i][1];
        mvprintw(startRow + i, (termWidth / 2) - (line.length() / 2), "%s", line.c_str());
    }
    refresh();
}


User* Leaderboard::findUser(const std::string& username) {
    for (size_t i = 0; i < users.size(); ++i) {
        if (users[i].username == username) {
            return &users[i];
        }
    }
    return nullptr;
}


void Leaderboard::displayAllUsers() {
    clear();
    int termHeight, termWidth;
    getmaxyx(stdscr, termHeight, termWidth);

    mvprintw(termHeight / 2 - users.size() / 2 - 1, (termWidth / 2) - 7, "Existing Users:");

    for (size_t i = 0; i < users.size(); ++i) {
        mvprintw(termHeight / 2 - users.size() / 2 + i + 1,
                 (termWidth / 2) - (users[i].username.length() / 2),
                 "%s", users[i].username.c_str());
    }
    refresh();
}


void Leaderboard::createUser(const std::string& username) {
    if (findUser(username) == nullptr) {
        User newUser(username);
        users.push_back(newUser);
    }
}

bool Leaderboard::usersEmpty() const {
    return users.empty();
}




void Leaderboard::displayLastFiveScoresAllUsers() {
    clear();
    int termHeight, termWidth;
    getmaxyx(stdscr, termHeight, termWidth);

    int line = termHeight / 2 - (users.size() * 3);
    for (size_t i = 0; i < users.size(); ++i) {
        mvprintw(line++, (termWidth / 2) - (users[i].username.length() / 2) - 6,
                 "%s", users[i].username.c_str());
        int scoresShown = 0;
        std::string scoresLine;
        for (int score : users[i].scores) {
            scoresLine += std::to_string(score) + "  ";
            scoresShown++;
            if (scoresShown >= 5) break;
        }
        mvprintw(line++, (termWidth / 2) - (scoresLine.length() / 2), "%s", scoresLine.c_str());
        line++;
    }
    refresh();
}

int Leaderboard::getHighestGlobalScore() const{
    if (!topScores.empty()) {
        return std::stoi(topScores.front()[1]);
    }
    return 0;
}


