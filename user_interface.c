#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <stdlib.h>

#include "user_interface.h"
#include "view.h"


void print_play_field(Game *game, int input_row, int input_column);

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


void print_play_field(Game *game, int input_row, int input_column) {
    char *field = view_play_field(game->board, input_row, input_column);
    printf("\n%s\n", field);
    free(field);
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


void remove_spaces_from_name(char *name) {
    const char *character = name;
    do {
        while (isspace(*character)) {
            ++character;
        }
    } while ((*name++ = *character++));
}