#ifndef DAWG_H
#define DAWG_H
#include "helper.h"
#include <algorithm>
#include <functional>
#include <string>
#include <unordered_map>
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
                return h1 ^ (h2 << 1);
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
        Dawg(const std::string &wordlist_file);
        void insert_word(const std::string &word);
        void print() const;
        void print(DawgNode *current, std::string indent, bool is_last,
                   bool backwards) const;
        bool contains(const std::string &word) const;
        // current maybe could be a reference
        std::vector<std::string>
        get_words_from_tiles(const std::unordered_multiset<Tile> &rack,
                             size_t max_depth) const;

        std::vector<std::string>
        get_extensions(const std::unordered_multiset<Tile> &rack,
                       const std::string &word, const size_t &max_prefix_len, const size_t &max_suffix_len) const;

      private:
        int num_nodes;
        std::string wordlist_file;
        DawgNode *start;
        DawgNode *end;

        std::unordered_set<DawgNode *, DawgNodeHash, DawgNodeEq> reg;
        void replace_or_register(DawgNode *d);
        bool has_children(DawgNode *d) const;
        void build_dawg();

        std::pair<DawgNode *, size_t>
        find_common_prefix(std::string word) const;
        void add_suffix(DawgNode *last_state, const std::string &word, size_t index);

        void
        get_words_from_tiles(std::unordered_multimap<Tile, bool> &rack,
                             DawgNode *node, std::string word_path,
                             std::vector<std::string> &words, size_t depth,
                             size_t max_depth) const;

        void
        get_extensions(std::unordered_multimap<Tile, bool> &rack, std::string word,
                       std::string ext_path, DawgNode *node,
                       std::vector<std::string> &exts, const size_t &max_prefix_len, const size_t &max_suffix_len

        ) const;


};

#endif
