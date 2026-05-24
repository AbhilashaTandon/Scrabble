#include "../include/test.h"
#include "gtest/gtest.h"


std::string wordlist_file = "";
std::string trie_file = "";
std::string extensions_file = "";

class LookupFiles : public testing::Environment {
      public:
        explicit LookupFiles(const std::string &wordlist,
                             const std::string &trie, const std::string &ext) {
                wordlist_file = wordlist;
                trie_file = trie;
                extensions_file = ext;
        }
};

int main(int argc, char *argv[]) {

        if (argc == 4) {
                testing::InitGoogleTest(&argc, argv);
                testing::AddGlobalTestEnvironment(
                    new LookupFiles(std::string(argv[1]), std::string(argv[2]),
                                    std::string(argv[3])));
                return RUN_ALL_TESTS();
        } else {
                return 0;
        }
}
