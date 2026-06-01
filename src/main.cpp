#include "../include/dawg.h"
#include "../include/wordlist.h"
#include "../include/parse_gcg.h"
#include <filesystem>
#include <cassert>
#include <gtest/gtest.h>

int main(int argc, char **argv) {
        if(argc < 3){
                return -1;
        }


        Dawg d = Dawg(argv[1]);
        d.build_dawg();
        d.print();

        std::string gcg_file_dir = argv[2];


        GCGParser parser(WORDLIST_FILE, GCG_FILE_DIR);

        for (const auto &entry :
             std::filesystem::directory_iterator(gcg_file_dir)) {
                parser.reset(gcg_file_dir + "/" + entry.path().string());
                bool game_result = parser.validate_game(false);
                if (!game_result) {
                        std::cout << entry.path() << std::endl;
                        // parser.validate_game(true);
                }
                assert(game_result);
        }
        
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
