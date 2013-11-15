#include <iostream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int fib( int num)
{
  if( num == 0 || num == 1)
    return 1;
  else
    return fib( num-1) + fib( num-2);
}

int numWays( int N)
{
  int sum = 0;
  int right = N-1;
  while( right >= 1)
  {
    sum += fib(N - right) * fib( right+3);
    right--;
  }
  return sum;
}

int main( int argc, char** argv)
{
  int N;

  for( int i=4; i<21; i++)
  {
    cout << "For " << i << ": ";
    cout << numWays(i) << " " << "Diff: " << numWays( i) - numWays( i-1) - numWays( i-2)<< endl;
  }


  return 0;
}
