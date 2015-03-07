#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "lib/c_printf/c_printf.h"
#include "macro.h"

#define MAP_WIDTH 20
#define MAP_HEIGHT 20
#define NUM_OF_TOTAL_MINE 10

int ground[MAP_HEIGHT][MAP_WIDTH];

void generate_map() {
	srand((unsigned)time(NULL));
	for( int i = 0; i < MAP_HEIGHT; i ++ ) {
		for( int j = 0; j < MAP_WIDTH; j ++ ) {
			ground[i][j] = 0;
		}
	}
	for( int i = 0; i < NUM_OF_TOTAL_MINE; i ++ ) {
		int x, y;
		do {
			x = RandomRangeInt(0, MAP_WIDTH);
			y = RandomRangeInt(0, MAP_HEIGHT);
		} while(ground[y][x] != 0);

		ground[y][x] = -1;
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