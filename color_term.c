#include <stdio.h>
#include "color_term.h"

void set_terminal_color(Color color) {
    printf("\033[%sm", color);
}