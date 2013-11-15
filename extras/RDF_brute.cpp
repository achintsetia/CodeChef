#include <iostream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX 50000

long double arr[MAX][100];

long double compute(int N, int K)
{
  if( K>= N) return 0;

  if( K == 0) return (double) N;

  if( arr[N][K] >= 0)
    return arr[N][K];

  long double sum = 0;

  for( int i=N-1; i>=1; i--)
    sum += compute( i, K-1);

   arr[N][K] = sum / (double) N;
   return arr[N][K];
}


int main( int argc, char** argv)
{
  int N, K;

  for( int i=0; i<MAX; i++)
    for( int j=0; j<100; j++)
      arr[i][j] = -1.0;

  scanf("%d %d", &N, &K);

  printf("%0.7Lf\n", compute(N, K));
  return 0;
}
