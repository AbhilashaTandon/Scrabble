#include "../include/helper.h"
#include <utility>

score_t get_score(std::string word) {
        score_t score = 0;
        for (auto tile : word) {
                score += tile_scores[tile - 64];
                // A -> 1, B -> 2, ...
                // We start at one because 0 represents no tile
        }
        return score;
}

std::pair<uint8_t, uint8_t> get_xy(position_t pos) {
        return std::make_pair(pos % 15, pos / 15);
}

position_t get_pos(int x, int y){
        return position_t(x + y * 15);
}
