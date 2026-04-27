#ifndef DAWG_H
#define DAWG_H
#include "helper.h"
#include <set>
#include <vector>

class DawgNode {
        friend class Dawg;

      public:
        DawgNode(Tile t);
        bool equivalent(DawgNode *other);

      private:
        std::vector<DawgNode *> parents;
        std::vector<DawgNode *> children;
        Tile t;
};

class Dawg {
        friend class DawgNode;

      public:
        Dawg(std::string wordlist_file_path);
        bool contains(std::string word);
        void print(DawgNode *current, std::string indent, bool is_last);

      private:
        DawgNode start;
        DawgNode end;
        void add_word(std::string word, std::set<DawgNode *> *reg);
        void replace_or_register(DawgNode *state, std::set<DawgNode *> *reg);
};

#endif
