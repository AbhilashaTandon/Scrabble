#ifndef PRINT_H
#define PRINT_H
#include <array>
#include <string>
#include "board.h"
#define RED (tput setaf 1)
#define RESET (tput setaf 9)

const std::array<std::u32string,32> board_template = {
U"     A   B   C   D   E   F   G   H   I   J   K   L   M   N   O  ",
U"   ┌───────────────────────────────────────────────────────────┐", 
U"1  │                                                           │", 
U"   │                                                           │", 
U"2  │                                                           │", 
U"   │                                                           │", 
U"3  │                                                           │", 
U"   │                                                           │", 
U"4  │                                                           │", 
U"   │                                                           │", 
U"5  │                                                           │", 
U"   │                                                           │", 
U"6  │                                                           │", 
U"   │                                                           │", 
U"7  │                                                           │", 
U"   │                                                           │", 
U"8  │                             *                             │", 
U"   │                                                           │", 
U"9  │                                                           │", 
U"   │                                                           │", 
U"10 │                                                           │", 
U"   │                                                           │", 
U"11 │                                                           │", 
U"   │                                                           │", 
U"12 │                                                           │", 
U"   │                                                           │", 
U"13 │                                                           │", 
U"   │                                                           │", 
U"14 │                                                           │", 
U"   │                                                           │", 
U"15 │                                                           │", 
U"   └───────────────────────────────────────────────────────────┘"
};

const std::array<std::u32string, 56> rack_tiles = {
    U"   ", U" A₁", U" B₃", U" C₃", U" D₂", U" E₁", U" F₄", U" G₂", U" H₄", U" I₁",
    U" J₈", U" K₅", U" L₁", U" M₃", U" N₁", U" O₁", U" P₃", U"Q₁₀", U" R₁", U" S₁",
    U" T₁", U" U₁", U" V₄", U" W₄", U" X₈", U" Y₄", U"Z₁₀", U"BL₀", U"   ", U"   ", 

     U" A₀", U" B₀", U" C₀", U" D₀", U" E₀", U" F₀", U" G₀", U" H₀", U" I₀",
    U" J₀", U" K₀", U" L₀", U" M₀", U" N₀", U" O₀", U" P₀", U" Q₀", U" R₀", U" S₀",
    U" T₀", U" U₀", U" V₀", U" W₀", U" X₀", U" Y₀", U" Z₀"
};


#endif
