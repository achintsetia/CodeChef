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
  int T, N;
  cin >> T;

  for( int i=0; i<T; i++)
  {
    cin >> N;
    int count = N;
    string strArr;
    cin >> strArr;
    bool array[N];


    for( int j=0; j<N; j++)
      array[j] = false;

    for( int j=0; j<N; j++)
    {
      if( strArr[j] == '1')
      {
        if(( j > 0) && (j < N-1))
        {
          array[j+1] = true;
          array[j-1] = true;
          array[j] = true;
        }
        else if( j == 0)
        {
          array[j+1] = true;
          array[j] = true;
        }
        else
        {
          array[j-1] = true;
          array[j] = true;
        }
      }
    }

    for( int j=0; j<N; j++)
      if( array[j])
        count--;
    cout << count << endl;
  }

  return 0;
}
