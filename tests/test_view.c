#include <stdbool.h>
#include "greatest.h"
#include "../view.h"
#include "../termcolor.h"

TEST view_nonempty_hof() {
    int players_count = 3;
    Player players[] = {
        {"peter", 99},
        {"jozo",  55},
        {"alena", 43},
    };
    char *result = view_hof(players, players_count);
    ASSERT_STR_EQ(
            "3 hráčov, ktorí hrali túto hru.\n"
            "peter: 99\n"
            "jozo: 55\n"
            "alena: 43\n",
            result);
    PASS();
}

TEST view_closed_board() {
    Board *board = create_board(4, 4, 0);
    char *field = view_play_field(board, 0, 0);
    ASSERT_STR_EQ("   1 2 3 4 \n"
                  "1  - - - - \n"
                  "2  - - - - \n"
                  "3  - - - - \n"
                  "4  - - - - \n",
                  field);
    free(board);
    free(field);
    PASS();
}

TEST view_opened_empty_board() {
    Board *board = create_board(4, 4, 0);
    for (int i = 0; i < board->row_count; i++) {
        for (int j = 0; j < board->column_count; j++) {
            board->tiles[i][j]->tile_state = OPEN;
        }
    }
    char *field = view_play_field(board, 0, 0);
    ASSERT_STR_EQ("   1 2 3 4 \n"
                  "1  0 0 0 0 \n"
                  "2  0 0 0 0 \n"
                  "3  0 0 0 0 \n"
                  "4  0 0 0 0 \n",
                  field);
    free(board);
    free(field);
    PASS();
}

TEST view_open_mine() {
    Board *board = create_board(4, 4, 0);
    int x = 1, y = 2;
    board->tiles[x][y]->is_mine = true;
    board->tiles[x][y]->tile_state = OPEN;
    char *field = view_play_field(board, 0, 0);
    ASSERT_STR_EQ("   1 2 3 4 \n"
                  "1  - - - - \n"
                  "2  - - X - \n"
                  "3  - - - - \n"
                  "4  - - - - \n",
                  field);
    free(board);
    free(field);
    PASS();
}


TEST view_just_opened_mine() {
    Board *board = create_board(4, 4, 0);
    int x = 1, y = 2;
    board->tiles[x][y]->is_mine = true;
    board->tiles[x][y]->tile_state = OPEN;
    char *field = view_play_field(board, x+1, y+1);
    ASSERT_STR_EQ("   1 2 3 4 \n"
                  "1  - - - - \n"
                  "2  - - " COLOR_RED "X" COLOR_DEFAULT " - \n"
                  "3  - - - - \n"
                  "4  - - - - \n",
                  field);
    free(board);
    free(field);
    PASS();
}

TEST view_multiple_opened_tiles() {
    Board *board = create_board(4, 4, 0);
    board->tiles[0][0]->is_mine = true;
    board->tiles[0][0]->tile_state = OPEN;
    board->tiles[1][1]->tile_state = OPEN;
    board->tiles[2][1]->value = 1;
    board->tiles[2][1]->tile_state = OPEN;
    board->tiles[3][2]->value = 2;
    board->tiles[3][2]->tile_state = OPEN;
    char *field = view_play_field(board, 0, 0);
    ASSERT_STR_EQ("   1 2 3 4 \n"
                  "1  X - - - \n"
                  "2  - 0 - - \n"
                  "3  - " COLOR_BOLD_RED "1" COLOR_DEFAULT " - - \n"
                  "4  - - " COLOR_GREEN "2" COLOR_DEFAULT " - \n",
                  field);
    free(board);
    free(field);
    PASS();
}


SUITE (test_view) {
    RUN_TEST(view_nonempty_hof);
    RUN_TEST(view_closed_board);
    RUN_TEST(view_opened_empty_board);
    RUN_TEST(view_open_mine);
    RUN_TEST(view_just_opened_mine);
    RUN_TEST(view_multiple_opened_tiles);
}