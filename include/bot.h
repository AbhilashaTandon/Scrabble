#ifndef BOT_H
#define BOT_H
#include "board.h"
#include "helper.h"

class Bot : public Board {
      public:
        bool make_play(std::array<tile_place_t, 7> play);
        Bot(std::string wordlist_file_path, std::string trie_file_path,
              std::string ext_file_path);

      private:
        std::vector<uint32_t> horiz_move_opts;
        std::vector<uint32_t> vert_move_opts;
};

#endif
