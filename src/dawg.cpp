#include "../include/dawg.h"
#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

Dawg::Dawg() {
        start = new DawgNode('^');
        end = new DawgNode('$');
}

// void Dawg::build_dawg() {
//         std::fstream file =
//             std::fstream(wordlist_file.c_str(), std::ios_base::in);
//         std::string line;
//         while (std::getline(file, line)) {
//                 std::istringstream stream(line);
//                 std::string word;
//                 if (!(stream >> word)) {
//                         std::cerr << line << '\n';
//                         continue;
//                 }
//                 insert_word(word);
//         }
//
//         std::cout << end->parents.size() << '\n';
// }
//
// void Dawg::insert_word(std::string word) {
//         DawgNode *current = start;
//         size_t idx = 0;
//         for (; idx < word.size(); idx++) {
//                 bool child_found = false;
//                 for (DawgNode *child : current->children) {
//                         if (child->c == word[idx]) {
//                                 child_found = true;
//                                 current = child;
//                                 break;
//                         }
//                 }
//                 if (!child_found) {
//                         break;
//                 }
//                 if (idx == word.size() - 1) {
//                         auto end_node = std::find(current->children.begin(),
//                                                   current->children.end(), end);
//                         if (end_node == current->children.end()) {
//                                 // mark node as terminal
//                                 current->children.push_back(end);
//                                 end->parents.push_back(current);
//                                 return;
//                         }
//                         // otherwise word is already present in dawg so we can
//                         // return
//                         return;
//                 }
//         }
//
//         if (current->children.size() > 0) {
//                 replace_or_register(current);
//                 return;
//         }
//
//         // add suffix to dawg
//
//         for (; idx < word.size(); idx++) {
//
//                 bool child_found = false;
//                 for (DawgNode *child : current->children) {
//                         if (child->c == word[idx]) {
//                                 child_found = true;
//                                 current = child;
//                                 break;
//                         }
//                 }
//                 assert(!child_found);
//                 DawgNode * new_node = new DawgNode(word[idx]);
//                 current->children.push_back(new_node);
//                 new_node->parents.push_back(current);
//                 current = new_node;
//         }
//
//         //make the last node we added terminal
//         current->children.push_back(end);
//         end->parents.push_back(current);
// }
//
//         void Dawg::print(DawgNode * current, std::string indent, bool is_last,
//                          bool backwards) const {
//                 std::cout << indent;
//                 if (is_last) {
//                         std::cout << "└─";
//                         indent += "  ";
//                 } else {
//                         std::cout << "├─";
//                         indent += "| ";
//                 }
//                 if (current == start && backwards) {
//                         std::cout << "^\n";
//                         return;
//                 } else if (current == end && !backwards) {
//                         std::cout << "$\n";
//                         return;
//                 }
//
//                 std::cout << current->c << '\n';
//
//                 if (backwards) {
//
//                         size_t num_parents = current->parents.size();
//
//                         for (size_t i = 0; i < num_parents; i++) {
//                                 print(current->parents[i], indent,
//                                       i == num_parents - 1, backwards);
//                         }
//                 } else {
//                         size_t num_children = current->children.size();
//
//                         for (size_t i = 0; i < num_children; i++) {
//                                 print(current->children[i], indent,
//                                       i == num_children - 1, backwards);
//                         }
//                 }
//         }
//
//         void Dawg::print() const { print(start, "", false, false); }
//
//         void Dawg::shrink_trie(DawgNode * leaf) {
//                 if (leaf->parents.size() < 2) {
//                         return;
//                 }
//
//                 std::vector<DawgNode *> unique_parents(27, nullptr);
//
//                 for (DawgNode *parent : leaf->parents) {
//                         if (parent == start) {
//                                 unique_parents[0] = start;
//                                 continue;
//                         }
//
//                         if (parent == leaf) {
//                                 continue;
//                         }
//
//                         int idx = parent->c - 64;
//                         if (idx >= 27 || idx < 0) {
//                                 return;
//                         }
//
//                         if (unique_parents[idx] == nullptr) {
//                                 unique_parents[idx] = parent;
//                         } else {
//                                 parent->add_parents(unique_parents[idx]);
//                         }
//                 }
//
//                 for (auto itr = unique_parents.begin();
//                      itr < unique_parents.end();) {
//                         if (*itr == nullptr) {
//                                 unique_parents.erase(itr);
//                                 continue;
//                         }
//                         itr++;
//                 }
//
//                 for (DawgNode *d : unique_parents) {
//                         shrink_trie(d);
//                 }
//
//                 leaf->parents = unique_parents;
//         }
// }
//
//         void Dawg::build_dawg() {
//                 build_trie();
//                 shrink_trie(this->end);
//                 print(this->end, "", false, true);
//         }
