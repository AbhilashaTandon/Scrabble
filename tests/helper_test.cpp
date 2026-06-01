#include "../include/helper.h"
#include "../deps/doctest.h"

TEST_CASE("GetPosTest") {
        for (int i = 0; i < 15; i++) {
                for (int j = 0; j < 15; j++) {
                        position_t pos = get_pos(i, j);
                        REQUIRE_EQ(pos, i + j * 15);
                        std::pair<uint8_t, uint8_t> coords = get_xy(pos);
                        CHECK_EQ(i, coords.first);
                        CHECK_EQ(j, coords.second);
                }
        }
}
