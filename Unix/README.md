# C++ Terminal Tetris Game 🎮

This is a console-based implementation of the classic **Tetris** game, developed in C++ using the `ncurses` library. It includes features such as user profiles, scoring, and a leaderboard system.

## Project Structure

```
Cpp-Tetris-Game
│
├── include
│   ├── block.h
│   ├── colours.h
│   ├── game.h
│   ├── grid.h
│   ├── leaderboard.h
│   ├── position.h
│   └── user.h
│
├── src
│   ├── block.cpp
│   ├── blocks.cpp
│   ├── colours.cpp
│   ├── game.cpp
│   ├── grid.cpp
│   ├── leaderboard.cpp
│   ├── main.cpp
│   ├── position.cpp
│   └── user.cpp
│
├── leaderboard.csv
├── users.csv
└── README.md
```

## Dependencies

- **ncurses library** (for terminal graphics)

On Ubuntu/Debian-based systems:
```bash
sudo apt-get install libncurses5-dev libncursesw5-dev
```

On macOS (using Homebrew):
```bash
brew install ncurses
```

## How to Compile and Run 🚀

Navigate to the project directory (`Unix`) and run:

```bash
g++ -std=c++17 src/*.cpp -I include -lncurses -o tetris
./tetris
```

- `src/*.cpp`: Compiles all `.cpp` files within the `src` directory.
- `-I include`: Specifies the directory containing header files.
- `-lncurses`: Links the `ncurses` library.
- `-o tetris`: Generates an executable named `tetris`.

## Controls 🎮

| Key              | Action                  |
|------------------|-------------------------|
| `←` or `a`       | Move Left               |
| `→` or `d`       | Move Right              |
| `↓` or `s`       | Move Down               |
| `↑` or `w`       | Rotate                  |
| `Spacebar`       | Hard Drop               |
| `Esc`            | Exit Game               |

## Features ✨
- Multiple users and profiles
- Maintains personal highest scores
- Global leaderboard for top scores
- Difficulty levels (Easy, Medium, Hard)

## Author 🖥️
Developed by:
- **Aaditya Kaushik - 202401001**  
- **Akshay Das - 202401011**  
- **Darsh Valand - 202401045**  
- **Harshit Goyal - 202401065**

## License 📄
This project is licensed under the MIT License.

