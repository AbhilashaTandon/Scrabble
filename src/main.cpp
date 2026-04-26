#include "../include/board.h"
#include "../include/trie.h"
#include <iostream>

int main() {
        setlocale(LC_ALL, "en_US.UTF-8");

        Trie t = Trie("../wordlists/trie.txt");

        std::vector<Tile> rack = {A, B, S, C, O, N, D};

        for(auto word : t.get_words(rack)){
                std::cout << '\n' << word;
        }

        return 0;
}
