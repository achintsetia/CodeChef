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
  string str;
  cin >> str;

  int len = str.size();
  unsigned int count = 0;

  for( int i=0; i<len; i++)
    if( (int) str[i] - '0'  == 9)
      count++;

  count %= 1000000007;
  cout << count << endl;

  for( int i=0; i<len; i++)
    for( int j=i+1; j<len; j++)
      if( (str[i] != '0' || str[j] != '0') && (int) (str[i] - '0' + str[j] - '0') % 9 == 0)
        count++;
  cout << count << endl;
  count %= 1000000007;

  for( int i=0; i<len; i++)
    for( int j=i+1; j<len; j++)
      for( int k=j+1; k<len; k++)
        if( (str[i] != '0' || str[j] != '0' || str[k] != '0') && (int) (str[i] - '0' + str[j] - '0' + str[k] - '0') % 9 == 0)
        {
          count++;
          count %= 1000000007;
        }
  cout << count << endl;

  for( int i=0; i<len; i++)
    for( int j=i+1; j<len; j++)
      for( int k=j+1; k<len; k++)
        for( int l=k+1; l<len; l++)
          if(  (str[i] != '0' || str[j] != '0' || str[k] != '0' || str[l] != '0') && (int) (str[i] - '0' + str[j] - '0' +
                    str[k] - '0' + str[l] - '0') % 9 == 0)
          {
            count++;
            count %= 1000000007;
          }

  cout << count << endl;
  return 0;
}
