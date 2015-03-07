#include <stdio.h>
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


int counting_border(int x, y) {
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

	for( int i = 0; i < MAP_HEIGHT; i ++ ) {
		for( int j = 0; j < MAP_WIDTH; j ++ ) {
			printf("%3d",  ground[i][j]);
		}
		printf("\n");
	}
}

int main(int argc, char const *argv[])
{
	// c_printf(" * [r]%s\n", "Red");
	// c_printf(" * [g]%s\n", "Green");
	// c_printf(" * [y]%s\n", "Yellow");
	// c_printf(" * [b]%s\n", "Blue");
	// c_printf(" * [m]%s\n", "Magenta");
	// c_printf(" * [c]%s\n", "Cyan");
	// c_printf(" * [n]%s\n", "Normal");

	generate_map();


	return 0;
}