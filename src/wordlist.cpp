#include "../include/wordlist.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

WordList::WordList(std::string wordlist_file_path, std::string trie_file_path) : trie(trie_file_path) {
        std::fstream file = std::fstream(wordlist_file_path.c_str(), std::ios_base::in);
        std::string line;
        while (std::getline(file, line)) {
                std::istringstream stream(line);
                std::string word;
                if (!(stream >> word)) {
                        std::cerr << line << '\n';
                        continue;
                }
                this->wordlist.insert(word);
        }
}

uint32_t WordList::size() const { return wordlist.size(); }

bool WordList::contains(std::string word) const {
        return wordlist.contains(word);
}
