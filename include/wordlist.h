#ifndef WORDLIST_H
#define WORDLIST_H
#include "helper.h"
#include <set>
class WordList {
      public:
        WordList(std::string file_path);

        bool contains(std::string) const;
        uint32_t size() const;

      private:
        std::set<std::string> wordlist;


};
#endif
