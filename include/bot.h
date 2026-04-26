#ifndef BOT_H
#define BOT_H
#include "helper.h"
#include "board.h"

class Bot : public Board{
public:
        void make_play();
private:
        std::vector<uint32_t> horiz_move_opts;
        std::vector<uint32_t> vert_move_opts;
        //keep track of words played so far???
};

#endif
