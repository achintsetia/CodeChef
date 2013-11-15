#include <iostream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

unsigned long long array[100000];
bool bitVec[89441];

int hashFunc( unsigned long long int num)
{
  int sum = 0;
  for(int i=0; i<64; i++)
  {
    if(num & 1)
      sum+= ((i+1)*(i+1));
    num >>= 1;
  }
  return sum;
}

int main( int argc, char** argv)
{
  int N, index;
  bool yesFlag = false;
  bool imFlag = false;
  unsigned long long int num;
  int j=0;

  scanf("%d", &N);

  for(int i=0; i<89441; i++)
    bitVec[i] = false;

  for( int i=0; i<N; i++)
  {
    scanf("%llu", &array[i]);
    if( !yesFlag)
    {
      for( int j=0; j<64; j++)
      {
        if( i > j)
        {
          index = hashFunc( array[i] ^ array[i-j-1]);
          if( bitVec[index] == true)
          {
            if( j ==0)
            {
              if( imFlag == false)
                yesFlag = true;
              else imFlag = false;
            }
            else
              yesFlag = true;
          }
          else
          {
            bitVec[index] = true;
            if( j == 0)
            {
              if( imFlag == true)
                imFlag = false;
              else
                imFlag = true;
            }
          }
        }
      }
    }
  }
  if( yesFlag) cout << "Yes" << endl;
  else cout << "No" << endl;

  return 0;
}
