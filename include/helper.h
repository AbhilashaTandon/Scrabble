#ifndef HELPER_H
#define HELPER_H
// Contains small helper functions and lookup tables used throughout the
// codebase
#include <cstdint>
#include <string>
#include <utility>
#include <vector>

typedef uint16_t score_t;
typedef uint8_t tilecount_t;
typedef uint8_t position_t;
typedef std::pair<uint8_t, uint8_t> coords_t;

constexpr score_t tile_scores[30] = {0, 1, 3, 3, 2, 1, 4,  2,  4, 1,
                                     8, 5, 1, 3, 1, 1, 3,  10, 1, 1,
                                     1, 1, 4, 4, 8, 4, 10, 0, 0, 0};
constexpr tilecount_t tile_freq[30] = {
    0, 9, 2, 2, 4, 12, 2, 3, 2, 9, 1, 1, 4, 2,
    6, 8, 2, 1, 6, 4,  6, 4, 2, 2, 1, 2, 1, 2, 0, 0}; // last one is blank
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
};
enum Square { EMPTY, DOUBLE_LETTER, TRIPLE_LETTER, DOUBLE_WORD, TRIPLE_WORD };

bool is_letter_bonus(Square sq);

typedef std::pair<Tile, position_t> tile_place_t;

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

score_t get_score(std::string word);

coords_t get_xy(position_t pos);

position_t get_pos(int x, int y);

uint32_t get_bitmask(std::vector<Tile> tiles);

const position_t PASS = 225;


#endif
