#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include "ui.h"
#include "board.h"

bool play_again(){
   char choice = '\0';
   printf("Chceli by ste si zahrať znova? (y/n) ");
   scanf(" %c", &choice);
   return choice == 'y';
}

int get_valid_input(const char *prompt, int min, int max) {
    int value;
    while (1) {
        printf("%s (%d - %d): ", prompt, min, max);
        if (scanf("%d", &value) != 1 || value < min || value > max) {
            printf("Neplatný vstup. Skúste znova.\n");
            while (getchar() != '\n');
        } else {
            break;
//            printf("\n");
        }
    }



    return value;
}


int main() {
    do {



        int rows = get_valid_input("Zadajte počet riadkov", 1, 25);
        int columns = get_valid_input("Zadajte počet stĺpcov", 1, 25);
        int max_mines = rows * columns - 1;
        int mines = get_valid_input("Zadajte počet mín", 1, max_mines);

        Game *game = create_game();
        Board *board = create_board(rows, columns, mines);
        game->board = board;
        read_player_name(game);
        play_game(game);
        destroy_game(game);
    } while (play_again());

    exit(EXIT_SUCCESS);
}


