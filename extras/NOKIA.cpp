#include <iostream>
#include <algorithm>
#include <string.h>
#include <math.h>

using namespace std;

int evalCost( int array[], int size)
{
  bool posed[size];
  for( int i=0; i<size; i++)
    posed[i] = false;

  int cost = 0;
  for( int i=0; i<size; i++)
  {
    int ind = array[i];
    while(( ind >= 1) && ( posed[ind-1] == false))
      ind--;
    cost += array[i] - ind;

    ind = array[i];
    while(( ind <= size) && ( posed[ind-1] == false))
      ind++;
    cost += ind - array[i];

    posed[array[i]-1] = true;
  }
  return cost;
}

int main( int argc, char** argv)
{
  int T;
  cin >> T;

  for( int i=0; i<T; i++)
  {
    int N, M;
    cin >> N;
    cin >> M;

    int array[N];
    for( int j=0; j<N; j++)
      array[j] = j+1;

    long int fact = 1;
    for( int j=0; j<N; j++)
      fact *= j+1;

    long int count = 0;
    int cost = 0;
    int min = 1000;
    bool outFlag = false;

    do
    {
      cost = evalCost( array, N);

      if( (M - cost) < min)
        min = M - cost;

      if( M - cost == 0)
      {
        cout << 0 << endl;
        outFlag = true;
        break;
      }
      count++;
    }
    while( next_permutation( array, array+N) && (count <= (fact)/2));
    if( !outFlag)
    {
      if( min > 0)
        cout << min << endl;
      else if( min < 0)
        cout << -1 << endl;
    }

  }
  return 0;
}
