#include "../include/dawg.h"
#include <gtest/gtest.h>

TEST(DawgTests, DawgNode) {
        DawgNode a = DawgNode(Tile::A);
        DawgNode b = DawgNode(Tile::B);
        DawgNode c = DawgNode(Tile::C);
        a.add_child(&b);
        EXPECT_TRUE(a.has_child(&b));
        a.add_child(&c);
        EXPECT_TRUE(a.has_child(&c));
        c.add_parent(&b);
        EXPECT_TRUE(c.has_parent(&b));
        c.remove_parent(&b);
        EXPECT_FALSE(c.has_parent(&b));
        c.add_parent(&a);
        EXPECT_TRUE(c.has_parent(&a));
        c.remove_parent(&a);
        EXPECT_FALSE(c.has_parent(&a));
        a.remove_child(&c);
        EXPECT_FALSE(a.has_child(&c));
        a.remove_child(&b);
        EXPECT_FALSE(a.has_child(&b));
}

TEST(DawgTests, DawgInsertion) {
        std::vector<std::string> wordlist = {"BAKE", "BALE", "CAKE", "DALE", "DAVE", "BANE", "BA", "AKE", "BAKED", "ABAKE", ""};

        Dawg d = Dawg(wordlist);
        for(std::string word : wordlist){
                // std::cout << word << '\n';
                EXPECT_TRUE(d.contains(word));
        }
        EXPECT_FALSE(d.contains("B"));
        EXPECT_FALSE(d.contains("A"));
        EXPECT_FALSE(d.contains("AB"));
        EXPECT_FALSE(d.contains("ABAKED"));
        EXPECT_FALSE(d.contains("BAKER"));
        EXPECT_TRUE(d.contains("BAKE"));
}

// TEST(DawgTests, CreateDawg){
//         Dawg d = Dawg("../wordlists/NWL2023-modified.txt");
// }
//
//
// TEST(DawgTests, CommonSubstring){
//         Dawg d = Dawg("../wordlists/NWL2023-modified.txt");
//         EXPECT_TRUE(d.common_prefix("ABACUS").first != 0);
//         EXPECT_TRUE(d.common_prefix("A").first != 0);
// }
//
// TEST(DawgTests, FindWord){
//         Dawg d = Dawg("../wordlists/testing.txt");
//         EXPECT_TRUE(d.contains("BIKE"));
//         EXPECT_TRUE(d.contains("CAD"));
//         EXPECT_TRUE(d.contains("LAKE"));
//         EXPECT_FALSE(d.contains("XXXXXX"));
//         EXPECT_FALSE(d.contains("abacus"));
//         EXPECT_FALSE(d.contains(""));
// }
