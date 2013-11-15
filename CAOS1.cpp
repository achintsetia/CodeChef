#include <iostream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;


int main( int argc, char** argv)
{
  int T; scanf("%d", &T);

  while(T--)
  {
    int R, C;
    scanf("%d %d", &R, &C);

    char Map[R][C];

    for( int i=0; i<R; i++)
        scanf("%s", Map[i]);

    if( R < 5 || C < 5)
    {
      printf("0\n");
      continue;
    }

    int count = 0;
    for( int i=2; i<R-2; i++)
      for( int j=2; j<C-2; j++)
      {
        if( Map[i][j] != '#' &&
            Map[i-1][j] == '^' && Map[i-2][j] == '^' &&
            Map[i][j-1] == '^' && Map[i][j-2] == '^' &&
            Map[i+1][j] == '^' && Map[i+2][j] == '^' &&
            Map[i][j+1] == '^' && Map[i][j+2] == '^')
        {
          count++;
        }
      }
    printf("%d\n", count);
  }
  return 0;
}
