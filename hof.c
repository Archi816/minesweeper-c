#include "hof.h"
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <assert.h>


// hall of fame file name
#define HOF_FILENAME_LENGTH 80
static char hof_file[HOF_FILENAME_LENGTH] = "score";

int load_score_to_list(Player list_of_players[]) {

    assert(list_of_players != NULL);
    FILE *file = fopen(hof_file, "r");

    if (file == NULL) {
        return -1;
    }
    int index_of_player = 0;
    while (fscanf(file, "%s %d", list_of_players[index_of_player].name,
                  &list_of_players[index_of_player].score) != EOF
           && index_of_player < PLAYERS_LIMIT) {

        index_of_player++;
    }

    fclose(file);
    return index_of_player;
}

void save_players_to_file(Player list_of_players[], const int size) {
    assert(list_of_players != NULL);
    FILE *file = fopen(hof_file, "w");

    if (file == NULL) { return; }
    for (int i = 0; i < size; i++) {
        if (i < PLAYERS_LIMIT) {
            fprintf(file, "%s %d\n", list_of_players[i].name, list_of_players[i].score);
        }
    }
    fclose(file);
}

bool add_player_to_list(Player list_of_players[], int *size_of_list, const Player player) {
    assert(list_of_players != NULL && size_of_list != NULL);

    if (*size_of_list < PLAYERS_LIMIT) {
        // adds player on the end of the list
        list_of_players[*size_of_list] = player;
        *size_of_list = *size_of_list + 1;
    } else {
        return false;
    }

    return true;
}

void set_hof_file_name(const char name[]) {
    strncpy(hof_file, name, HOF_FILENAME_LENGTH);
}
