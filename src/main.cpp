#include "../include/board.h"
#include "../include/dawg.h"
#include "../include/trie.h"
#include <cassert>
#include <iostream>
#include <vector>

int main() {
        setlocale(LC_ALL, "en_US.UTF-8");

        std::vector<std::string> wordlist = {"BAKE", "BALE", "CAKE", "DALE"};
        Dawg d = Dawg(wordlist);
        // assert(d.contains("ABACUS"));
        // assert(d.contains("EMBEDDING"));
        // std::cout << (d.contains("GOONIES"));
        // assert(d.contains("XXXXXX"));
        // assert(d.contains("abacus"));
        // assert(d.contains(""));

        return 0;
}
