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
  scanf("%d", &T);

  while(T--)
  {
    string str;
    cin >> str;

    int len = str.size();

    int histL[26];
    int histR[26];

    for( int i=0; i<26; i++)
    {
      histL[i]=0;
      histR[i]=0;
    }

    for( int i=0; i<len/2; i++)
      histL[str[i]-'a']++;

    for( int i=(len%2==0)?len/2:len/2+1; i<len; i++)
      histR[str[i]-'a']++;

    bool ans = true;
    for( int i=0; i<26; i++)
      if( histL[i] != histR[i])
      {
        ans = false;
        break;
      }

    ans == true ? cout << "YES" << endl : cout << "NO" << endl;
  }
  return 0;
}
