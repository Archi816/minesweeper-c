#include "greatest.h"
#include "../user_interface.h"
#include "../color_term.h"

TEST set_default_color_value() {
    Color color = color_for_value(0);
    ASSERT_STR_EQ(color, COLOR_DEFAULT);
    PASS();
}

TEST set_mine_color_value() {
    Color color = color_for_value(-1);
    ASSERT_STR_EQ(color, COLOR_RED);
    PASS();
}

TEST remove_spaces_from_name_without_spaces() {
    char name_to_change[MAX_PLAYER_LENGTH] = "peto";
    const char name[MAX_PLAYER_LENGTH] = "peto";
    remove_spaces_from_name(name_to_change);
    ASSERT_STR_EQ(name, name_to_change);
    PASS();
}

TEST remove_spaces_from_name_with_spaces() {
    char name_to_change[MAX_PLAYER_LENGTH] = "peto z \nruzinova\n\n";
    const char name[MAX_PLAYER_LENGTH] = "petozruzinova";
    remove_spaces_from_name(name_to_change);
    ASSERT_STR_EQ(name, name_to_change);
    PASS();
}

SUITE (test_user_interface) {
    RUN_TEST(set_default_color_value);
    RUN_TEST(set_mine_color_value);
    RUN_TEST(remove_spaces_from_name_without_spaces);
    RUN_TEST(remove_spaces_from_name_with_spaces);
}