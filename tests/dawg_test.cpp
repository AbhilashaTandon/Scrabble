#include "../include/dawg.h"
#include <gtest/gtest.h>


TEST(DawgTests, CreateDawg){
        Dawg d = Dawg("../wordlists/NWL2023-modified.txt");
}


TEST(DawgTests, CommonSubstring){
        Dawg d = Dawg("../wordlists/NWL2023-modified.txt");
        EXPECT_TRUE(d.common_substring("ABACUS").first != 0);
        EXPECT_TRUE(d.common_substring("A").first != 0);
}

TEST(DawgTests, FindWord){
        Dawg d = Dawg("../wordlists/testing.txt");
        EXPECT_TRUE(d.contains("BIKE"));
        EXPECT_TRUE(d.contains("CAD"));
        EXPECT_TRUE(d.contains("LAKE"));
        EXPECT_FALSE(d.contains("XXXXXX"));
        EXPECT_FALSE(d.contains("abacus"));
        EXPECT_FALSE(d.contains(""));
}

