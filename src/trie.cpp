#include "../include/trie.h"
// #include <benchmark/benchmark.h>
#include <cassert>
#include <cctype>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>

void print(struct TrieNode *node) {
        if (node->letter != NONE) {
                std::cout << char(node->letter + 64) << " ";
        }
        if (node->left != NULL) {
                print(node->left);
        }
        if (node->right != NULL) {
                print(node->right);
        }
}

Trie::Trie(std::string file_path) {
        this->root = {0, 0, 0, 0, NONE};
        wordlist = parse_trie_file(file_path);

        std::cout << "All words loaded" << "\n";
        std::queue<struct TrieNode *> ancestors =
            std::queue<struct TrieNode *>();
        ancestors.push(&this->root);

        while (!ancestors.empty()) {
                struct TrieNode *current = ancestors.front();
                ancestors.pop();
                if (current->letter == NONE) {
                        assert(current->left == NULL);
                        assert(current->right == NULL);
                        continue;
                }
                // std::cout << ancestors.size() << " ";
                // std::cout << char(current->letter + 64) << '\n';
                if (current->left != NULL && current->left->letter != NONE)
                        ancestors.push(current->left);
                if (current->right != NULL && current->right->letter != NONE)
                        ancestors.push(current->right);
        }
}

std::vector<std::string> Trie::get_words(std::vector<Tile> available) const {
        struct TrieNode current = this->root;
        while (true) {
                if (current.letter == NONE) {
                        break;
                }
                bool present = false;
                for (std::vector<Tile>::iterator i = available.begin();
                     i < available.end(); i++) {
                        if (*i == current.letter) {
                                present = true;
                                available.erase(i);
                                break;
                        }
                }
                if (present) {
                        if (current.left == NULL) {
                                break;
                        }
                        current = *current.left;
                        continue;
                }

                else {
                        if (current.right == NULL) {
                                break;
                        }
                        current = *current.right;
                        continue;
                }
        }
        std::vector<std::string> words_found{};
        for (auto itr = wordlist.data() + current.wordlist_idx + 1;
             itr <
             wordlist.data() + current.wordlist_idx + 1 + current.num_words;
             itr++) {
                words_found.push_back(*itr);
        }
        return words_found;
}

std::vector<std::string> Trie::parse_trie_file(std::string file_path) {
        std::fstream file = std::fstream(file_path.c_str(), std::ios_base::in);
        // read in file

        std::string line;
        std::vector<std::string> wordlist = std::vector<std::string>();
        // int num_nodes = 0;

        while (std::getline(file, line)) {
                // parse line by line
                std::vector<std::string> words = std::vector<std::string>();
                std::istringstream stream(line);
                std::string tree_path; // tells us what letters are present and
                                       // missing in words
                if (!(stream >> tree_path)) {
                        std::cerr << line << '\n';
                        continue;
                }

                std::string next_word;
                while ((stream >> next_word)) {
                        words.push_back(next_word);
                }

                struct TrieNode *current = &this->root;
                for (char c : tree_path) {
                        // build tree
                        Tile t = isupper(c) ? make_tile(c) : make_tile(c - 32);
                        if (current->letter == NONE) {
                                current->letter = t;
                        } else {
                                assert(t == current->letter);
                        }

                        if (isupper(c)) {
                                if (current->left == NULL) {
                                        struct TrieNode *child =
                                            new struct TrieNode(0, 0, NULL,
                                                                NULL, NONE);
                                        current->left = child;
                                        // num_nodes++;
                                }
                                current = current->left;
                        } else {
                                if (current->right == NULL) {
                                        struct TrieNode *child =
                                            new struct TrieNode(0, 0, NULL,
                                                                NULL, NONE);
                                        current->right = child;
                                        // num_nodes++;
                                }
                                current = current->right;
                        }
                }

                // std::cout << num_nodes << '\n';
                // print(&this->root);
                // std::cout << '\n';

                current->wordlist_idx = wordlist.size() - 1;
                current->num_words = words.size();
                wordlist.insert(wordlist.end(), words.begin(), words.end());
        }

        return wordlist;
}

bool Trie::contains(std::string word) const {
        std::vector<Tile> tiles{};
        for (char c : word) {
                tiles.push_back(make_tile(c));
        }

        std::vector<std::string> lookup = get_words(tiles);

        for (std::string lookup_word : lookup) {
                if (lookup_word == word) {
                        return true;
                }
        }
        return false;
}
uint32_t Trie::size() { return wordlist.size(); }
