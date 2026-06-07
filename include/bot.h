#ifndef BOT_H
#define BOT_H
#include "board.h"
#include "helper.h"

class Bot : public Board {
      public:
        bool make_play(move_t play);
        Bot(std::string wordlist_file_path);
        std::vector<move_t> get_valid_moves() const;

      private:
  //probably want to keep track of all words played
        std::vector<uint32_t> horiz_move_opts;
        std::vector<uint32_t> vert_move_opts;
};

#endif
