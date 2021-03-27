#include "greatest.h"
#include "../user_interface.h"

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
    RUN_TEST(remove_spaces_from_name_without_spaces);
    RUN_TEST(remove_spaces_from_name_with_spaces);
}