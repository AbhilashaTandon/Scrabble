#ifndef PRINT_H
#define PRINT_H
#include <array>
#include <string>
#include "board.h"
#define RED (tput setaf 1)
#define RESET (tput setaf 9)

const std::array<std::u32string,31> board_template = {
U"┌───────────────────────────────────────────────────────────┐", 
U"│3 W         2 L             3 W             2 L         3 W│", 
U"│                                                           │", 
U"│    2 W             3 L             3 L             2 W    │", 
U"│                                                           │", 
U"│        2 W             2 L     2 L             2 W        │", 
U"│                                                           │", 
U"│2 L         2 W             2 L             2 W         2 L│", 
U"│                                                           │", 
U"│                2 W                     2 W                │", 
U"│                                                           │", 
U"│    3 L             3 L             3 L             3 L    │", 
U"│                                                           │", 
U"│        2 L             2 L     2 L             2 L        │", 
U"│                                                           │", 
U"│3 W         2 L              *              2 L         3 W│", 
U"│                                                           │", 
U"│        2 L             2 L     2 L             2 L        │", 
U"│                                                           │", 
U"│    3 L             3 L             3 L             3 L    │", 
U"│                                                           │", 
U"│                2 W                     2 W                │", 
U"│                                                           │", 
U"│2 L         2 W             2 L             2 W         2 L│", 
U"│                                                           │", 
U"│        2 W             2 L     2 L             2 W        │", 
U"│                                                           │", 
U"│    2 W             3 L             3 L             2 W    │", 
U"│                                                           │", 
U"│3 W         2 L             3 W             2 L         3 W│", 
U"└───────────────────────────────────────────────────────────┘"
};

const std::array<std::u32string, 30> rack_tiles = {
    U"   ", U" A₁", U" B₃", U" C₃", U" D₂", U" E₁", U" F₄", U" G₂", U" H₄", U" I₁",
    U" J₈", U" K₅", U" L₁", U" M₃", U" N₁", U" O₁", U" P₃", U"Q₁₀", U" R₁", U" S₁",
    U" T₁", U" U₁", U" V₄", U" W₄", U" X₈", U" Y₄", U"Z₁₀", U"BL₀", U"   ", U"   ",
};

const std::array<std::u32string, 30> board_tiles = { U" ", U"A", U"B", U"C", U"D", U"E", U"F", U"G", U"H", U"I", U"J", U"K", U"L", U"M", U"N", U"O", U"P", U"Q", U"R", U"S", U"T", U"U", U"V", U"W", U"X", U"Y", U"Z", U"_", U" ", U" "};

#endif
