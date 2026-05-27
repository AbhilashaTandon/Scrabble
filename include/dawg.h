#ifndef DAWG_H
#define DAWG_H
#include "parse_cli_args.h"
#include <algorithm>
#include <string>
#include <unordered_set>

struct DawgNode {
        std::unordered_set<DawgNode *> parents{};
        std::unordered_set<DawgNode *> children{};
        char c;

        DawgNode(char c) : c(c) {}

        bool operator==( DawgNode const & rhs ) const{
                return c == rhs.c && children == rhs.children;
        }
};

class Dawg {
      public:
        Dawg();
        void build_dawg();
        void insert_word(std::string word);
        void replace_or_register(DawgNode *d);
        void print() const;
        void print(DawgNode *current, std::string indent, bool is_last,
                   bool backwards) const;
        //current maybe could be a reference

      private:
        DawgNode *start;
        DawgNode *end;
        std::unordered_set<DawgNode *> reg{};
};

#endif
