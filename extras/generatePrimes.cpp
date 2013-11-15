#include <iostream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX 1000000

bool primes[MAX] = {true};

void gen_primes()
{
  int i,j;
  //for(i=0;i<MAX;i++) primes[i] = 1;
  for(i=2;i<=(int)sqrt(MAX);i++)
    if (primes[i])
      for(j=i;j*i<MAX;j++) primes[i*j] = 0;
}

int main( int argc, char** argv)
{
  gen_primes();
  return 0;
}
