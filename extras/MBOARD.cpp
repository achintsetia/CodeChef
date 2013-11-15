#include <iostream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

bool rowTru[500001];
bool colTru[500001];

bool rowFal[500001];
bool colFal[500001];

int main( int argc, char** argv)
{
  int N, Q;
  char str[10];
  int index, x;
  int numRowTru = 0;
  int numColTru = 0;
  int numRowFal = 0;
  int numColFal = 0;

  scanf( "%d %d", &N, &Q);

  for( int i=0; i<Q; i++)
  {
    scanf( "%s %d", str, &index);

    if( !strcmp(str, "RowSet"))
    {
      scanf( "%d", &x);
      if( x == 1)
      {

      }
      else
      {

      }
    }
    else if( !strcmp(str, "ColSet"))
    {
      scanf( "%d", &x);
      if( x == 1)
      {

      }
      else
      {

      }
    }
    else if( !strcmp(str, "RowQuery"))
    {

    }
    else if( !strcmp(str, "ColQuery"))
    {

    }
  }
  return 0;
}
