#ifndef _U_I
#define _U_I

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

#endif