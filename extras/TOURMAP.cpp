#include <iostream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

string nameFrom;
string nameTo;
string amount;

int main( int argc, char** argv)
{
  int T, N;

  cin >> T;

  while( T--)
  {
    cin >> N;
    for( int i=0; i<N-1; i++)
    {
      cin >> nameFrom >> nameTo >> amount;
      cout << nameFrom << " " << nameTo << " " << amount << endl;
    }

  }
  return 0;
}
