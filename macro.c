#include "macro.h"
#include <termios.h>
#include <unistd.h>
#include <stdio.h>


double Random0to1()
{
    return ((double) rand() / (RAND_MAX));
}

double RandomRangeDouble(double start, double end)
{
    double length = (end - start);
    return Random0to1() * length - length/2;
}

int RandomRangeInt(int start, int end)
{
    int length = (end - start);
    int n = rand() % length;
    
    return n + start;
}

int mygetch() {
  struct termios oldt, newt;
  int ch;
  tcgetattr( STDIN_FILENO, &oldt );
  newt = oldt;
  newt.c_lflag &= ~( ICANON | ECHO );
  tcsetattr( STDIN_FILENO, TCSANOW, &newt );
  ch = getchar();
  tcsetattr( STDIN_FILENO, TCSANOW, &oldt );
  return ch;
}