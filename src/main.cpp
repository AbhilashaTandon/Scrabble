#include "../include/board.h"
#include "../include/trie.h"
#include <iostream>
#include "../include/dawg.h"
#include <cassert>

int main() {
        setlocale(LC_ALL, "en_US.UTF-8");
        
        Dawg d = Dawg("../wordlists/testing.txt");
        // assert(d.contains("ABACUS"));
        // assert(d.contains("EMBEDDING"));
        // std::cout << (d.contains("GOONIES"));
        // assert(d.contains("XXXXXX"));
        // assert(d.contains("abacus"));
        // assert(d.contains(""));

        return 0;
}
