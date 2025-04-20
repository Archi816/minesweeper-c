#include <stdlib.h>
#include <stdio.h>
#include "game.h"
#include "ui.h"
#include "board.h"

  bool play_again(){
   char choice;
   printf("Chceli by ste si zahrať znova? (y/n) ");
   scanf(" %c", &choice);
   return choice == 'y';
}


int main() {
    do {
    Game *game = create_game();
    Board *board = create_board(9, 9, 9);
    game->board = board;
    read_player_name(game);
    play_game(game);
    destroy_game(game);
    } while (play_again());
    exit (EXIT_SUCCESS);
}