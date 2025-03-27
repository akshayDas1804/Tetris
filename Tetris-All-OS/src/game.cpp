#include "game.h"
#include "headerfiles.h"


Game::Game(int startSpeed, Leaderboard *lb, string name)
{
    leaderboard = lb;
    grid = Grid();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    gameOver = false;
    score = 0;
    level = 1;                                    // Start at level 1
    totalRowsCleared = 0;                         // Initialize cleared rows counter
    dropSpeed = chrono::milliseconds(startSpeed); // Initial drop speed
    username = name;
}

Game::~Game()
{
    endwin(); // Restore terminal settings
}

Block Game::GetRandomBlock()
{
    if (blocks.empty())
    {
        blocks = GetAllBlocks();
    }
    int randomIndex = rand() % blocks.size();
    Block block = blocks[randomIndex];
    blocks.erase(blocks.begin() + randomIndex);
    return block;
}

vector<Block> Game::GetAllBlocks()
{
    vector<Block> blocks = {IBlock(), JBlock(), LBlock(), OBlock(), SBlock(), TBlock(), ZBlock()};

    random_device rd;
    mt19937 g(rd());                          // better random number generator
    shuffle(blocks.begin(), blocks.end(), g); // Correct shuffle usage

    return blocks;
}

void Game::Draw()
{
    clear();

    int termHeight, termWidth;
    getmaxyx(stdscr, termHeight, termWidth);

    if (termHeight < 24 || termWidth < 50)
    {
        move(0, 0);
        printw("Terminal too small! Resize and restart.");
        refresh();
        return;
    }

    int gridStartY = (termHeight / 2) - 10;
    int gridStartX = (termWidth / 2) - 15;

    grid.Draw(gridStartY, gridStartX);
    currentBlock.Draw(gridStartY, gridStartX);

    // ✅ Show Level Above Next Block
    move(gridStartY - 2, gridStartX + 30);
    printw("Level: %d", level);

    move(gridStartY, gridStartX + 30);
    printw("Score: %d", score);

    move(gridStartY + 2, gridStartX + 30);
    printw("Next:");

    vector<Position> nextTiles = nextBlock.GetCellPositions();
    for (Position item : nextTiles)
    {
        move(gridStartY + item.row + 4, gridStartX + (item.column * 2) + 32);
        attron(COLOR_PAIR(nextBlock.id));
        printw(" #");
        attroff(COLOR_PAIR(nextBlock.id));
    }

    refresh();
}

void Game::HardDrop()
{
    while (!IsBlockOutside() && BlockFits())
    {
        currentBlock.Move(1, 0);
    }
    currentBlock.Move(-1, 0); // Undo last move to keep it inside bounds
    LockBlock();              // Lock the block in place
}

void Game::HandleInput()
{
    int key = getch();
    if (key != ERR) // If a key was pressed
    {
        if (gameOver && key != 0)
        {
            gameOver = false;
            Reset();
        }
        switch (key)
        {
        case KEY_LEFT:
        case 'a':
            MoveBlockLeft();
            break;
        case KEY_RIGHT:
        case 'd':
            MoveBlockRight();
            break;
        case KEY_DOWN:
        case 's':
            MoveBlockDown();
            // UpdateScore(0, 1);
            break;
        case KEY_UP:
        case 'w':
            RotateBlock();
            break;
        case ' ': // Spacebar for Hard Drop
            HardDrop();
            break;
        case 27: // Escape key to quit
            gameOver = true;
            leaderboard->addScore(username, score);                // Save current user's score!
            leaderboard->saveToFile("users.csv");                  // Persist immediately
            leaderboard->saveLeaderboardToFile("leaderboard.csv"); // Persist leaderboard
            endwin();                                              // Restore terminal settings
            exit(0);                                               // Quit safely
        }
    }
}

void Game::MoveBlockLeft()
{
    if (!gameOver)
    {
        currentBlock.Move(0, -1);
        if (IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(0, 1);
        }
    }
}

