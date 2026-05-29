#ifndef DAWG_H
#define DAWG_H
#include "parse_cli_args.h"
#include <algorithm>
#include <functional>
#include <string>
#include <unordered_set>

struct DawgNode {
        std::unordered_map<char, DawgNode *> children{};
        std::vector<DawgNode *> parents{};
        const char c;

        DawgNode() : c(' ') {}

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
                return children == rhs.children;
        }
};

struct DawgNodeHash {
        std::size_t operator()(const DawgNode *s) const noexcept {
                std::size_t h1 = std::hash<char>{}(s->c);
                std::size_t h2 = 0;
                for (auto &it : s->children) {
                        h2 ^= std::hash<char>{}(it.first);
                }
                return h1 ^ (h2 << 1); // or use boost::hash_combine
        }
};

struct DawgNodeEq {
        bool operator()(DawgNode const *lhs, DawgNode const *rhs) const {
                return lhs->c == rhs->c && lhs->children == rhs->children;
        }
};

bool remove_from_vector(std::vector<DawgNode *> &vec, DawgNode *item);

class Dawg {
      public:
        Dawg();
        void build_dawg();
        void insert_word(std::string word);
        void print() const;
        void print(DawgNode *current, std::string indent, bool is_last,
                   bool backwards) const;
        bool contains(std::string word) const;
        // current maybe could be a reference
        std::vector<std::string>
        get_words_from_tiles(std::unordered_multiset<Tile> &rack, int max_depth) const;
        std::vector<std::string>
        get_words_from_tiles(std::unordered_multimap<Tile, bool> &rack,
                             DawgNode *node, std::string word_path,
                             std::vector<std::string> &words,  int max_depth) const;

      private:
        DawgNode *start;
        DawgNode *end;
        std::unordered_set<DawgNode *, DawgNodeHash, DawgNodeEq> reg;
        void replace_or_register(DawgNode *d);
        std::pair<DawgNode *, size_t>
        find_common_prefix(std::string word) const;
        void add_suffix(DawgNode *last_state, std::string word, size_t index);
        bool has_children(DawgNode *d) const;
        int num_nodes;
};

#endif
