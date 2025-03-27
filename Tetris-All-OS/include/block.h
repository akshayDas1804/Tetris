#pragma once
#include "headerfiles.h"
#include "position.h"
#include "colours.h"

class Block {
public:
    Block();
    void Draw(int, int);
    void Move(int rows, int columns);
    std::vector<Position> GetCellPositions();
    void Rotate();
    void UndoRotation();
    
    int id;
    vector<vector<Position>> cells;

private:
    int cellSize;
    int rotationState;
    std::vector<Colours> colours;
    int rowOffset;
    int columnOffset;
};
