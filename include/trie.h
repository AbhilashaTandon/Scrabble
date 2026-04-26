
#ifndef TRIE_H
#define TRIE_H
#include "helper.h"
#include "wordlist.h"
#include <array>
#include <cstdint>
#include <vector>
#include <string>
#include <span>

struct Node{
        int wordlist_idx;
        int num_words;
        struct Node *left;
        // left will always contain words that have letter
        struct Node *right;
        // right will always contain words that lack letter
        Tile letter;
};

class Trie {
public:
        Trie(std::string file_path);
        std::span<std::string> get_words(std::vector<Tile> available);
private:
        struct Node root;
        std::vector<std::string> wordlist; //holds all words so nodes can index them
};
#endif
