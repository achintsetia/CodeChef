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
  string A, B, C;
  int T;

  cin >> T;

  while(T--)
  {
    bool failFlag = false;
    string parents, children;
    int N;
    cin >> A >> B;
    parents = A + B;

    cin >> N;
    while( N--)
    {
      cin >> A;
      children = children + A;
    }


    int histP[26];
    for( int i=0; i<26; i++) histP[i] = 0;

    int histC[26];
    for( int i=0; i<26; i++) histC[i] = 0;

    for( int i=0; i<parents.size(); i++)
      histP[parents[i] - 'a']++;

    for( int i=0; i<children.size(); i++)
      histC[children[i] - 'a']++;

    for( int i=0; i<26; i++)
      if( histC[i] > histP[i])
      {
        cout << "NO" << endl;
        failFlag = true;
        break;
      }

    if( failFlag == false) cout << "YES" << endl;
  }
  return 0;
}
