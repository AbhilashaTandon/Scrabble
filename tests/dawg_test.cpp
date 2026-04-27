#include "../include/dawg.h"
#include <gtest/gtest.h>


TEST(DawgTests, CreateDawg){
        Dawg d = Dawg("../wordlists/NWL2023-modified.txt");
}

TEST(DawgTests, FindWord){
        Dawg d = Dawg("../wordlists/testing.txt");
        EXPECT_TRUE(d.contains("ABACUS"));
        EXPECT_TRUE(d.contains("EMBEDDING"));
        EXPECT_TRUE(d.contains("GOONIES"));
        EXPECT_FALSE(d.contains("XXXXXX"));
        EXPECT_FALSE(d.contains("abacus"));
        EXPECT_FALSE(d.contains(""));
}

