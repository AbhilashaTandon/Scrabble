#ifndef DAWG_H
#define DAWG_H
#include "parse_cli_args.h"
#include <algorithm>
#include <string>
#include <unordered_set>


struct DawgNode {
        std::vector<DawgNode *> parents{};
        std::vector<DawgNode *> children{};
        const char c;

        DawgNode() : c(' ') {  }

        DawgNode(char c) : c(c) {}

        bool operator==(DawgNode const &rhs) const {
                if (c != rhs.c) {
                        return false;
                }
                if (children.size() != rhs.children.size()) {
                        return false;
                }
                if (children.size() == 0) {
                        return true;
                }
                return std::is_permutation(children.begin(), children.end(),
                                           rhs.children.begin());
                // O(n^2) but fine for now
        }
};

bool remove_from_vector(std::vector<DawgNode *> &vec, DawgNode * item);

class Dawg {
      public:
        Dawg();
        void build_dawg();
        void insert_word(std::string word);
        void print() const;
        void print(DawgNode *current, std::string indent, bool is_last,
                   bool backwards) const;
        // current maybe could be a reference

      private:
        DawgNode *start;
        DawgNode *end;
        std::vector<DawgNode *> reg;
        void replace_or_register(DawgNode *d);
        std::pair<DawgNode *, size_t>
        find_common_prefix(std::string word) const;
        void add_suffix(DawgNode *last_state, std::string word, size_t index);
        bool has_children(DawgNode * d) const;
};

#endif
