#include "../include/parse_cli_args.h"
#include <gtest/gtest.h>

std::string wordlist_file = "";
std::string trie_file = "";
std::string extensions_file = "";
std::string games_dir = "";

LookupFiles::LookupFiles(const std::string &wordlist, const std::string &trie,
                         const std::string &ext, const std::string games) {
        assert(wordlist != "");
        wordlist_file = wordlist;
        assert(wordlist_file != "");
        trie_file = trie;
        extensions_file = ext;
        games_dir = games;
}

