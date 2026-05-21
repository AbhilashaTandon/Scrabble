
#include "../include/wordlist.h"
#include "../include/board.h"
#include <gtest/gtest.h>

TEST(WordlistTests, WordTests) {
        WordList w = WordList("../wordlists/NWL2023-modified.txt", "../wordlists/trie.txt");
        ASSERT_TRUE(w.contains("AA"));
        ASSERT_TRUE(w.contains("AB"));
        ASSERT_TRUE(w.contains("CAKE"));
        ASSERT_TRUE(w.contains("ZEPHYR"));
        ASSERT_FALSE(w.contains("BB"));
        ASSERT_FALSE(w.contains("JKDKFDKFD"));
}

TEST(WordlistTests, BoardTests) {
        Board b = Board("../wordlists/NWL2023-modified.txt", "../wordlists/trie.txt", "../wordlists/extensions.txt");
        ASSERT_TRUE(b.contains("AA"));
        ASSERT_TRUE(b.contains("AB"));
        ASSERT_TRUE(b.contains("CAKE"));
        ASSERT_TRUE(b.contains("ZEPHYR"));
        ASSERT_FALSE(b.contains("BB"));
        ASSERT_FALSE(b.contains("JKDKFDKFD"));
}
