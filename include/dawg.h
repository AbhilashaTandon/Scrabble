#ifndef DAWG_H
#define DAWG_H
#include "helper.h"
#include <vector>

class DawgNode {
        friend class Dawg;
      public:
        DawgNode(Tile t);

      private:
        std::vector<DawgNode *> parents;
        std::vector<DawgNode *> children;
        Tile t;
};

class Dawg {
        friend class DawgNode;
      public:
        Dawg(std::string wordlist_file_path);
        bool contains(std::string word) const;

      private:
        void compress();
        DawgNode start;
        DawgNode end;
        void add_word(std::string word);
};

#endif
