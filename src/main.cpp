// #include "../include/board.h"
#include "../include/parse_cli_args.h"
#include "../include/parse_gcg.h"
#include <cassert>
// #include <filesystem>
// #include <iostream>

int main(int argc, char **argv) {


        if (argc == 5) {
                LookupFiles l =
                    LookupFiles(std::string(argv[1]), std::string(argv[2]),
                                std::string(argv[3]), std::string(argv[4]));
        }
        setlocale(LC_ALL, "en_US.UTF-8");
        GCGParser parser("short_game_with_bad_moves.gcg");
        parser.validate_game(true);

        return 0;
}
