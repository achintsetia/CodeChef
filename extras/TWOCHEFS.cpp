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
  int N1, N2;
  scanf("%d %d", &N1, &N2);

  int arr1[N1], arr2[N2], sumArr1[N1], sumArr2[N2];
  int sum1=0, sum2=0;

  for( int i=0; i<N1; i++)
  {
    scanf("%d", &arr1[i]);
    if( i>0)
      sumArr1[i] = sumArr1[i-1] + arr1[i];
    else
      sumArr1[i] = arr1[i];
  }

  for( int i=0; i<N2; i++)
  {
    scanf("%d", &arr2[i]);
    sum2 += arr2[i];
    if( i>0)
      sumArr2[i] = sumArr2[i-1] + arr2[i];
    else
      sumArr2[i] = arr2[i];
  }

  return 0;
}
