#include "grid.h"
#include "headerfiles.h"

Grid::Grid() {
    numRows = 20;
    numCols = 10;
    Initialize();
}

void Grid::Initialize() {
    for (int row = 0; row < numRows; row++) {
        for (int column = 0; column < numCols; column++) {
            grid[row][column] = 0;
        }
    }
}

void Grid::Print() {
    for (int row = 0; row < numRows; row++) {
        for (int column = 0; column < numCols; column++) {
            cout << (grid[row][column] ? "#" : ".") << " ";
        }
        cout << endl;
    }
}

void Grid::Draw(int startY, int startX) {
    for (int row = 0; row < numRows; row++) {
        move(startY + row, startX);  // Offset grid to center
        for (int column = 0; column < numCols; column++) {
            if (grid[row][column] == 0) {
                // ✅ Set grid color to yellow
                attron(COLOR_PAIR(7));  
                printw(". ");
                attroff(COLOR_PAIR(7));
            } else {
                attron(COLOR_PAIR(grid[row][column]));  // Set block color
                printw("# ");
                attroff(COLOR_PAIR(grid[row][column]));
            }
        }
    }
}

bool Grid::IsCellOutside(int row, int column) {
    return !(row >= 0 && row < numRows && column >= 0 && column < numCols);
}

bool Grid::IsCellEmpty(int row, int column) {
    return grid[row][column] == 0;
}

int Grid::ClearFullRows() {
    int completed = 0;
    for (int row = numRows - 1; row >= 0; row--) {
        if (IsRowFull(row)) {
            ClearRow(row);
            completed++;
        } else if (completed > 0) {
            MoveRowDown(row, completed);
        }
    }
    return completed;
}

bool Grid::IsRowFull(int row) {
    for (int column = 0; column < numCols; column++) {
        if (grid[row][column] == 0) {
            return false;
        }
    }
    return true;
}

void Grid::ClearRow(int row) {
    for (int column = 0; column < numCols; column++) {
        grid[row][column] = 0;
    }
}

void Grid::MoveRowDown(int row, int numRows) {
    for (int column = 0; column < numCols; column++) {
        grid[row + numRows][column] = grid[row][column];
        grid[row][column] = 0;
    }
}


int Grid::getColoumns()
{
    return numCols;
}

int Grid::getRows()
{
    return numRows;
}