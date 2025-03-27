# 🎮 C++ Terminal Tetris Game

This is a console-based implementation of the classic **Tetris** game, developed in C++ using a terminal UI library (`ncurses` for Linux/macOS, `PDCurses` for Windows). It includes features such as user profiles, difficulty levels, scoring, and a persistent leaderboard system.

---

## 📂 Project Structure

```
Tetris/
├── include/               # Header files
├── src/                   # Source code (.cpp files)
├── leaderboard.csv        # Top scores (global)
├── users.csv              # All user score history
├── PDCurses/              # (Optional) Windows-specific curses library
└── README.md
```

---

## 📦 Dependencies

### 🐧 Linux (Ubuntu/Debian)
```bash
sudo apt install libncurses-dev
```

### 🍕 macOS (via Homebrew)
```bash
brew install ncurses
```

### 🪟 Windows (PDCurses)
1. Clone [PDCurses](https://github.com/wmcbrine/PDCurses)
2. Open MSYS2 or Git Bash and build:
```bash
cd PDCurses/wincon
make            # for MSYS2
mingw32-make    # for Git Bash
```

---

## 🚀 How to Compile and Run

### 🪟 Windows
```bash
g++ src/*.cpp -o tetris.exe -Iinclude -IPDCurses -LPDCurses/wincon -l:pdcurses.a
```

### 🐧 Linux/macOS
```bash
g++ -std=c++17 src/*.cpp -Iinclude -lncurses -o tetris
./tetris
```

---

## 🎮 Controls

| Key         | Action        |
|-------------|---------------|
| `←` or `a`  | Move Left     |
| `→` or `d`  | Move Right    |
| `↓` or `s`  | Move Down     |
| `↑` or `w`  | Rotate        |
| `Spacebar`  | Hard Drop     |
| `Esc`       | Exit Game     |

---

## ✨ Features

- Multiple users and profiles
- Cross-platform support
- Personal best and last 5 scores tracked
- Global leaderboard (top 5)
- Easy, Medium, Hard difficulty levels
- Terminal UI with color blocks
- Persistent storage in `.csv` files

---

## 📊 Data Structures Used

| Component     | Structure                            | Purpose                                                       |
|---------------|----------------------------------------|---------------------------------------------------------------|
| `Block`       | `vector<vector<Position>>`            | Stores all 4 rotation states for each tetromino               |
| `Grid`        | `int[20][10]`                         | 2D array representing the Tetris game grid                    |
| `Leaderboard` | `vector<User>`                        | Stores user profiles                                          |
|               | `vector<vector<string>>`              | Stores top 5 global scores with usernames                     |
| `User`        | `vector<int>`                         | Tracks last 5 scores of a user                                |
| `Colours`     | `vector<Colours>`                     | Holds RGB definitions and terminal color IDs for block colors |


### 📘 Classes and Their Responsibilities

| Class / Struct | Description |
|----------------|-------------|
| `Block`        | Represents a Tetromino shape. Handles movement, rotation, and rendering of blocks. |
| `Game`         | Core game engine. Handles input, block logic, scoring, and game state. |
| `Grid`         | Manages the 20x10 playfield, including collision detection and row clearing. |
| `Leaderboard`  | Manages all users and scores. Supports loading/saving data and top score tracking. |
| `User`         | Represents an individual user with their scores and personal best. |
| `Position`     | A simple structure to store a cell’s coordinates. |
| `Colours`      | Defines color components (RGB + ncurses ID) for the blocks. |

---

### 🔍 Class Details

#### `Block`
- **id** – Block type ID (used for color).
- **cells** – All possible rotations of the block as 2D vectors of `Position`.
- **rotationState** – Current rotation index.
- **rowOffset, columnOffset** – Current block position on grid.
- **Move(), Rotate(), UndoRotation()** – Change position or orientation.
- **Draw(), GetCellPositions()** – Render or return adjusted positions of block.

#### `Game`
- **grid** – Instance of `Grid` to manage block placement.
- **leaderboard** – Pointer to `Leaderboard` for storing scores.
- **score, level, dropSpeed** – Game metrics and difficulty scaling.
- **HandleInput(), MoveBlockDown(), LockBlock(), Draw()** – Main game logic and flow.

#### `Grid`
- **grid[20][10]** – Matrix representing the playfield.
- **ClearFullRows(), IsCellEmpty(), MoveRowDown()** – Core mechanics for line clearing and collision.

#### `Leaderboard`
- **users** – List of all players.
- **topScores** – Top 5 global scores as vector of [username, score].
- **addScore(), updateLeaderboard(), saveToFile()** – Score management functions.

#### `User`
- **username** – Player name.
- **scores** – Last 5 scores.
- **highestScoreEver** – Personal best score.
- **addScore(), displayScores()** – Score tracking and display methods.

#### `Position`
- **row, column** – Basic cell position.

#### `Colours`
- **r, g, b** – RGB values.
- **colourID** – Used by `ncurses` or `curses` to assign color pairs.

---

## 🧮 Scoring System

The scoring system rewards players based on the number of rows cleared:

| Lines Cleared at Once | Points Awarded |
|------------------------|----------------|
| 1 row                  | 10 points      |
| 2 rows                 | 40 points      |
| 3 rows                 | 90 points      |
| 4+ rows                | 30 × number of rows |

**Bonus:**
- Every 3 rows cleared = +1 level (faster speed)
- On game over:
  - 🎯 If new personal best → `"New Personal High Score!"`
  - 🏆 If highest ever → `"New Leaderboard Topper!"`

---

## ⏱️ Complexity Overview

| Operation                      | Time Complexity | Space Complexity |
|--------------------------------|------------------|-------------------|
| Block Movement/Rotation        | O(1)             | O(1)              |
| Grid Drawing and Updates       | O(n × m)         | O(1)              |
| Row Clearing (Grid)            | O(n)             | O(1)              |
| Leaderboard Insertion & Sort   | O(n log n)       | O(n)              |
| User Score Insertion           | O(1)             | O(1)              |
| Loading from CSV               | O(u × s)         | O(u + s)          |
| Saving to CSV                  | O(u × s)         | O(u + s)          |

Where:
- `n` = number of rows (20)
- `m` = number of columns (10)
- `u` = number of users
- `s` = number of scores per user

---


## 👨‍💻 Authors

Developed by:

- **Aaditya Kaushik - 202401001**  
- **Akshay Das - 202401011**  
- **Darsh Valand - 202401045**  
- **Harshit Goyal - 202401065**

---

## 📄 License

This project is licensed under the [MIT License](LICENSE).


---


