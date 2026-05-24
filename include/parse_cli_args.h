
#ifndef PARSE_CLI_ARGS_H
#define PARSE_CLI_ARGS_H

#include "helper.h"

#include <gtest/gtest.h>
#include <string>

extern std::string wordlist_file;
extern std::string trie_file;
extern std::string extensions_file;
extern std::string games_dir;

// TEST(MyTest, command_line_arg_test) {
//         ASSERT_FALSE(wordlist_file.empty());
//         ASSERT_FALSE(trie_file.empty());
//         ASSERT_FALSE(extensions_file.empty());
// }

class LookupFiles : public testing::Environment {
      public:
        LookupFiles(const std::string &wordlist,
                             const std::string &trie, const std::string &ext,
                             const std::string games);
};

int parse_cli_args(int argc, char *argv[], bool testing);

#endif
