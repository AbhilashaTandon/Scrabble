#define DOCTEST_CONFIG_IMPLEMENT
#include "../deps/doctest.h"
#include "../include/wordlist.h"

int main(int argc, char **argv) {
        doctest::Context context;

        context.applyCommandLine(argc, argv);


        int res = context.run();  // run
        if (context.shouldExit()) // important - query flags (and --exit) rely
                                  // on the user doing this
                return res;       // propagate the result of the tests

        // d.print();
        // setlocale(LC_ALL, "en_US.UTF-8");
        // for (const auto &entry :
        // std::filesystem::directory_iterator(games_dir)) {
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
