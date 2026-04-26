#include "../include/trie.h"
#include <cassert>
#include <cctype>
#include <fstream>
#include <iostream>
#include <queue>
#include <sstream>
#include <string>
#include <span>

Trie::Trie(std::string file_path) {
        std::fstream file = std::fstream(file_path.c_str(), std::ios_base::in);
        std::string line;
        root = {0, 0, 0, 0, NONE};
        std::vector<std::string> words = std::vector<std::string>();
        int num_nodes = 0;
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

                struct Node *current = &root;
                for (char c : tree_path) {
                        // if (isupper(c)) {
                        //         if (current->left == NULL) {
                        //                 struct Node *child = new struct Node(
                        //                     0, NULL, NULL, Tile(c - 64));
                        //                 current->left = child;
                        //                 std::cout << "new node" << " " << child->letter << '\n';
                        //         }
                        //         current = current->left;
                        // } else {
                        //         if (current->right == NULL) {
                        //                 struct Node *child = new struct Node(
                        //                     0, NULL, NULL, Tile(c - 96));
                        //                 std::cout << "new node" << " " << child->letter << '\n';
                        //                 current->right= child;
                        //         }
                        //         current = current->right;
                        // }
                        current->letter = isupper(c) ? Tile(c - 64) : Tile(c - 96);

                        if(isupper(c)){
                                if(current->left == NULL){
                                        struct Node *child = new struct Node(0, 0, NULL, NULL, NONE);
                                        current->left = child;
                                        num_nodes++;
                                }
                                current = current->left;
                        }
                        else{
                                if(current->right == NULL){
                                        struct Node *child = new struct Node(0, 0, NULL, NULL, NONE);
                                        current->right = child;
                                        num_nodes++;
                                }
                                current = current->right;
                        }
                }
                
                std::cout << num_nodes << '\n';


                current->wordlist_idx = wordlist.size() - 1;
                current->num_words = words.size();
                wordlist.insert(wordlist.end(), words.begin(), words.end());

        }

        std::cout << "All words loaded" << "\n";
        std::queue<struct Node *> ancestors = std::queue<struct Node *>();
        ancestors.push(&root);
        assert(root.left != NULL);
        assert(root.right != NULL);

        while (!ancestors.empty()) {
                struct Node *current = ancestors.front();
                ancestors.pop();
                // std::cout << ancestors.size() << " ";
                // std::cout << char(current->letter + 64) << '\n';
                if (current->left != NULL)
                        ancestors.push(current->left);
                if (current->right != NULL)
                        ancestors.push(current->right);
        }
}

std::span<std::string> Trie::get_words(std::vector<Tile> available) {
        struct Node *current = &root;
        while (true) {
                if (current->letter == NONE) {
                        continue;
                }
                bool present = false;
                for (std::vector<Tile>::iterator  i = available.begin(); i < available.end(); i++) {
                        if (*i == current->letter) {
                                present = true;
                                available.erase(i);
                                break;
                        }
                }
                if (present) {
                        if (current->left == NULL) {
                                return std::span(wordlist.data() + current->wordlist_idx, current->num_words);
                        }
                        std::cout << char(current->letter + 64);
                        current = current->left;
                        continue;
                }

                else {
                        if (current->right == NULL) {
                                return std::span(wordlist.data() + current->wordlist_idx, current->num_words);
                        }
                        std::cout << char(current->letter + 96);
                        current = current->right;
                        continue;
                }
        }
}
