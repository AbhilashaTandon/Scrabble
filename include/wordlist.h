#ifndef WORDLIST_H
#define WORDLIST_H
#include "helper.h"
#include "trie.h"
#include <set>
class WordList {
      public:
        WordList(std::string wordlist_file_path, std::string trie_file_path);

        bool contains(std::string) const;
        uint32_t size() const;

      private:
        std::set<std::string> wordlist;
        Trie trie;

};
#endif
