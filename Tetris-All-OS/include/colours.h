#pragma once
#include "headerfiles.h"

struct Colours {
    int r, g, b;
    int colourID; // ID for ncurses/curses color pair
};

// Declare colors with ID mapping for ncurses
extern const Colours darkGrey;
extern const Colours green;
extern const Colours red;
extern const Colours orange;
extern const Colours yellow;
extern const Colours purple;
extern const Colours cyan;
extern const Colours blue;
extern const Colours lightBlue;
extern const Colours darkBlue;

// Function to get all colors
std::vector<Colours> GetCellColours();
