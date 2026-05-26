

#ifndef PARSE_GCG_H
#define PARSE_GCG_H
#include "board.h"
#include "helper.h"
#include "parse_cli_args.h"

class GCGParser {
public:
        GCGParser(std::string file_path);
        bool validate_game(bool verbose);
        bool parse_move(std::string line, bool verbose);
        void reset(std::string file_path);

      private:
        std::string player1;
        std::string player2;
        Board b;
        std::string file_path;
};

#endif
