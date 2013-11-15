#include <iostream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int dArray[2000];

double expSum;

void plotTree( int start, int end, int level)
{
  if( start < end)
  {
    if( level%2 == 0)
    {
      expSum += dArray[start] / pow(2.0, level+1);
      expSum += dArray[end-1] / pow(2.0, level+1);
    }
    plotTree( start+1, end, level+1);
    plotTree( start, end-1, level+1);
  }
}

int main( int argc, char** argv)
{

  int T, N;

  scanf( "%d", &T);

  while( T--)
  {
    scanf( "%d", &N);

    for( int i=0; i<N; i++)
      scanf("%d", &dArray[i]);

    if( N == 1)
    {
      printf("%.5f\n", (double)dArray[0]);
      continue;
    }

    expSum = 0;

    plotTree( 0, N, 0);
    printf( "%.2f\n", expSum);
  }
  return 0;
}
