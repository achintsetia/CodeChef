#include <iostream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int C[100];

int mixture[100][100];
int smoke[100][100];

int giveMinSmoke(int N)
{
  int currVal = 0, j;
  for( int len=2; len<=N; len++)
    for( int i=0; i<=N-len+1; i++)
    {
      j = i+len-1;
      smoke[i][j] = 0x7fffffff;
      for( int k=i; k<j; k++)
      {
        currVal = smoke[i][k] + smoke[k+1][j] + mixture[i][k]*mixture[k+1][j];
        if( currVal < smoke[i][j])
          smoke[i][j] = currVal;
      }
    }
  return smoke[0][N-1];
}

int main( int argc, char** argv)
{
  int N;

  while( scanf("%d", &N) != 0)
  {

    scanf("%d", &mixture[0][0]);
    C[0] = mixture[0][0];
    smoke[0][0] = 0;

    for( int i=1; i<N; i++)
    {
      scanf("%d", &mixture[i][i]);
      C[i] = C[i-1] + mixture[i][i];
      smoke[i][i] = 0;
    }

    for(int i=0; i<N; i++)
      for( int j=i+1; j<N; j++)
        mixture[i][j] = (C[j] - C[i] + mixture[i][i]) % 100;

    printf( "%d\n", giveMinSmoke(N));
  }
  return 0;
}
