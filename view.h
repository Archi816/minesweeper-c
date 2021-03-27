#ifndef MINES_VIEW_H
#define MINES_VIEW_H

#include "board.h"
#include "hall_of_fame.h"

char *view_hof(Player *players, int players_count);

char *view_play_field(Board *board, int input_row, int input_column);

#endif //MINES_VIEW_H
