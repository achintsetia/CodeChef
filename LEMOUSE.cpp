#include <iostream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int arr[101][101];
pair<int, int> C[101][101];

#define TOP 1
#define LEFT 2

int numScaredMouse( int N, int M)
{
  int A = arr[0][0] + arr[1][0] + arr[0][1];
  C[0][0] = make_pair(A,A);


  for( int i=1; i<N; i++)
  {
    int ans = (i+1<=N-1)?arr[i+1][0]:0;
    ans += arr[i][1];
    C[i][0] = make_pair(C[i-1][0].first + ans, C[i-1][0].second + ans);
  }
  for( int j=1; j<M; j++)
  {
    int ans = (j+1<=M-1)?arr[0][j+1]:0;
    ans += arr[1][j];
    C[0][j] = make_pair(C[0][j-1].first + ans, C[0][j-1].second + ans);
  }

  for( int i=1; i<N; i++)
    for( int j=1; j<M; j++)
    {
      int ans = (i+1<=N-1)?arr[i+1][j]:0;
      ans += (j+1<=M-1)?arr[i][j+1]:0;

      int T1 = C[i-1][j].first, T2=C[i-1][j].second;
      int L1 = C[i][j-1].first, L2=C[i][j-1].second;
      T1 += arr[i][j-1];
      L2 += arr[i-1][j];

      C[i][j]  = make_pair(ans + min(T1,T2), ans + min(L1,L2));
    }
  return min(C[N-1][M-1].first, C[N-1][M-1].second);
}

int main( int argc, char** argv)
{
  int T,N,M;
  scanf("%d", &T);

  while(T--)
  {
    scanf("%d %d", &N, &M);

    for( int i=0; i<N; i++)
    {
      string str;
      cin >> str;
      for( int j=0; j<M; j++)
        arr[i][j] = (int) (str[j] - '0');
    }

    printf( "%d\n", numScaredMouse( N, M));
#if 1
    for( int i=0; i<N; i++)
    {
      for( int j=0; j<M; j++)
        cout << C[i][j].first << "(" << C[i][j].second <<") ";
      cout << endl;
    }
#endif
  }
  return 0;
}
