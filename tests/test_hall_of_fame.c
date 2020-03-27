#include "greatest.h"
#include "../hall_of_fame.h"

TEST load_file_number_of_players() {
    set_hof_file_name("tests/score/optimal_size");
    Player list_of_players[PLAYERS_LIMIT];

    ASSERT_EQ(5, load_score_to_list(list_of_players));
    PASS();
}

TEST load_file_over_limit() {
    set_hof_file_name("tests/score/over_size");
    int high_size_of_list = PLAYERS_LIMIT + 5;
    Player list_of_players[high_size_of_list];

    ASSERT_EQ(PLAYERS_LIMIT, load_score_to_list(list_of_players));
    PASS();
}

TEST load_nonexistent_file() {
    set_hof_file_name("tests/score/nonexistent");
    Player list_of_players[PLAYERS_LIMIT];
    ASSERT_EQ(-1, load_score_to_list(list_of_players));
    PASS();
}

TEST compare_loaded_and_saved_players() {
    Player list_of_players[PLAYERS_LIMIT] = {
            {"peter", 99},
            {"jozo",  55},
            {"alena", 43},
    };
    int size_of_input_list = 3;
    set_hof_file_name("tests/score/for_saving");

    save_players_to_file(list_of_players, size_of_input_list);
    Player test_list_of_players[size_of_input_list];
    int size_of_test_list =
            load_score_to_list(test_list_of_players);

            ASSERT_EQ(size_of_input_list, size_of_test_list);
    for (int i = 0; i < size_of_test_list; i++) {
        ASSERT_EQ(list_of_players[i].score, test_list_of_players[i].score);
        ASSERT_STR_EQ(list_of_players[i].name, test_list_of_players[i].name);
    }
    PASS();
    remove("tests/score/for_saving");
}

TEST save_player_to_list_invalid() {
    Player list_of_players[11] = {
            {"peter", 99},
            {"jozo",  55},
            {"alena", 43},
            {"roman", 32},
            {"lubo",  21},
            {"milan", 20},
            {"alex",  18},
            {"dano",  9},
            {"kiko",  4},
            {"lubo",  2}
    };
    int size = PLAYERS_LIMIT + 1;
    set_hof_file_name("tests/score/for_saving");
    Player *player = (Player *) calloc(1, sizeof(Player));
    strcpy(player->name, "lucia");
    player->score = 26;

    ASSERT_FALSE(add_player_to_list(list_of_players, &size, *player));
    free(player);
    remove("tests/score/for_saving");
    PASS();
}

TEST add_player_to_optimal_list() {
    Player list_of_players[PLAYERS_LIMIT] = {
            {"peter", 99},
            {"alex",  18},
            {"lubo",  2}
    };
    int size = 3;
    Player *player = (Player *) calloc(1, sizeof(Player));
    strcpy(player->name, "lucia");
    player->score = 26;

    int size_before_adding = size;
    add_player_to_list(list_of_players, &size, *player);
    ASSERT_EQ(size_before_adding + 1, size);
    free(player);
    remove("tests/score/for_saving");
    PASS();
}

SUITE (test_hall_of_fame) {
    RUN_TEST(load_file_number_of_players);
    RUN_TEST(load_file_over_limit);
    RUN_TEST(compare_loaded_and_saved_players);
    RUN_TEST(save_player_to_list_invalid);
    RUN_TEST(add_player_to_optimal_list);
}
