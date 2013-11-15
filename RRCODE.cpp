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
  int T; cin >> T;

  while(T--)
  {
    int N, K;
    unsigned int Ans;
    cin >> N >> K >> Ans;

    unsigned int Arr[N];
    for( int i=0; i<N; i++) cin >> Arr[i];

    string op; cin >> op;

    if( K == 0)
    {
      cout << Ans << endl;
      continue;
    }

    if( op[0] == 'X')
    {
      if( K%2 == 1)
      {
        for( int i=0; i<N; i++) Ans ^= Arr[i];
      }
    }
    else if( op[0] == 'A')
    {
      for( int i=0; i<N; i++) Ans &= Arr[i];
    }
    else if( op[0] == 'O')
    {
      for( int i=0; i<N; i++) Ans |= Arr[i];
    }
    else
    {
      exit(1);
    }

    cout << Ans << endl;
  }
  return 0;
}
