#pragma once
#include "grid.h"
// #include "user.h"
#include "tetrominoes.h"
#include <chrono>
#include "leaderboard.h"
#include <bits/stdc++.h>
using namespace std;

class Game
{
public:
    Game(int startSpeed, Leaderboard* lb, string name);
    ~Game();
    void Draw();
    void HandleInput();
    void MoveBlockDown();
    bool gameOver;
    int score;
    int level; // ✅ Track the game level
    int totalRowsCleared; // ✅ Track total cleared rows
        int getScore();

    chrono::milliseconds dropSpeed; // ✅ Fully qualify
    // User currentUser;


private:
    void HardDrop();
    void MoveBlockLeft();
    void MoveBlockRight();
    Block GetRandomBlock();
    std::vector<Block> GetAllBlocks();
    bool IsBlockOutside();
    void RotateBlock();
    void LockBlock();
    bool BlockFits();
    void Reset();
    void UpdateScore(int linesCleared);
    Grid grid;
    Leaderboard* leaderboard;
    std::vector<Block> blocks;
    Block currentBlock;
    Block nextBlock;
    string username;
 // ✅ Drop speed based on level
};
