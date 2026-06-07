

#ifndef PARSE_GCG_H
#define PARSE_GCG_H
#include "board.h"
#include "helper.h"

class GCGParser {
      public:
        GCGParser(std::string wordlist_file, std::string file_path);
        bool validate_game(bool verbose);
        bool parse_move(std::string line, bool verbose);
        void reset(std::string file_path);

      private:
        std::string player1;
        std::string player2;
        Board b;
        std::string file_path;

        bool parse_special_actions(std::string &position,
                                   std::istringstream &stream,
                                   int &point_difference, int &updated_score,
                                   bool is_player_1, bool &retFlag);
};

#endif
