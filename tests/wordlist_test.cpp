
#include "../include/dawg.h"
#include <fstream>
#include "../deps/doctest.h"
#include <sstream>
#include <string>
#include "../include/wordlist.h"


TEST_CASE("DawgTests") {
        Dawg d = Dawg("../wordlists/NWL2023-modified.txt");

        std::fstream file =
            std::fstream("../wordlists/NWL2023-modified.txt", std::ios_base::in);
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
