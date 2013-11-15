#include <iostream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

#define mod 1000000007

typedef unsigned long long llu;

llu prod( llu a1, llu a2, llu a3)
{
  llu p = a1 % mod;
  p *= a2 % mod; p %= mod;
  p *= a3 % mod; p %= mod;
  return p;
}

int main( int argc, char** argv)
{
  int T;
  scanf("%d", &T);
  llu N[3];

  while(T--)
  {
    scanf( "%llu %llu %llu", &N[0], &N[1], &N[2]);

    sort( N, N+3);

    llu x = N[0];
    llu y = N[1] - N[0];
    llu z = N[2] - N[1];

    llu sum = 0;

    sum += prod( x, x-1, x-2); sum %= mod;
    sum += prod( x, x-1, y); sum %= mod;
    sum += prod( x, x-1, z); sum %= mod;
    sum += prod( x, y, x-1); sum %= mod;
    sum += prod( x, y, y-1); sum %= mod;
    sum += prod( x, y, z); sum %= mod;

    printf( "%llu\n", sum);
  }
  return 0;
}
