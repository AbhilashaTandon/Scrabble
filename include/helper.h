#ifndef HELPER_H
#define HELPER_H

// Contains small helper functions and lookup tables used throughout the
// codebase
#include <array>
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

typedef int16_t score_t;
typedef uint8_t tilecount_t;
typedef uint8_t position_t;
typedef std::pair<uint8_t, uint8_t> coords_t;

constexpr score_t tile_scores[56] = {
    0, 1, 3, 3, 2, 1, 4, 2,  4, 1, 8, 5, 1, 3, 1, 1, 3, 10, 1,
    1, 1, 1, 4, 4, 8, 4, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,  0,
    0, 0, 0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
constexpr tilecount_t tile_freq[56] = {
    0, 9, 2, 2, 4, 12, 2, 3, 2, 9, 1, 1, 4, 2, 6, 8, 2, 1, 6,
    4, 6, 4, 2, 2, 1,  2, 1, 2, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0,
    0, 0, 0, 0, 0, 0,  0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
// there might be a mistake here but whatever ill deal w that later

enum Tile {
        NONE,
        A,
        B,
        C,
        D,
        E,
        F,
        G,
        H,
        I,
        J,
        K,
        L,
        M,
        N,
        O,
        P,
        Q,
        R,
        S,
        T,
        U,
        V,
        W,
        X,
        Y,
        Z,
        BLANK,
        START,
        END,
        BLANK_A,
        BLANK_B,
        BLANK_C,
        BLANK_D,
        BLANK_E,
        BLANK_F,
        BLANK_G,
        BLANK_H,
        BLANK_I,
        BLANK_J,
        BLANK_K,
        BLANK_L,
        BLANK_M,
        BLANK_N,
        BLANK_O,
        BLANK_P,
        BLANK_Q,
        BLANK_R,
        BLANK_S,
        BLANK_T,
        BLANK_U,
        BLANK_V,
        BLANK_W,
        BLANK_X,
        BLANK_Y,
        BLANK_Z,
};

Tile make_tile(char c);

enum Square { EMPTY, DOUBLE_LETTER, TRIPLE_LETTER, DOUBLE_WORD, TRIPLE_WORD };

bool is_letter_bonus(Square sq);

typedef std::pair<Tile, position_t> tile_place_t;
typedef std::array<tile_place_t, 7> move_t;

score_t get_score(std::string word);

constexpr Square board_layout[225] = {
    TRIPLE_WORD,   EMPTY,         EMPTY,         DOUBLE_LETTER, EMPTY,
    EMPTY,         EMPTY,         TRIPLE_WORD,   EMPTY,         EMPTY,
    EMPTY,         DOUBLE_LETTER, EMPTY,         EMPTY,         TRIPLE_WORD,

    EMPTY,         DOUBLE_WORD,   EMPTY,         EMPTY,         EMPTY,
    TRIPLE_LETTER, EMPTY,         EMPTY,         EMPTY,         TRIPLE_LETTER,
    EMPTY,         EMPTY,         EMPTY,         DOUBLE_WORD,   EMPTY,

    EMPTY,         EMPTY,         DOUBLE_WORD,   EMPTY,         EMPTY,
    EMPTY,         DOUBLE_LETTER, EMPTY,         DOUBLE_LETTER, EMPTY,
    EMPTY,         EMPTY,         DOUBLE_WORD,   EMPTY,         EMPTY,

    DOUBLE_LETTER, EMPTY,         EMPTY,         DOUBLE_WORD,   EMPTY,
    EMPTY,         EMPTY,         DOUBLE_LETTER, EMPTY,         EMPTY,
    EMPTY,         DOUBLE_WORD,   EMPTY,         EMPTY,         DOUBLE_LETTER,

    EMPTY,         EMPTY,         EMPTY,         EMPTY,         DOUBLE_WORD,
    EMPTY,         EMPTY,         EMPTY,         EMPTY,         EMPTY,
    DOUBLE_WORD,   EMPTY,         EMPTY,         EMPTY,         EMPTY,

    EMPTY,         TRIPLE_LETTER, EMPTY,         EMPTY,         EMPTY,
    TRIPLE_LETTER, EMPTY,         EMPTY,         EMPTY,         TRIPLE_LETTER,
    EMPTY,         EMPTY,         EMPTY,         TRIPLE_LETTER, EMPTY,

    EMPTY,         EMPTY,         DOUBLE_LETTER, EMPTY,         EMPTY,
    EMPTY,         DOUBLE_LETTER, EMPTY,         DOUBLE_LETTER, EMPTY,
    EMPTY,         EMPTY,         DOUBLE_LETTER, EMPTY,         EMPTY,

    TRIPLE_WORD,   EMPTY,         EMPTY,         DOUBLE_LETTER, EMPTY,
    EMPTY,         EMPTY,         DOUBLE_WORD,   EMPTY,         EMPTY,
    EMPTY,         DOUBLE_LETTER, EMPTY,         EMPTY,         TRIPLE_WORD,

    EMPTY,         EMPTY,         DOUBLE_LETTER, EMPTY,         EMPTY,
    EMPTY,         DOUBLE_LETTER, EMPTY,         DOUBLE_LETTER, EMPTY,
    EMPTY,         EMPTY,         DOUBLE_LETTER, EMPTY,         EMPTY,

    EMPTY,         TRIPLE_LETTER, EMPTY,         EMPTY,         EMPTY,
    TRIPLE_LETTER, EMPTY,         EMPTY,         EMPTY,         TRIPLE_LETTER,
    EMPTY,         EMPTY,         EMPTY,         TRIPLE_LETTER, EMPTY,

    EMPTY,         EMPTY,         EMPTY,         EMPTY,         DOUBLE_WORD,
    EMPTY,         EMPTY,         EMPTY,         EMPTY,         EMPTY,
    DOUBLE_WORD,   EMPTY,         EMPTY,         EMPTY,         EMPTY,

    DOUBLE_LETTER, EMPTY,         EMPTY,         DOUBLE_WORD,   EMPTY,
    EMPTY,         EMPTY,         DOUBLE_LETTER, EMPTY,         EMPTY,
    EMPTY,         DOUBLE_WORD,   EMPTY,         EMPTY,         DOUBLE_LETTER,

    EMPTY,         EMPTY,         DOUBLE_WORD,   EMPTY,         EMPTY,
    EMPTY,         DOUBLE_LETTER, EMPTY,         DOUBLE_LETTER, EMPTY,
    EMPTY,         EMPTY,         DOUBLE_WORD,   EMPTY,         EMPTY,

    EMPTY,         DOUBLE_WORD,   EMPTY,         EMPTY,         EMPTY,
    TRIPLE_LETTER, EMPTY,         EMPTY,         EMPTY,         TRIPLE_LETTER,
    EMPTY,         EMPTY,         EMPTY,         DOUBLE_WORD,   EMPTY,

    TRIPLE_WORD,   EMPTY,         EMPTY,         DOUBLE_LETTER, EMPTY,
    EMPTY,         EMPTY,         TRIPLE_WORD,   EMPTY,         EMPTY,
    EMPTY,         DOUBLE_LETTER, EMPTY,         EMPTY,         TRIPLE_WORD};

coords_t get_xy(position_t pos);

position_t get_pos(int x, int y);

uint32_t get_bitmask(std::vector<Tile> tiles);

const position_t PASS = 225;

constexpr std::array<std::pair<char, char>, 75> nonexistent_bigrams = {
    std::make_pair('B', 'Q'), std::make_pair('B', 'X'),
    std::make_pair('C', 'F'), std::make_pair('C', 'J'),
    std::make_pair('C', 'V'), std::make_pair('C', 'X'),
    std::make_pair('D', 'X'), std::make_pair('F', 'Q'),
    std::make_pair('F', 'V'), std::make_pair('F', 'X'),
    std::make_pair('F', 'Z'), std::make_pair('G', 'Q'),
    std::make_pair('G', 'X'), std::make_pair('H', 'X'),
    std::make_pair('J', 'B'), std::make_pair('J', 'C'),
    std::make_pair('J', 'F'), std::make_pair('J', 'G'),
    std::make_pair('J', 'H'), std::make_pair('J', 'M'),
    std::make_pair('J', 'P'), std::make_pair('J', 'Q'),
    std::make_pair('J', 'T'), std::make_pair('J', 'V'),
    std::make_pair('J', 'W'), std::make_pair('J', 'X'),
    std::make_pair('J', 'Y'), std::make_pair('J', 'Z'),
    std::make_pair('K', 'Q'), std::make_pair('K', 'X'),
    std::make_pair('K', 'Z'), std::make_pair('M', 'X'),
    std::make_pair('P', 'Q'), std::make_pair('P', 'X'),
    std::make_pair('Q', 'B'), std::make_pair('Q', 'C'),
    std::make_pair('Q', 'D'), std::make_pair('Q', 'F'),
    std::make_pair('Q', 'G'), std::make_pair('Q', 'H'),
    std::make_pair('Q', 'J'), std::make_pair('Q', 'K'),
    std::make_pair('Q', 'L'), std::make_pair('Q', 'M'),
    std::make_pair('Q', 'N'), std::make_pair('Q', 'P'),
    std::make_pair('Q', 'Q'), std::make_pair('Q', 'R'),
    std::make_pair('Q', 'T'), std::make_pair('Q', 'V'),
    std::make_pair('Q', 'X'), std::make_pair('Q', 'Y'),
    std::make_pair('Q', 'Z'), std::make_pair('R', 'X'),
    std::make_pair('S', 'X'), std::make_pair('T', 'X'),
    std::make_pair('V', 'B'), std::make_pair('V', 'F'),
    std::make_pair('V', 'H'), std::make_pair('V', 'J'),
    std::make_pair('V', 'P'), std::make_pair('V', 'Q'),
    std::make_pair('V', 'T'), std::make_pair('V', 'W'),
    std::make_pair('V', 'X'), std::make_pair('W', 'Q'),
    std::make_pair('W', 'V'), std::make_pair('W', 'X'),
    std::make_pair('X', 'J'), std::make_pair('X', 'K'),
    std::make_pair('X', 'R'), std::make_pair('X', 'Z'),
    std::make_pair('Y', 'Q'), std::make_pair('Z', 'R'),
    std::make_pair('Z', 'X'),

};

#endif
