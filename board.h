#ifndef MINES_BOARD_H
#define MINES_BOARD_H

#define MAX_ROW_COUNT 30
#define MAX_COLUMN_COUNT 30

#include <stdbool.h>

typedef enum {
    CLOSED,
    OPEN,
    MARKED
} TileState;

typedef struct {
    bool is_mine;                /* Records if mine is on the Tile */
    TileState tile_state;        /* Enum for status of the Tile state */
    int value;                   /* Number of neighbour tiles where is mine on; -1 if mine is not on */
} Tile;

typedef struct {
    int row_count;                                  /* Number of rows in the Board */
    int column_count;                               /* Number of columns in the Board */
    int mine_count;                                 /* Number of mines in the Board */
    Tile *tiles[MAX_ROW_COUNT][MAX_COLUMN_COUNT];   /* 2-dimensional struct array of the tiles */
} Board;

/**
 * Creates and allocates pointer of the Board
 * @return pointer of the Board
 */
Board *create_board(int row_count, int column_count, int mine_count);

/**
 * Frees pointer of the each Tile in the Board
 * Frees pointer of the Board
 */
void destroy_board(Board *board);

/**
 * Checks if Game is solved
 * @return false if Board consists of any Tile which is closed and has clue value, else true
 */
bool is_game_solved(Board *board);

/**
 * Checks if input row and column are within correct range
 * @return true if input coordinates are within the range, false otherwise
 */
bool is_input_data_correct(Board *board, int input_row, int input_column);

/**
 * If Game is lost all mines are shown
 */
void open_all_mines(Board *board);

#endif //MINES_BOARD_H