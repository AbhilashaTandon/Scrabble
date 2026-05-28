#include "../include/dawg.h"
#include <algorithm>
#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>

bool find_in_vector(std::vector<DawgNode *> &vec, DawgNode *item) {
        auto itr = std::find(vec.begin(), vec.end(), item);
        return itr != vec.end();
}

bool remove_from_vector(std::vector<DawgNode *> &vec, DawgNode *item) {
        auto itr = std::find(vec.begin(), vec.end(), item);
        bool found = itr != vec.end();
        vec.erase(itr);
        return found;
}

Dawg::Dawg() {
        start = new DawgNode('<');
        end = new DawgNode('>');
}

bool Dawg::has_children(DawgNode *d) const {
        if (d->children.size() == 0) {
                return false;
        }
        if (d->children.size() > 1) {
                return true;
        }
        return d->children[0] != end;
}

void Dawg::build_dawg() {
        reg.clear();
        std::fstream file =
            std::fstream(wordlist_file.c_str(), std::ios_base::in);
        std::string line;
        while (std::getline(file, line)) {
                std::istringstream stream(line);
                std::string word;
                if (!(stream >> word)) {
                        std::cerr << line << '\n';
                        continue;
                }
                insert_word(word);
                if (end->parents.size() > 26) {
                        std::cout << word << '\n';
                        return;
                }
                assert(start->parents.size() == 0);
                assert(end->children.size() == 0);
        }
        replace_or_register(start);
}

std::pair<DawgNode *, size_t> Dawg::find_common_prefix(std::string word) const {
        DawgNode *current = start;
        for (size_t i = 0; i < word.size(); i++) {
                bool child_found = false;
                for (DawgNode *child : current->children) {
                        if (child->c == word[i]) {
                                child_found = true;
                                current = child;
                                break;
                        }
                }

                // child not found
                if (!child_found) {
                        assert(current != nullptr);
                        return std::make_pair(current, i);
                }
        }

        assert(current != end);
        assert(current != nullptr);
        if (!find_in_vector(current->children, end)) {
                assert(!find_in_vector(end->parents, current));
                current->children.push_back(end);
                end->parents.push_back(current);
                return std::make_pair(end, word.size());
        } else {
                return std::make_pair(current, word.size());
        }
}

void Dawg::add_suffix(DawgNode *last_state, std::string word, size_t index) {
        if (last_state == end) {
                return;
        }
        assert(last_state != nullptr);
        DawgNode *current = last_state;
        for (size_t i = index; i < word.size(); i++) {
                assert(current != end);
                assert(end->c == '>');
                DawgNode *new_node = new DawgNode(word[i]);
                assert(end->c == '>');
                assert(new_node != end);
                current->children.push_back(new_node);
                new_node->parents.push_back(current);
                current = new_node;
        }
        assert(current != end);
        current->children.push_back(end);
        end->parents.push_back(current);
}

void Dawg::insert_word(std::string word) {
        auto [last_state, idx] = find_common_prefix(word);
        if (last_state == end) {
                return;
        }
        if (has_children(last_state)) {
                replace_or_register(last_state);
        }
        add_suffix(last_state, word, idx);
}

void Dawg::replace_or_register(DawgNode *d) {
        assert(d != nullptr);
        assert(d != end);
        assert(has_children(d));
        DawgNode *last_child = d->children.front();
        char last_letter = last_child->c;
        for (DawgNode *child : d->children) {
                if (child->c > last_letter) {
                        last_child = child;
                        last_letter = child->c;
                }
        }
        assert(last_child != nullptr);

        if (has_children(last_child)) {
                replace_or_register(last_child);
        }

        for (DawgNode *saved : reg) {
                assert(saved != nullptr);
                if (*saved != *last_child) {
                        continue;
                }

                remove_from_vector(d->children, last_child);
                d->children.push_back(saved);
                saved->parents.push_back(d);
                // replace last child with saved

                for (DawgNode *child : last_child->children) {
                        assert(find_in_vector(saved->children, child));
                        // must share same children
                        assert(find_in_vector(child->parents, saved));
                        assert(find_in_vector(child->parents, last_child));
                        remove_from_vector(child->parents, last_child);
                }
                assert(last_child != end);
                delete last_child;
                return;
        }

        reg.push_back(last_child);
}

void Dawg::print(DawgNode *current, std::string indent, bool is_last,
                 bool backwards) const {
        assert(current != nullptr);
        std::cout << indent;
        if (is_last) {
                std::cout << "└─";
                indent += "  ";
        } else {
                std::cout << "├─";
                indent += "| ";
        }
        if (current == start && backwards) {
                std::cout << "<\n";
                return;
        } else if (current == end && !backwards) {
                std::cout << ">\n";
                return;
        }

        std::cout << current->c << '\n';

        if (backwards) {

                size_t num_parents = current->parents.size();
                size_t i = 0;

                for (DawgNode *d : current->parents) {
                        print(d, indent, i == num_parents - 1, backwards);
                        i++;
                }
        } else {
                size_t num_children = current->children.size();
                size_t i = 0;

                for (DawgNode *d : current->children) {
                        print(d, indent, i == num_children - 1, backwards);
                        i++;
                }
        }
}

void Dawg::print() const {
        print(start, "", false, false);
        print(end, "", false, true);
}
