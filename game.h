#ifndef _GAME_H
#define _GAME_H
#include "hall_of_fame.h"
#include "board.h"

typedef enum  {
    FAILED,
    PLAYING,
    SOLVED,
} GameState;

typedef struct {
    Board *board;          /* Struct of the play field */
    Player *player;        /* Struct of user who is playing the Game */
    GameState game_state;  /* Enum for status of the Game */
} Game;

/**
 * Creates and allocates pointers of a Board, Player and Game
 * Set Game state to PLAYING
 * @return pointer of the Game
 */
Game *create_game();

/**
 * Opens selected Tile(s) according to input coordinates
 * Set Game state weather Game is solved or failed
 * Checks if input coordinates are in the correct range if Game state is playing
 */
void open_tile(Game *game, int input_row, int input_column);

/**
 * Frees pointers of the Player and Game
 */
void destroy_game(Game *game);

#endif