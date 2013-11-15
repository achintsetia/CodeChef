#include <iostream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

bool checkSubstr( string s1, string s2)
{
  //S1 is smaller than S2
  for( int i=0, j=0; i<s1.size(); i++)
  {
    while( s1[i] != s2[j] && j<s2.size()) j++;

    if( s1[i] == s2[j]) j++;
    else return false;
  }
  return true;
}

int main( int argc, char** argv)
{
  string s1, s2;

  int T;

  cin >> T;

  while(T--)
  {
    cin >> s1 >> s2;
    if( s1.size() < s2.size() && checkSubstr(s1, s2))
    {
      cout << "YES" << endl; continue;
    }
    else if( s2.size() < s1.size() && checkSubstr(s2, s1))
    {
      cout << "YES" << endl; continue;
    }
    else if( !strcmp(s1.c_str(), s2.c_str()))
    {
      cout << "YES" << endl; continue;
    }
    cout << "NO" << endl;
  }
  return 0;
}
