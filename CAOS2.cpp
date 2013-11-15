#include <iostream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX 501
int primesLess[501];
bool primes[MAX];

void preProcessing()
{
  for( int i=0; i<MAX; i++) primes[i] = true;

  int sqrtN = (int)sqrt(MAX);
  for( int i=2; i<=sqrtN; i++)
    if( primes[i])
    {
      for( int j=i; j*i<MAX; j++)
        primes[i*j] = false;
    }

  int count = 0;
  primesLess[0] = 0;
  primesLess[1] = 0;
  for(int i=2; i<MAX; i++)
  {
    if( primes[i]) count++;
    primesLess[i] = count;
  }
}


int main( int argc, char** argv)
{
  preProcessing();
  int T; scanf("%d", &T);

  while(T--)
  {
    int R, C;
    scanf("%d %d", &R, &C);

    char Map[R][C];

    for( int i=0; i<R; i++)
        scanf("%s", Map[i]);

    if( R < 5 || C < 5)
    {
      printf("0\n");
      continue;
    }

    int Left[R][C];
    int Right[R][C];
    int Top[R][C];
    int Bottom[R][C];

    //Left
    for( int i=0; i<R; i++)
    {
      Left[i][0] = 0;
      for(int j=1; j<C; j++)
      {
        if( Map[i][j-1] == '^') Left[i][j] = Left[i][j-1]+1;
        else Left[i][j] = 0;
      }
    }

    //Right
    for( int i=0; i<R; i++)
    {
      Right[i][C-1] = 0;
      for(int j=C-2; j>=0; j--)
      {
        if( Map[i][j+1] == '^') Right[i][j] = Right[i][j+1]+1;
        else Right[i][j] = 0;
      }
    }

    //Top
    for( int j=0; j<C; j++)
    {
      Top[0][j] = 0;
      for( int i=1; i<R; i++)
      {
        if(Map[i-1][j] == '^') Top[i][j] = Top[i-1][j] + 1;
        else Top[i][j] = 0;
      }
    }

    //Bottom
    for( int j=0; j<C; j++)
    {
      Bottom[R-1][j] = 0;
      for( int i=R-2; i>=0; i--)
      {
        if(Map[i+1][j] == '^') Bottom[i][j] = Bottom[i+1][j]+1;
        else Bottom[i][j] = 0;
      }
    }
    #if 0
    cout << "Left: " << endl;
    for(int i=0; i<R; i++)
    {
      for(int j=0; j<C; j++)
        cout << Left[i][j] << " ";
      cout << endl;
    }

    cout << "Right: " << endl;
    for(int i=0; i<R; i++)
    {
      for(int j=0; j<C; j++)
        cout << Right[i][j] << " ";
      cout << endl;
    }

    cout << "Top: " << endl;
    for(int i=0; i<R; i++)
    {
      for(int j=0; j<C; j++)
        cout << Top[i][j] << " ";
      cout << endl;
    }

    cout << "Bpttom: " << endl;
    for(int i=0; i<R; i++)
    {
      for(int j=0; j<C; j++)
        cout << Bottom[i][j] << " ";
      cout << endl;
    }
    #endif


    int count = 0;
    for(int i=2; i<R-2; i++)
      for(int j=2; j<C-2; j++)
      {
        if( Map[i][j] != '#')
        {
          int num = min(min(min(Left[i][j], Right[i][j]), Top[i][j]), Bottom[i][j]);
          count += primesLess[num];
        }
      }

    printf("%d\n", count);
  }
  return 0;
}
