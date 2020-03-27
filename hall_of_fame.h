#ifndef _HOF_H
#define _HOF_H

#include <stdbool.h>

//limit of score file
#define PLAYERS_LIMIT 10

//limit of Player length
#define MAX_PLAYER_LENGTH 30

typedef struct {
    char name[MAX_PLAYER_LENGTH];       /* name of Player */
    int score;                          /* value of score */
} Player;


/**
 * Loads hall of fame from file
 * @return the number of loaded entries or -1, if there was error in loading
 */
int load_score_to_list(Player list_of_players[]);


/**
 * Saves the hall of fame list to the file
 */
void save_players_to_file(Player list_of_players[], const int size_of_list);


/**
 * Adds Player to the hall of fame list
 * @return true, if Player (entry) was added to the list, false otherwise
 */
bool add_player_to_list(Player list_of_players[], int *size_of_list, const Player player);


/**
 * Renames name of hof_file static variable
 */
void set_hof_file_name(const char name[]);

#endif
