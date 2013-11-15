#include <iostream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

#define PI 3.141592653589793238462643383

struct line
{
  double m;
  double c;
  double X;
  double Y;
};

vector<line> lineVec;

int main( int argc, char** argv)
{

  int N;
  double L, R, X, Y, Z;
  double m, c;
  lineVec.reserve( 100000);

  scanf("%d %lf %lf", &N, &L, &R);

  int lineCount = 0;
  double PI2 = PI/2.0;

  for( int i=0; i<N; i++)
  {
    scanf( "%lf %lf %lf", &X, &Y, &Z);

    //Computing Left line
    double angle = (Z*PI) / 180.0;
    line tempLine;
    tempLine.X = X;
    tempLine.Y = Y;
    tempLine.m = tan( PI2 - angle);
    tempLine.c = -(tempLine.m*X) + Y;

    lineVec.push_back( tempLine);

    //Computing Right line
    tempLine.m = tan( PI2 + angle);
    tempLine.c = -(tempLine.m*X) + Y;

    lineVec.push_back( tempLine);

    lineCount += 2;
  }

  double minHeight = (double) RAND_MAX;

  for( int i=0; i<lineCount; i++)
    for( int j=i+1; j<lineCount; j++)
    {
      //Solving for X and Y
      if( fabs( lineVec[i].m - lineVec[j].m) > 0.001)
      {
        X = (lineVec[j].c - lineVec[i].c) / (lineVec[i].m - lineVec[j].m);

        Y = ((lineVec[j].m*lineVec[i].c) - (lineVec[i].m*lineVec[j].c)) / ( lineVec[j].m - lineVec[i].m);

#if 0
        cout << "Lines (1): "<< lineVec[i].m << " " << lineVec[i].c;
        cout << " (2): " << lineVec[j].m << " " << lineVec[j].c << endl;
        cout << " meet at " << X << " " <<  Y << endl;
#endif

        if( X >= L && X <= R && Y > 0 && Y<minHeight)
          minHeight = Y;
      }
      else
      {
        if( lineVec[j].X >= L && lineVec[j].X <= R && lineVec[j].Y < minHeight)
          minHeight = lineVec[j].Y;
      }
    }

    printf( "%.6f\n", minHeight);
  return 0;
}
