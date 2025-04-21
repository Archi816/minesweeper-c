#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include "ui.h"
#include "board.h"


int get_valid_input(const char *prompt, int min, int max) {
    int value;
    while (1) {
        printf("%s (%d - %d): ", prompt, min, max);
        if (scanf("%d", &value) != 1 || value < min || value > max) {
            printf("Neplatný vstup. Skúste znova.\n");
            while (getchar() != '\n'); // flush stdin
        } else {
            break;
            printf("\n");
        }
    }



    return value;
}

int main() {
        int rows = get_valid_input("Zadajte počet riadkov", 1, 20);
        int columns = get_valid_input("Zadajte počet stĺpcov", 1, 20);

        int max_mines = rows * columns - 1;
        int mines = get_valid_input("Zadajte počet mín", 1, max_mines);

    Game *game = create_game();
    Board *board = create_board(rows, columns, mines);
    game->board = board;



    read_player_name(game);
    play_game(game);
    destroy_game(game);
    exit(EXIT_SUCCESS);
}
