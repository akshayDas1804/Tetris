#include "block.h"
#include "colours.h"
#include "headerfiles.h"

Block::Block()
{
    cellSize = 30;
    rotationState = 0;
    rowOffset = 0;
    columnOffset = 0;
}

void Block::Draw(int startY, int startX) {
    vector<Position> tiles = GetCellPositions();
    
    for (Position item : tiles) {
        if (item.row >= 0 && item.row < 20 && item.column >= 0 && item.column < 10) {
            move(startY + item.row, startX + (item.column * 2));
            attron(COLOR_PAIR(id)); 
            addch('#');
            attroff(COLOR_PAIR(id));
        }
    }
}

void Block::Move(int rows, int columns)
{
    rowOffset += rows;
    columnOffset += columns;
}

vector<Position> Block::GetCellPositions()
{
    vector<Position> tiles = cells[rotationState];
    vector<Position> movedTiles;
    for (Position item : tiles) {
        movedTiles.push_back({item.row + rowOffset, item.column + columnOffset});
    }
    return movedTiles;
}

void Block::Rotate()
{
    rotationState = (rotationState + 1) % cells.size();
}

void Block::UndoRotation()
{
    rotationState = (rotationState - 1 + cells.size()) % cells.size();
}
