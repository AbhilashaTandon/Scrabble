#include "../include/trie.h"
#include <cassert>
#include <cctype>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>

Trie::Trie(std::string file_path) {
        std::fstream file = std::fstream(file_path.c_str(), std::ios_base::in);
        std::string line;
        root = {0, 0, 0, NONE};
        std::vector<std::string> words = std::vector<std::string>();
        while (std::getline(file, line)) {
                std::istringstream stream(line);
                std::string tree_path;
                if (!(stream >> tree_path)) {
                        std::cerr << line << '\n';
                        continue;
                }

                std::string next_word;
                while ((stream >> next_word)) {
                        words.push_back(next_word);
                }

                struct Node current = root;
                for (char c : tree_path) {
                        if (isupper(c)) {
                                // has letter
                                // assert(current.letter == 0);
                                current.letter = Tile(c - 64);
                                // assert(current.left == NULL);
                                if (current.left == NULL) {
                                        struct Node child = {0, NULL, NULL,
                                                             NONE};
                                        current.left = &child;
                                }
                                current = *current.left;
                        } else {
                                // assert(islower(c));
                                // lacks letter
                                // assert(current.letter == 0);
                                current.letter = Tile(c - 96);
                                // assert(current.right == NULL);
                                if (current.right == NULL) {
                                        struct Node child = {0, NULL, NULL,
                                                             NONE};
                                        current.right = &child;
                                }
                                current = *current.right;
                        }
                }

                // wordlist.push_back(words);

                // current.wordlist_idx = wordlist.size() - 1;
        }

        std::cout << "All words loaded" << "\n";
        std::queue<struct Node> ancestors = std::queue<struct Node>();
        ancestors.push(root);

        while (!ancestors.empty()) {
                struct Node current = ancestors.front();
                ancestors.pop();
                for (size_t i = 0; i < ancestors.size(); i++) {
                        std::cout << " ";
                }
                std::cout << char(current.letter + 64) << '\n';
                if (current.left != NULL)
                        ancestors.push(*current.left);
                if (current.right != NULL)
                        ancestors.push(*current.right);
        }
}

std::vector<std::string> Trie::get_words(std::vector<Tile> available) {
        struct Node current = root;
        while (true) {
                if (current.letter == NONE) {
                        continue;
                }
                bool present = false;
                for (Tile t : available) {
                        if (t == current.letter) {
                                present = true;
                                break;
                        }
                }
                if (present) {
                        if (current.left == NULL) {
                                return wordlist[current.wordlist_idx];
                        }
                        std::cout << char(current.letter + 64);
                        current = *current.left;
                        continue;
                }

                else {
                        if (current.right == NULL) {
                                return wordlist[current.wordlist_idx];
                        }
                        std::cout << char(current.letter + 96);
                        current = *current.right;
                        continue;
                }
        }
}
