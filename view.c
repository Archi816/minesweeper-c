#include <assert.h>
#include <string.h>
#include "view.h"
#include "termcolor.h"
#include "sb.h"

Color value_colors[] = {
        COLOR_DEFAULT, COLOR_BOLD_RED, COLOR_GREEN,
        COLOR_BOLD_MAGENTA, COLOR_CYAN, COLOR_MAGENTA,
        COLOR_YELLOW, COLOR_BLUE, COLOR_BOLD_YELLOW
};

void view_column_coordinates(StringBuilder *sb, int column_count);
void view_tile(StringBuilder *sb, Tile *tile, bool is_mine_on_selected_tile);
void view_value(StringBuilder *sb, int value);

/**
 * Returns whole play field
 */
char *view_play_field(Board *board, int input_row, int input_column) {
    assert(board != NULL);
    StringBuilder *sb = sb_create();

    view_column_coordinates(sb, board->column_count);
    int row_enumeration = 1;
    for (int row = 0; row < board->row_count; row++) {
        sb_appendf(sb, "%d  ", row_enumeration);

        for (int column = 0; column < board->column_count; column++) {

            if (row == input_row - 1 && column == input_column - 1) {
                view_tile(sb, board->tiles[row][column], true);
            } else {
                view_tile(sb, board->tiles[row][column], false);
            }
            sb_append(sb, " ");
        }
        row_enumeration++;
        sb_append(sb, "\n");
    }
    return sb_concat_free(sb);
}


/**
 * Enumerates columns beyond play field
 */
void view_column_coordinates(StringBuilder *sb, int column_count) {
    sb_append(sb, "   ");
    for (int e = 1; e <= column_count; e++) {
        sb_appendf(sb, "%d ", e);
    }
    sb_append(sb, "\n");
}


/**
 * Prints one single Tile
 */
void view_tile(StringBuilder *sb, Tile *tile, bool is_mine_on_selected_tile) {
    assert(tile != NULL);

    if (tile->tile_state == OPEN && tile->is_mine) {
        if (is_mine_on_selected_tile) {
            // sets red mine just for mine on the input coordinates
            sb_append(sb, COLOR_RED "X" COLOR_DEFAULT);
        } else {
            sb_append(sb, "X");
        }
    }
    if (tile->tile_state == CLOSED) {
        sb_append(sb, "-");
    } else if (tile->tile_state == OPEN && !tile->is_mine) {
        view_value(sb, tile->value);
    } else if (tile->tile_state == MARKED) {
        sb_append(sb, "!");
    }
}


void view_value(StringBuilder *sb, int value) {
    if (value != 0)
        sb_appendf(sb, "%s%d%s", value_colors[value], value, COLOR_DEFAULT);
    else
        sb_appendf(sb, "%d", value);
}
