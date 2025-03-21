#include "colours.h"

// ✅ Define standard colors & assign ncurses IDs
const Colours pink       = {255, 105, 180, 11};  
const Colours green      = { 47, 230,  23, 2 };
const Colours red        = {232,  18,  18, 3 };
const Colours orange     = {226, 116,  17, 4 };  
const Colours yellow     = {237, 234,   4, 5 };
const Colours purple     = {166,   0, 247, 6 };
const Colours cyan       = { 21, 204, 209, 7 };
const Colours blue       = { 13,  64, 216, 8 };
const Colours lightBlue  = { 59,  85, 162, 9 };
const Colours darkBlue   = { 44,  44, 127, 10 };

std::vector<Colours> GetCellColours() {
    return {pink, green, red, orange, yellow, purple, cyan, blue, lightBlue, darkBlue};
}
