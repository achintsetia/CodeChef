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

  cin >> T;

  int hist[123];

  string s;

  while( T--)
  {
    for( int i=0; i<123; i++)
      hist[i] = 0;

    cin >> s;

    for( int i=0; i<s.size(); i++)
      hist[(int)s[i]]++;

    int sum = 0;
    for( int i=0; i<123; i++)
        sum += (hist[i] +1 )/ 2;

    cout << sum << endl;
  }
  return 0;
}
