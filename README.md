# C++ Terminal Tetris Game 🎮

This is a console-based implementation of the classic **Tetris** game, developed in C++ using a terminal UI library (`ncurses` for Linux/macOS, `PDCurses` for Windows). It includes features such as user profiles, difficulty levels, scoring, and a persistent leaderboard system.

---

## 📂 Project Structure

```
Tetris/
🔹️ include/               # Header files
🔹️ src/                   # Source code (.cpp files)
🔹️ leaderboard.csv        # Top scores (global)
🔹️ users.csv              # All user score history
🔹️ PDCurses/              # (Optional) Windows-specific curses library
🔹️ README.md
```

---

## 📦 Dependencies

### 🐧 **Linux (Ubuntu/Debian)**

```bash
sudo apt install libncurses-dev
```

### 🍕 **macOS (via Homebrew)**

```bash
brew install ncurses
```

### 🫠 **Windows (using PDCurses)**

1. Download or clone [PDCurses](https://github.com/wmcbrine/PDCurses) :
   
```bash
git clone https://github.com/wmcbrine/PDCurses
```
2. Open **MSYS2 MinGW 64-bit shell** (MinGW Terminal)
3. Build PDCurses:

```bash
cd /path/to/PDCurses/wincon
make
```

---

## 🚀 How to Compile and Run


### 🫠 Windows (PowerShell)

Poweshell (Recommended):

```bash
g++ (Get-ChildItem src\*.cpp) -o tetris.exe -Iinclude -IPDCurses -LPDCurses\wincon -l:pdcurses.a
```
In case that does not work, try :

```bash
g++ src/*.cpp -o tetris.exe -Iinclude -IPDCurses -LPDCurses/wincon -l:pdcurses.a
```

> ✅ Replace paths according to where you put PDCurses


### 🐧 Linux/macOS

```bash
g++ -std=c++17 src/*.cpp -Iinclude -lncurses -o tetris
./tetris
```

### 🫠 Windows (PowerShell)

```powershell
g++ (Get-ChildItem src\*.cpp) -o tetris.exe -Iinclude -IPDCurses -LPDCurses\wincon -l:pdcurses.a
.\tetris.exe
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
- Personal best and last 5 scores tracked
- Global leaderboard (top 5)
- Easy, Medium, Hard difficulty levels
- Terminal UI with color blocks
- Persistent storage in `.csv` files

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

