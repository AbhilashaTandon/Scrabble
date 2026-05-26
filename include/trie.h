
#ifndef TRIE_H
#define TRIE_H
#include "helper.h"
#include <array>
#include <cstdint>
#include <span>
#include <string>
#include <vector>

struct TrieNode {
        int wordlist_idx;
        int num_words;
        struct TrieNode *left;
        // left will always contain words that have letter
        struct TrieNode *right;
        // right will always contain words that lack letter
        Tile letter;
};

class Trie {
      public:
        Trie(std::string file_path);
        std::span<std::string> get_words(std::vector<Tile> available);

        bool contains(std::string);
        uint32_t size();

      private:
        struct TrieNode root;
        std::vector<std::string>
            wordlist; // holds all words so nodes can index them
        std::vector<std::string> parse_trie_file(std::string file_path);
};

void print(struct TrieNode *);

#endif
