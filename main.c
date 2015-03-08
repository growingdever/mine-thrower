#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "lib/c_printf/c_printf.h"
#include "macro.h"

#define MAP_WIDTH 20
#define MAP_HEIGHT 20
#define NUM_OF_TOTAL_MINE 30


enum {
	Mine = -1,
} MAP_SYMBOL;

int ground[MAP_HEIGHT][MAP_WIDTH];
int flipped[MAP_HEIGHT][MAP_WIDTH];
int current_cursor_x = 0;
int current_cursor_y = 0;


int counting_border(int x, int y) {
	int count = 0;
	for( int i = y - 1; i <= y + 1; i ++ ) {
		if( i < 0 || i >= MAP_HEIGHT ) {
			continue;
		}
		for( int j = x - 1; j <= x + 1; j ++ ) {
			if( i == y && j == x ) {
				continue;
			}

			if( j < 0 || j >= MAP_WIDTH ) {
				continue;
			}

			if( ground[i][j] == Mine ) {
				count++;
			}
		}
	}

	return count;
}

void generate_map() {
	srand((unsigned)time(NULL));

	// initialize
	for( int i = 0; i < MAP_HEIGHT; i ++ ) {
		for( int j = 0; j < MAP_WIDTH; j ++ ) {
			ground[i][j] = 0;
			flipped[i][j] = 0;
		}
	}

	// create mine
	for( int i = 0; i < NUM_OF_TOTAL_MINE; i ++ ) {
		int x, y;
		do {
			x = RandomRangeInt(0, MAP_WIDTH);
			y = RandomRangeInt(0, MAP_HEIGHT);
		} while(ground[y][x] != 0);

		ground[y][x] = Mine;
	}

	// counting
	for( int i = 0; i < MAP_HEIGHT; i ++ ) {
		for( int j = 0; j < MAP_WIDTH; j ++ ) {
			if( ground[i][j] == Mine ) {
				continue;
			}

			ground[i][j] = counting_border(j, i);
		}
	}
}

void print_ground() {
	// border
	for( int i = 0; i <= (MAP_WIDTH) * 3 + 1; i ++ ) {
		if( i == 0 || i == (MAP_WIDTH) * 3 + 1 ) {
			c_printf("[g]%s", "+");
		} else {
			c_printf("[g]%s", "-");
		}
	}
	printf("\n");

	for( int i = 0; i < MAP_HEIGHT; i ++ ) {
		// border
		c_printf("[g]%s", "|");
		for( int j = 0; j < MAP_WIDTH; j ++ ) {
			char str[32], str2[32];
			if( ! flipped[i][j] ) {
				if( i == current_cursor_y && j == current_cursor_x ) {
					c_printf("[y]%s", "<");
					strcpy(str, "-");
				} else {
					strcpy(str, " - ");
				}
				
				c_printf("[n]%s", str);

				if( i == current_cursor_y && j == current_cursor_x ) {
					c_printf("[y]%s", ">");
				}
				continue;
			}

			strcpy(str, "");
			if( i == current_cursor_y && j == current_cursor_x ) {
				c_printf("[y]%s", "<");
				strcpy(str, "%c");
			} else {
				strcpy(str, " %c ");
			}

			if( ground[i][j] == Mine ) {
				sprintf(str2, str, '*');
				c_printf("[r]%s", str2);
			} else if( ground[i][j] > 0 ) {
				sprintf(str2, str, ground[i][j] + '0');
				c_printf("[b]%s", str2);
			} else {
				sprintf(str2, str, ' ');
				c_printf("[n]%s", str2);
			}

			if( i == current_cursor_y && j == current_cursor_x ) {
				c_printf("[y]%s", ">");
			}
		}
		// border
		c_printf("[g]%s\n", "|");
	}

	// border
	for( int i = 0; i <= (MAP_WIDTH) * 3 + 1; i ++ ) {
		if( i == 0 || i == (MAP_WIDTH) * 3 + 1 ) {
			c_printf("[g]%s", "+");
		} else {
			c_printf("[g]%s", "-");
		}
	}
}

void flip_current_cursor() {
	flipped[current_cursor_y][current_cursor_x] = 1;
}

void process_moving_cursor(char c) {
	switch(c) {
	// up
	case 'i':
		current_cursor_y -= 1;
		break;
	// down
	case 'j':
		current_cursor_y += 1;
		break;
	// left
	case 'h':
		current_cursor_x -= 1;
		break;
	// right
	case 'k':
		current_cursor_x += 1;
		break;
	}

	// bound
	if( current_cursor_x < 0 ) {
		current_cursor_x = 0;
	} else if( current_cursor_x >= MAP_WIDTH ) {
		current_cursor_x = MAP_WIDTH - 1;
	}
	if( current_cursor_y < 0 ) {
		current_cursor_y = 0;
	} else if( current_cursor_y >= MAP_HEIGHT ) {
		current_cursor_y = MAP_HEIGHT - 1;
	}
}

void process_command() {
	char c = mygetch();
	if( c == '\n' || c == '\r' ) {
		return;
	}

	// lower case
	if( c >= 'A' && c <= 'Z' ) {
		c += 'a' - 'A';
	}

	if( c == 'i' || c == 'j' || c == 'h' || c == 'k' ) {
		process_moving_cursor(c);
	}

	if( c == ' ' ) {
		flip_current_cursor();
	}
}

int main(int argc, char const *argv[])
{
	generate_map();
	while(1) {
		system("clear");
		print_ground();
		process_command();
	}

	return 0;
}