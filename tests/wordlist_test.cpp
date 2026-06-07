
#include "../include/dawg.h"
#include <fstream>
#include "../deps/doctest.h"
#include <sstream>
#include <string>
#include "../include/wordlist.h"


TEST_CASE("DawgTests") {
        Dawg d = Dawg(WORDLIST_FILE);

        std::fstream file =
            std::fstream(WORDLIST_FILE, std::ios_base::in);
        std::string line;
        while (std::getline(file, line)) {
                std::istringstream stream(line);
                std::string word;
                if (!(stream >> word)) {
                        INFO((line + "\n"));
                        continue;
                }
                REQUIRE(d.contains(word));
        }
}
