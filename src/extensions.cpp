#include "../include/extensions.h"
#include <cassert>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <unordered_map>

extension_map read_file(std::string file_path) {

        std::fstream file = std::fstream(file_path.c_str(), std::ios_base::in);
        // read in file

        std::string word;
        std::string line;
        extension_map extensions = extension_map();

        while (std::getline(file, line)) {
                // parse line by line
                extension affixes =
                        extension();
                std::istringstream stream(line);
                std::string tree_path; // tells us what letters are present and
                                       // missing in words
                if (!(stream >> word)) {
                        std::cerr << line << '\n';
                        continue;
                }

                std::string affix;
                while ((stream >> affix)) {
                        auto index = affix.find('-');
                        affixes.push_back(std::make_pair(
                            affix.substr(0, index), affix.substr(index + 1)));
                }

                extensions[word] = affixes;

        }

        return extensions;
}