void Game::MoveBlockRight()
{
    if (!gameOver)
    {
        currentBlock.Move(0, 1);
        if (IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(0, -1);
        }
    }
}

void Game::MoveBlockDown()
{
    if (!gameOver)
    {
        currentBlock.Move(1, 0);
        if (IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.Move(-1, 0);
            LockBlock();
        }
    }
}

bool Game::IsBlockOutside()
{
    vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles)
    {
        if (grid.IsCellOutside(item.row, item.column))
        {
            return true;
        }
    }
    return false;
}

void Game::RotateBlock()
{
    if (!gameOver)
    {
        currentBlock.Rotate();
        if (IsBlockOutside() || BlockFits() == false)
        {
            currentBlock.UndoRotation();
        }
    }
}

void Game::LockBlock()
{
    vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles)
    {
        grid.grid[item.row][item.column] = currentBlock.id;
    }
    currentBlock = nextBlock;

    if (!BlockFits())
    {
        gameOver = true;

        int termHeight, termWidth;
        getmaxyx(stdscr, termHeight, termWidth);

        clear();

        // Retrieve user's personal best and global highest correctly:
        User* currentUser = leaderboard->findUser(username);
        int personalHighest = currentUser ? currentUser->highestScoreEver : 0;
        int globalHighest = leaderboard->getHighestGlobalScore();

        bool newPersonalBest = (score > personalHighest);
        bool newHighestScore = (score > globalHighest);

        // Display "GAME OVER!" centered
        mvprintw(termHeight / 2, termWidth / 2 - 5, "GAME OVER!");

        // Display "New Personal High Score!" if applicable
        if (newPersonalBest) {
            mvprintw(termHeight / 2 + 1, termWidth / 2 - 12, "New Personal High Score!");
        }

        // Display "Highest Score!" if applicable
        if (newHighestScore) {
            mvprintw(termHeight / 2 + 2, termWidth / 2 - 17, "Congratulations ! New Leaderboard Topper!");
        }

        refresh();
        // std::this_thread::sleep_for(std::chrono::seconds(3));
        this_thread::sleep_for(chrono::seconds(3));
        clear();

        // Only AFTER displaying, update leaderboard and user
        // leaderboard->addScore(username, score);

        return;
    }

    nextBlock = GetRandomBlock();
    int rowsCleared = grid.ClearFullRows();

    if (rowsCleared > 0)
    {
        totalRowsCleared += rowsCleared;
        UpdateScore(rowsCleared);

        if (totalRowsCleared % 3 == 0)
        {
            level++;
            dropSpeed -= chrono::milliseconds(50);
            if (dropSpeed < chrono::milliseconds(100))
            {
                dropSpeed = chrono::milliseconds(100);
            }
        }
    }
}


bool Game::BlockFits()
{
    vector<Position> tiles = currentBlock.GetCellPositions();
    for (Position item : tiles)
    {
        if (grid.IsCellEmpty(item.row, item.column) == false)
        {
            return false;
        }
    }
    return true;
}

int Game::getScore()
{
    return score;
}

void Game::Reset()
{
    grid.Initialize();
    blocks = GetAllBlocks();
    currentBlock = GetRandomBlock();
    nextBlock = GetRandomBlock();
    score = 0;
}

void Game::UpdateScore(int linesCleared)
{
    if (linesCleared)
    {
        int scoreToAdd = 0;

        int multipleOf3 = linesCleared / 3; // Number of full sets of 3 rows
        int remainder = linesCleared % 3;   // Remaining rows after groups of 3

        // ✅ Award 30 points per row for each full set of 3
        scoreToAdd += multipleOf3 * (3 * 30);

        // ✅ If remainder is 2, award 20 points per row for those 2 rows
        if (remainder == 2)
        {
            scoreToAdd += 2 * 20;
        }
        // ✅ If remainder is 1, award 10 points for that single row
        else if (remainder == 1)
        {
            scoreToAdd += 1 * 10;
        }

        score += scoreToAdd;
    }
}

