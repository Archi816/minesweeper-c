#ifndef _U_I
#define _U_I

#include "game.h"
#include "color_term.h"

/**
 * Scans name of a Player
 */
void read_player_name(Game *game);

/**
 * Handles whole process of the Game
 * Calls game_loop function
 */
void play_game(Game *game);

/**
 * Sets standard input colour according to clue value
 * Calls set_terminal_colour function
 * @param value of the clue Tile
 */
Color color_for_value(int value);

/**
* Removes spaces from players name
*/
void remove_spaces_from_name(char *name);

#endif