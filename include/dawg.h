#ifndef DAWG_H
#define DAWG_H
#include "helper.h"
#include <set>
#include <string>
#include <vector>

class DawgNode {
        friend class Dawg;

      public:
        DawgNode(Tile t);
        bool equivalent(DawgNode *other);
        void add_child(DawgNode *child);
        void add_parent(DawgNode *parent);
        void remove_child(DawgNode *child);
        void remove_parent(DawgNode *parent);
        bool has_child(DawgNode *child);
        bool has_parent(DawgNode *parent);

      private:
        std::vector<DawgNode *> parents;
        std::set<DawgNode *> parents_set;
        std::vector<DawgNode *> children;
        std::set<DawgNode *> children_set;
        Tile t;
};

class Dawg {
        friend class DawgNode;

      public:
        Dawg(std::string wordlist_file_path);
        Dawg(std::vector<std::string> wordlist);
        bool contains(std::string word);
        void print(DawgNode *current, std::string indent, bool is_last, bool backwards);
        std::pair<size_t, DawgNode *> common_substring(std::string word);

      private:
        DawgNode start;
        DawgNode end;
        void add_word(std::string word, std::set<DawgNode *> *reg);
        void replace_or_register(DawgNode *state, std::set<DawgNode *> *reg);
        bool is_terminal(DawgNode *node) const;
};

#endif
