#include "hof.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>


int compare_scores(const void *a, const void *b) {
    const Player *player_a = (const Player *)a;
    const Player *player_b = (const Player *)b;
    return (player_b->score - player_a->score);
}


/**
 * Load hall of fame from the file
 * @return the number of loaded entries or 0, if there was error in loading
 */
int read_scores(char *filename, Player *list_of_players) {
    assert(filename != NULL);
    assert(list_of_players != NULL);
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        //printf("Error opening file: %s\n", filename);
        return 0;
    }
    int index_of_player = 0;
    while (fscanf(file, "%s %d", list_of_players[index_of_player].name,
                  &list_of_players[index_of_player].score) != EOF
           && index_of_player < PLAYERS_LIMIT) {
        //printf("Read player: %s %d\n", list_of_players[index_of_player].name, list_of_players[index_of_player].score);
        index_of_player++;
    }

    fclose(file);

    //printf("Total players read: %d\n", index_of_player);

    qsort(list_of_players, index_of_player, sizeof(Player), compare_scores);
    return index_of_player;
}




/**
 * Save the hall of fame array to the file
 */
void save_scores(char *filename, Player *list_of_players, const int size) {
    assert(filename != NULL);
    assert(list_of_players != NULL);
    FILE *file = fopen(filename, "w");

    if (file == NULL) { return; }
    for (int i = 0; i < size; i++) {
        if (i < PLAYERS_LIMIT) {
            fprintf(file, "%s %d\n", list_of_players[i].name, list_of_players[i].score);
        }
    }
    fclose(file);
}




/**
 * Add Player to the hall of fame array
 * @return true, if Player (entry) was added to the list, false otherwise
 */
bool add_player_to_list(Player list_of_players[], int *size_of_list, const Player player) {
    assert(list_of_players != NULL && size_of_list != NULL);

    if (*size_of_list <= PLAYERS_LIMIT) {
        bool is_player_added = false;
        int insert_index = -1;
        if (*size_of_list == 0) {
            list_of_players[0] = player;
            (*size_of_list)++;
            return true;
        }
    

        for (int i = 0; i < *size_of_list; i++) {
            if (player.score >= list_of_players[i].score) {
                insert_index = i;
                if (player.score == list_of_players[i].score) {
                    list_of_players[i] = player;
                    is_player_added = true;
                    break;
                }
            }
        }





        if (insert_index != -1 && !is_player_added) {
            for (int j = *size_of_list; j > insert_index; j--) {
                list_of_players[j] = list_of_players[j - 1];
            }
            list_of_players[insert_index] = player;
            (*size_of_list)++;
            is_player_added = true;
        } else if (*size_of_list < PLAYERS_LIMIT && !is_player_added) {
            list_of_players[*size_of_list] = player;
            (*size_of_list)++;
            is_player_added = true;
        }

        qsort(list_of_players, *size_of_list, sizeof(Player), compare_scores);
        return is_player_added;
    } 

    return false;
}
