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
  int T, N, M, min, max;
  int w, x, y, z;

  scanf("%d", &T);

  while(T--)
  {
    scanf("%d %d", &N, &M);
    min = 1;
    max = N;

    while(M--)
    {
      scanf("%d %d %d %d", &w, &x, &y, &z);
      if( w == 1 && z >= 0)
      {
        max = max >= y+z ? max : y+z;
        if( x == 1)
          min = min <= x+z ? min : x+z;
      }
      else if( w == 2 && z < 0)
      {
        max = max >= y-z ? max : y-z;
        if( x == 1)
          min = min <= x-z ? min : x-z;
      }
      else if( w == 2 && z >=0)
      {
        min = min <= x-z ? min : x-z;
        if( y == N)
          max = max >= y-z ? max : y-z;
      }
      else if( w == 1 && z < 0)
      {
        min = min <= x+z ? min : x+z;
        if( y == N)
          max = max >= y-z ? max : y-z;
      }
    }
    cout << max - min << endl;
  }

  return 0;
}
