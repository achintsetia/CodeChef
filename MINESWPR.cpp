#include <iostream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <stack>

using namespace std;

char Survey(int x, int y) {
  printf("S %d %d\n", x, y);
  fflush(stdout);
  char res;
  scanf(" %c", &res);
  return res;
}

void Neutralize(int x, int y) {
  printf("N %d %d\n", x, y);
  fflush(stdout); /* but it is not necessary here */
}

void genRandSeq( int arr[], int N)
{

  for( int i=0; i<N; i++)
    arr[i] = i;
/*
  bool taken[N];
  int count = 0;

  for( int i=0; i<N; i++)
    taken[i]= false;

  for( int i=1; i<N; i+=3)
  {
    arr[count++] = i;
    taken[i]=true;
  }

  for( int i=count, j=0; i<N, j<N; j++)
    if( taken[j] == false)
    {
      taken[j] = true;
      arr[i++] = j;;
    }

  for( int i=count; i<N; i++)
  {
    int num = count + (rand() % (N-count));
    swap( arr[i], arr[num]);
  }
  */
}

int countUnvisited( int check[], int i, int j, int N, vector< pair<int, int> > &sublist)
{
  int num = 0;
  for( int l=-1; l<2; l++)
    for( int m=-1; m<2; m++)
      if( (i+l) < N-1 && (i+l) > 0 && (j+m) < N-1 && (j+m) > 0 && check[(i+l)*N + j+m] == 0)
        num++;
  return num;
}

void markAllNeighbourVisited( int check[], int i, int j, int N)
{
  check[i*N+j] = 1;
  for( int l=-1; l<2; l++)
    for( int m=-1; m<2; m++)
    {
      if( (i+l) < N-1 && (i+l) > 0 && (j+m) < N-1 && (j+m) > 0)
        check[(i+l)*N + j+m] = 1;
    }
}
struct cmp
{
  bool operator()(pair<int, int> a, pair<int, int> b)
  {
    int A=0, B=0;
    if( a.first > 0 && ((a.first-1)% 3 == 0)) A++;
    if( a.second > 0 && ((a.second-1)% 3 == 0)) A++;

    if( b.first > 0 && ((b.first-1)% 3 == 0)) B++;
    if( b.second > 0 && ((b.second-1)% 3 == 0)) B++;

    return A > B;
  }
};

int main( int argc, char** argv)
{
  int N, M, K;
  scanf("%d %d %d", &N, &M, &K);

  int check[N*N];
  for( int i=0; i<N; i++)
    for( int j=0; j<N; j++)
      check[i*N+j] = 0;


  vector< pair<int, int> > mines;

  int xArr[N], yArr[N];

  genRandSeq( xArr, N);
  genRandSeq( yArr, N);

  int mineCount = 0;

  vector< pair<int, int> > points;

  for( int i=0; i<N; i++)
    for( int j=0; j<N; j++)
      points.push_back(make_pair(i,j));

  //sort(points.begin(), points.end(), cmp());

  for( int p=0; p<points.size(); p++)
  {
    int i=points[p].first;
    int j=points[p].second;

    if( check[xArr[i]*N + yArr[j]] == 1)
      continue;

    if( mineCount == M)
      break;

    char q = Survey( xArr[i], yArr[j]);
    if( q == '0')
      markAllNeighbourVisited( check, xArr[i], yArr[j], N);
    else if( q >= '1' && q <='8')
    {
      check[xArr[i]*N + yArr[j]] = 1;
      vector< pair<int, int> > sublist;
      if( (int) (q - 48) == countUnvisited( check, xArr[i], yArr[j], N, sublist))
      {
        for( int k=0; k<sublist.size(); k++)
        {
          //mines.push_back( sublist[k]);
          Neutralize( xArr[i], yArr[j]);
          mineCount++;
        }
      }
      sublist.clear();
    }
    else if( q == 'M' && mineCount < M)
    {
      check[xArr[i]*N+yArr[j]] = 1;
      Neutralize( xArr[i], yArr[j]);
      //mines.push_back( make_pair(xArr[i], yArr[j]));
      mineCount++;
    }
  }

  printf("Done\n");
  fflush(stdout);
  return 0;
}
