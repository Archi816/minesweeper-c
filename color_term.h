#ifndef _COLOR_TERM_H
#define _COLOR_TERM_H

#include <stdio.h>

typedef char * Color;

#define COLOR_RED "0;31"
#define COLOR_BOLD_RED  "1;31"
#define COLOR_GREEN "0;32"
#define COLOR_BOLD_MAGENTA "1;35"
#define COLOR_CYAN "0;36"
#define COLOR_MAGENTA "0;35"
#define COLOR_YELLOW "0;33"
#define COLOR_BLUE "0;34"
#define COLOR_BOLD_YELLOW "1;33"
#define COLOR_DEFAULT "0"

/**
 * Sets standard output color using one of the COLOR_* constants defined here
 */
void set_terminal_color(Color color);

#endif