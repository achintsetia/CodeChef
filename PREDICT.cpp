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
  int T;
  scanf("%d", &T);

  while(T--)
  {
    long double P;
    scanf("%Lf", &P);

    long double C = 10000.0*(1 + 2.0*P*(1.0-P) - P);

    long double A = C + (2.0*P-1.0)*10000;
    if(A > C) printf( "%Lf\n", A);
    else printf( "%Lf\n", C);
  }
  return 0;
}
