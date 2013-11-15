#include <iostream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

typedef long long int ll;

#define PI 3.141592653589793238462643383

struct tri
{
  double X;
  double Y;
  double l;
  double r;
  double m1;
  double m2;
};


tri triArray[50000];
int addArray[50000];


bool triCompare(int a, int b)
{
  return (triArray[a].r < triArray[b].r);
}

int main( int argc, char** argv)
{

  int N;
  double L, R, X, Y, Z;
  ll m, c;

  scanf("%d %lf %lf", &N, &L, &R);

  int triCount = 0;
  double PI2 = PI/2.0;
  double angle;

  for( int i=0; i<N; i++)
  {
    scanf( "%lf %lf %lf", &X, &Y, &Z);

    addArray[triCount] = triCount;

    //Computing Left line
    double angle = (Z*PI) / 180.0;
    triArray[triCount].X = X;
    triArray[triCount].Y = Y;
    triArray[triCount].m1 = tan( PI2 - angle);
    triArray[triCount].m2 = tan( PI2 + angle);
    triArray[triCount].l = X - Y/triArray[triCount].m1;
    triArray[triCount].r = X - Y/triArray[triCount].m2;

    triCount++;
  }

  sort( addArray, addArray+N, triCompare);

  double minHeight, maxHeight;



    printf( "%.9f\n", minHeight);
  return 0;
}
