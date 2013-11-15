#include <iostream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

void printArray( bool* array, int T)
{
  cout << "Array :" << endl;
  for( int i=0; i<T; i++)
  {
    for( int j=0; j<T; j++)
      cout << *(array + i*T+j) << " ";
    cout << endl;
  }
}

bool match( bool array1[], bool array2[], int T)
{
  for( int i=0; i<T; i++)
    if( array1[i] != array2[i]) return false;
  return true;
}


int main( int argc, char** argv)
{
  int T;
  scanf("%d", &T);

  char tmp[4];
  bool array[T][T];
  bool ans[T];
  bool breakFlag = false;

  for( int i=0; i<T; i++)
  {
    for( int j=0; j<T; j++)
    {
      scanf("%s", tmp);
      if( !strncmp( tmp, "YES", 3))
        array[i][j] = true;
      else
        array[i][j] = false;
    }
  }

  //printArray( (bool*) array, T);

  for( int k=0; k<T; k++)
  {
    for( int i=0; i<T; i++)
    {
      if( k != i)
        ans[i] = match( array[k], array[i], T);
      else
        ans[i] = true;
    }
    if( match( ans, array[k], T))
    {
      for( int i=0; i<T; i++)
      {
        if( ans[i])
          cout<< "YES" << endl;
        else
          cout<< "NO" << endl;
      }
      breakFlag = true;
      break;
    }
  }
  if( !breakFlag)
  {
    for( int i=0; i<T; i++)
    {
      cout<< "NO" << endl;
    }
  }
  return 0;
}
