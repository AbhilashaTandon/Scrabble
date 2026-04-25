#include "../include/board.h"
#include "../include/wordlist.h"
#include <iostream>

int main() {
        WordList list = WordList("wordlists/NWL2023-modified.txt");
        std::cout << list.size() << "\n";
        std::cout << list.contains("ABACUS") << "\n";
        Board b = Board();
        b.print();

        return 0;
}
