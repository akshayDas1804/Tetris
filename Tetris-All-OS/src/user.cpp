#include "user.h"
#include "headerfiles.h"


User::User(const string& name) : username(name), highestScoreEver(0) {}

void User::addScore(int score) {
    scores.push_back(score);
    if (scores.size() > 5) {
        scores.erase(scores.begin());
    }
    highestScoreEver = max(highestScoreEver, score);
}


void User::displayScores() const {
    clear();
    int termHeight, termWidth;
    getmaxyx(stdscr, termHeight, termWidth);
    mvprintw(termHeight / 2 - 3, (termWidth / 2) - (username.length() / 2) - 8,
             "Last 5 Scores for %s:", username.c_str());

    for (size_t i = 0; i < scores.size(); ++i) {
        mvprintw(termHeight / 2 - 1 + i, (termWidth / 2) - 1, "%d", scores[i]);
    }
    refresh();
}

