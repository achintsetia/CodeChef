#include <iostream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <vector>

using namespace std;

int main( int argc, char** argv)
{
  int N, num, command;
  vector<int> numArray;
  scanf("%d", &N);

  while(N--)
  {
    int numSize = numArray.size();
    scanf("%d", &command);
    if( command == 1)
    {
      scanf("%d", &num);
      int j = 0;
      while( j<numSize) && (numArray[j] <= num)
        j++;

      numArray.push_back( num);
    }
    else
    {
      printf( "%d",  numArray[numSize/3]);
    }
  }
  return 0;
}
