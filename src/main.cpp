#include "../include/board.h"
#include "../include/trie.h"
#include <iostream>
#include "../include/dawg.h"

int main() {
        setlocale(LC_ALL, "en_US.UTF-8");
        
        Dawg d = Dawg("../wordlists/NWL2023-modified.txt");

        return 0;
}
