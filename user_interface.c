#include "board.h"
#include "color_term.h"
#include "hall_of_fame.h"
#include "game.h"
#include "user_interface.h"
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>


/**
 * Prints rules for users input
 * Shows example of input selection from user
 */
void print_input_rules() {
    printf("Zadajte číslo riadka, medzeru a číslo stĺpca. Napr. 2 3, 5 9\n");
}

/**
 * Prints top score from list of players
 * @param number_of_all_players in te list
 */
void print_score(Player *list_of_players, int number_of_all_players) {
    assert(list_of_players != NULL);

    printf("%d hráčov, ktorí hrali túto hru.\n", number_of_all_players);
    for (int index = 0; index < number_of_all_players; index++) {
        printf("%s: ", list_of_players[index].name);
        printf("%d\n", list_of_players[index].score);
    }
}

/**
 * Enumerates columns beyond play field
 */
void print_column_coordinates(int column_count) {

    printf("\n   ");
    for (int e = 1; e <= column_count; e++) {
        printf("%d ", e);
    }
    printf("\n");
}

/**
 * Prints one single Tile
 */
void print_tile(Tile *tile, bool is_mine_on_selected_tile) {
    assert(tile != NULL);

    if (tile->tile_state == OPEN && tile->is_mine) {
        if (is_mine_on_selected_tile) {
            // sets red mine just for mine on the input coordinates
            set_terminal_color(color_for_value(tile->value));
        }
        printf("X");
        set_terminal_color(COLOR_DEFAULT);
    }
    if (tile->tile_state == CLOSED) {
        printf("-");
    } else if (tile->tile_state == OPEN && !tile->is_mine) {
        set_terminal_color(color_for_value(tile->value));
        printf("%d", tile->value);
        set_terminal_color(COLOR_DEFAULT);
    } else if (tile->tile_state == MARKED) {
        printf("!");
    }
}

/**
 * Prints whole play field
 */
void print_play_field(Game *game, int input_row, int input_column) {
    assert(game != NULL);

    print_column_coordinates(game->board->column_count);
    int row_enumeration = 1;
    for (int row = 0; row < game->board->row_count; row++) {
        printf("%d  ", row_enumeration);

        for (int column = 0; column < game->board->column_count; column++) {

            if (row == input_row - 1 && column == input_column - 1) {
                print_tile(game->board->tiles[row][column], true);
            } else {
                print_tile(game->board->tiles[row][column], false);
            }
            printf(" ");
        }
        row_enumeration++;
        printf("\n");
    }
    printf("\n");
}

/**
 * Handles players input process
 * Loops until game state is playing
 */
void game_loop(Game *game) {
    assert(game != NULL);
    int input, input_row = -1, input_column = -1;

    do {
        print_play_field(game, input_row, input_column);
        print_input_rules();

        while ((input = scanf("%d %d", &input_row, &input_column)) == 0) {
            scanf("%*[^\n] %*[^\n]");
            print_input_rules();
        }
        if (input != EOF) {
            // if input is not empty or is not correct then open tile
            open_tile(game, input_row - 1, input_column - 1);
        }

    } while (game->game_state == PLAYING);
    print_play_field(game, input_row, input_column);
}

void read_player_name(Game *game) {
    assert(game != NULL);
    printf("Zadajte vaše meno prosím: \n");
    char name_of_player[MAX_PLAYER_LENGTH];
    fgets(name_of_player, MAX_PLAYER_LENGTH, stdin);
    remove_spaces_from_name(name_of_player);
    strcpy(game->player->name, name_of_player);
}

void play_game(Game *game) {
    assert(game != NULL);

    Player list_of_players[PLAYERS_LIMIT];
    int size_of_list = load_score_to_list(list_of_players);
    if (size_of_list > 0) {
        print_score(list_of_players, size_of_list);
    }
    game_loop(game);

    if (game->game_state == SOLVED) {
        printf("Gratulujem %s. Riešenie je správne!\n", game->player->name);
    } else {
        printf("Ľutujem %s. Riešenie je nesprávne!\n", game->player->name);
    }
    printf("Vaše skóre je: %d\n", game->player->score);

    bool is_player_added_to_list =
            add_player_to_list(list_of_players, &size_of_list, *game->player);

    if (is_player_added_to_list) {
        save_players_to_file(list_of_players, size_of_list);
    }
}

Color value_colors[] = {
        COLOR_DEFAULT, COLOR_BOLD_RED, COLOR_GREEN,
        COLOR_BOLD_MAGENTA, COLOR_CYAN, COLOR_MAGENTA,
        COLOR_YELLOW, COLOR_BLUE, COLOR_BOLD_YELLOW
};

Color color_for_value(int value) {
    if (value == -1) {
        return COLOR_RED;
    } else {
        return value_colors[value];
    }
}

void remove_spaces_from_name(char *name) {

    const char *character = name;
    do {
        while (isspace(*character)) {
            ++character;
        }
    } while ((*name++ = *character++));
}