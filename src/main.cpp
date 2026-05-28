#include "../include/parse_cli_args.h"
#include "../include/dawg.h"
#include "../include/parse_gcg.h"
#include <cassert>
#include <filesystem>
#include <gtest/gtest.h>
#include "../include/parse_cli_args.h"
#include "../include/parse_gcg.h"
#include <cassert>
#include "../include/bot.h"

int main(int argc, char **argv) {


        if (argc == 5) {
                LookupFiles l =
                    LookupFiles(std::string(argv[1]), std::string(argv[2]),
                                std::string(argv[3]), std::string(argv[4]));
        }
        Dawg d = Dawg();
        d.build_dawg();
        d.print();
        // d.print();
        // setlocale(LC_ALL, "en_US.UTF-8");
        // for (const auto &entry : std::filesystem::directory_iterator(games_dir)) {
        //         GCGParser parser(entry.path());
        //         bool game_result = parser.validate_game(false);
        //         if (!game_result) {
        //                 std::cout << entry.path() << std::endl;
        //                 // parser.validate_game(true);
        //         }
        //         assert(game_result);
        // }


        return 0;
}
