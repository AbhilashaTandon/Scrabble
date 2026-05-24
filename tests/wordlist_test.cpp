
#include "../include/wordlist.h"
#include "../include/board.h"
#include "../include/parse_cli_args.h"
#include <gtest/gtest.h>

TEST(WordlistTests, WordTests) {
        WordList w = WordList(wordlist_file, trie_file);
        ASSERT_TRUE(w.contains("AA"));
        ASSERT_TRUE(w.contains("AB"));
        ASSERT_TRUE(w.contains("CAKE"));
        ASSERT_TRUE(w.contains("ZEPHYR"));
        ASSERT_FALSE(w.contains("BB"));
        ASSERT_FALSE(w.contains("JKDKFDKFD"));
}

TEST(WordlistTests, BoardTests) {
        Board b = Board(wordlist_file, trie_file, extensions_file);
        ASSERT_TRUE(b.contains("AA"));
        ASSERT_TRUE(b.contains("AB"));
        ASSERT_TRUE(b.contains("CAKE"));
        ASSERT_TRUE(b.contains("ZEPHYR"));
        ASSERT_FALSE(b.contains("BB"));
        ASSERT_FALSE(b.contains("JKDKFDKFD"));
}
