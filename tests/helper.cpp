#include "../include/helper.h"
#include <gtest/gtest.h>

TEST(HelperFnTests, GetPosTest) {
        for (int i = 0; i < 15; i++) {
                for (int j = 0; j < 15; j++) {
                        position_t pos = get_pos(i, j);
                        ASSERT_EQ(pos, i + j * 15);
                        std::pair<uint8_t, uint8_t> coords = get_xy(pos);
                        EXPECT_EQ(i, coords.first);
                        EXPECT_EQ(j, coords.second);
                }
        }
}
