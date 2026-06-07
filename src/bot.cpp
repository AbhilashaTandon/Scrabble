#include "../include/bot.h"

bool Bot::make_play(move_t play){
        return Board::make_play(play).size() > 0;
}
