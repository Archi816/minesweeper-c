#ifndef MINES_UI_H
#define MINES_UI_H

#include "game.h"

/**
 * Scans name of a Player
 */
void read_player_name(Game *game);

/**
 * Handles whole process of the Game
 * Calls game_loop function
 */
void play_game(Game *game);

#endif //MINES_UI_H