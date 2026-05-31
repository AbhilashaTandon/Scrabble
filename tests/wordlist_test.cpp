
#include "../include/dawg.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include "../include/board.h"
#include "../include/dawg.h"
#include "../include/parse_cli_args.h"
#include <gtest/gtest.h>


TEST(WordlistTests, BoardTests) {
        Board b = Board(trie_file, extensions_file);
        ASSERT_TRUE(b.contains("AA"));
        ASSERT_TRUE(b.contains("AB"));
        ASSERT_TRUE(b.contains("CAKE"));
        ASSERT_TRUE(b.contains("ZEPHYR"));
        ASSERT_FALSE(b.contains("BB"));
        ASSERT_FALSE(b.contains("JKDKFDKFD"));
}


TEST(WordlistTests, DawgTests) {
        Dawg d = Dawg();
        d.build_dawg();
        ASSERT_TRUE(d.contains("AA"));
        ASSERT_TRUE(d.contains("AB"));
        ASSERT_TRUE(d.contains("CAKE"));
        ASSERT_TRUE(d.contains("ZEPHYR"));
        ASSERT_FALSE(d.contains("BB"));
        ASSERT_FALSE(d.contains("JKDKFDKFD"));
        ASSERT_FALSE(d.contains("A"));
        ASSERT_FALSE(d.contains("B"));
        ASSERT_FALSE(d.contains("C"));
        ASSERT_FALSE(d.contains("D"));
        ASSERT_FALSE(d.contains("E"));
        ASSERT_FALSE(d.contains("F"));
        ASSERT_FALSE(d.contains("G"));
}


TEST(WordlistTests, FullTest) {
        Dawg d = Dawg();

        std::fstream file =
            std::fstream(wordlist_file.c_str(), std::ios_base::in);
        std::string line;
        while (std::getline(file, line)) {
                std::istringstream stream(line);
                std::string word;
                if (!(stream >> word)) {
                        std::cerr << line << '\n';
                        continue;
                }

                assert(d.contains(word));
        }
}
