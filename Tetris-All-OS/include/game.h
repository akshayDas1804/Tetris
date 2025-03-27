#pragma once
#include "headerfiles.h"
#include "grid.h"
#include "tetrominoes.h"
#include "leaderboard.h"

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
    int level; // Track the game level
    int totalRowsCleared; // Track total cleared rows
    int getScore();
    int cumulativeLinesCleared;
    chrono::milliseconds dropSpeed; // Fully qualify

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
};
