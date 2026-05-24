
#include "../include/parse_cli_args.h"
#include <gtest/gtest.h>

int main(int argc, char *argv[]) {

        if (argc == 5) {
                testing::InitGoogleTest(&argc, argv);
                testing::AddGlobalTestEnvironment(
                    new LookupFiles(std::string(argv[1]), std::string(argv[2]),
                                    std::string(argv[3]), std::string(argv[4])

                                        ));
                return RUN_ALL_TESTS();
        }

        return 0;
}
