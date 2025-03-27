#pragma once
#include "headerfiles.h"
#include "colours.h"

class Grid
{
public:
    Grid();
    void Initialize();
    void Print();
    void Draw(int, int);
    bool IsCellOutside(int row, int column);
    bool IsCellEmpty(int row, int column);
    int ClearFullRows();
    int grid[20][10];
    int getRows();
    int getColoumns();

private:
    bool IsRowFull(int row);
    void ClearRow(int row);
    void MoveRowDown(int row, int numRows);
    int numRows;
    int numCols;
    int cellSize;
    vector<Colours> colors;
};