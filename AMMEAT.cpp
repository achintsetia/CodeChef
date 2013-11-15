#include <iostream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

typedef unsigned long long ull;


int minBits( int i)
{
  int sumBits = 0;
  for( int j=0; j<7; j++)
    if( (i>>j) & 1 == 1)
      sumBits++;
  return sumBits;
}

int minPlates( unsigned long long P[], int N, unsigned long long M)
{
  int minAns = 100;

  int lim = 1;
  for( int i=0; i<N; i++)
    lim = lim*2;

    for( int i=1; i<lim; i++)
    {
      ull sum = 0;
      for( int j=0; j<N; j++)
        if( (i >> j) & 1 == 1)
          sum = sum+P[j];

      if( sum >= M && minBits(i) < minAns)
        minAns = minBits(i);
    }
    if( minAns == 100)
      return -1;
    else
      return minAns;
}

int main( int argc, char** argv)
{
  int T;
  scanf("%d", &T);

  while(T--)
  {
    int N;
    scanf("%d", &N);
    ull M;
    scanf("%llu", &M);

    ull P[N];

    for( int i=0; i<N; i++)
      scanf("%llu", &P[i]);

    printf( "%d\n", minPlates( P, N, M));
  }
  return 0;
}
