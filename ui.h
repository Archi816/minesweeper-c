#ifndef MINES_UI_H
#define MINES_UI_H

#include "game.h"

void read_player_name(Game *game);
void play_game(Game *game);
void flag_tile(Game *game, int row, int column);

#endif //MINES_UI_H