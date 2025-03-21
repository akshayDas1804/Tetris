#pragma once
#include <vector>
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

    // Vector-based replacement for map<int, vector<Position>>
    std::vector<std::vector<Position>> cells;

private:
    int cellSize;
    int rotationState;
    std::vector<Colours> colours;
    int rowOffset;
    int columnOffset;
};
