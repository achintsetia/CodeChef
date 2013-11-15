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
  while( T--)
  {
    string str;
    cin >> str;
    int numInst = 1;
    int start = str[0] - 'a';

    for( int i=1; i<str.size(); i++)
    {
      if( str[i] - 'a' - start  < 0)
        numInst += 26 + str[i] - 'a' - start;
      else
        numInst += str[i] - 'a' - start;
      start = str[i] - 'a';
    }
    if( numInst > 10*str.size())
      cout << "NO" << endl;
    else
      cout << "YES" << endl;
  }
  return 0;
}
