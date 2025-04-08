#include <stdlib.h>
#include <assert.h>
#include "game.h"

void update_player_score(Game *game, int input_row, int input_column) {
    if (game->game_state == FAILED) {
        game->player->score /= 2;
    } else {
        game->player->score += game->board->tiles[input_row][input_column]->value;
    }
    if (game->game_state == SOLVED) {
        game->player->score *= 2;
    }
}

void open_neighbour_tiles(Game *game, int row, int column) {
    assert(game != NULL);
    for (int d_row = -1; d_row <= 1; d_row++) {
        for (int d_column = -1; d_column <= 1; d_column++) {
            int a_row = row + d_row;
            int a_column = column + d_column;
            if (a_row >= 0 && a_row < game->board->row_count && a_column >= 0
                && a_column < game->board->column_count) {
                open_tile(game, a_row, a_column);
            }
        }
    }
}

Game *create_game() {
    Game *game = (Game *)malloc(sizeof(Game));
    Player *player = (Player *)malloc(sizeof(Player));
    game->player = player;
    game->player->score = 1;
    game->game_state = PLAYING;
    return game;
}

void move_mine(Board *board, int first_row, int first_column) {
    int new_row = rand() % board->row_count;
    int new_column = rand() % board->column_count;
    while (board->tiles[new_row][new_column]->is_mine) {
        new_row = rand() % board->row_count;
        new_column = rand() % board->column_count;
    }
    board->tiles[new_row][new_column]->is_mine = 1;
    board->tiles[first_row][first_column]->is_mine = 0;
}

void open_tile(Game *game, int input_row, int input_column) {
    if (game->game_state != PLAYING
        || !is_input_data_correct(game->board, input_row, input_column)) {
        return;
    }

    if (game->board->tiles[input_row][input_column]->tile_state == CLOSED) {
        if (game->board->tiles[input_row][input_column]->is_mine) {
            game->game_state = FAILED;
            open_all_mines(game->board);
            game->player->score /= 2; // Halve player's score when game fails
            return;
        }

        game->board->tiles[input_row][input_column]->tile_state = OPEN;

        if (game->board->tiles[input_row][input_column]->value == 0) {
            open_neighbour_tiles(game, input_row, input_column);
        }
        if (is_game_solved(game->board)) {
            game->game_state = SOLVED;
        }
        update_player_score(game, input_row, input_column);
    }
}

void destroy_game(Game *game) {
    assert(game != NULL);
    destroy_board(game->board);
    free(game->player);
    free(game);
}
