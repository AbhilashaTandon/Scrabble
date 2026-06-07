#ifndef WORD_H
#define WORD_H

#include "helper.h"
#include "dawg.h"
#include <array>
#include <cstdint>
#include <unordered_set>
#include <vector>

struct Word {
        std::string word;
        position_t start;
        bool is_vertical;

        Word(std::string w, position_t s, bool v)
            : word(w), start(s), is_vertical(v) {}
        bool operator<(const Word &other_word) const {
                return (word < other_word.word);
        }
        bool operator==(const Word &other_word) const {
                return (word == other_word.word) &&
                       (start == other_word.start) &&
                       (is_vertical == other_word.is_vertical);
        }
};


#endif
