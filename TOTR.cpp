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
  string permArrS, permArrC;

  cin >> T >> permArrS; permArrC = permArrS;

  for( int i=0; i<26; i++)
    permArrC[i] = permArrC[i] - 32;

  string sentence;

  while( T--)
  {
    cin >> sentence;

    for( int i=0; i<sentence.size(); i++)
    {
      if( sentence[i] == '_') sentence[i] = ' ';
      else if( sentence[i] >= 65 && sentence[i] <= 90)
        sentence[i] = permArrC[ sentence[i] - 65];
      else if( sentence[i] >= 97 && sentence[i] <= 122)
        sentence[i] = permArrS[ sentence[i] - 97];
    }
    cout << sentence << endl;
  }
  return 0;
}
