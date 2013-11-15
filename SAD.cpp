#include <iostream>
#include <string.h>
#include <math.h>
#include <stdlib.h>

using namespace std;

int main( int argc, char** argv)
{
  int R,C;
  cin >> R;
  cin >> C;

  int mat[R][C];

  for(int i=0; i<R; i++)
    for(int j=0; j<C; j++)
      cin >> mat[i][j];

  int colIndex[C], rowIndex[R], max, min;

  for(int i=0; i<R; i++)
    rowIndex[i] = -1;

  for(int j=0; j<C; j++)
    colIndex[j] = -1;

  bool foundFlag = false;

  for(int i=0; i<R; i++)
    for(int j=0; j<C; j++)
    {
      if( !foundFlag)
      {
        //largest num index in col
        if( colIndex[j] == -1)
        {
          max = 0;
          for( int l=0; l<R; l++)
            if( mat[l][j] > max)
            {
              max = mat[l][j];
              colIndex[j] = l;
            }
        }

        //min num index in row
        if( rowIndex[i] == -1)
        {
          min = RAND_MAX;
          for( int k=0; k<C; k++)
            if( mat[i][k] < min)
            {
              min = mat[i][k];
              rowIndex[i] = k;
            }
        }

        if( ( mat[i][j] == mat[colIndex[j]][j]) &&
            ( mat[i][j] == mat[i][rowIndex[i]]))
        {
          foundFlag = true;
          cout << mat[i][j]<<endl;
        }
      }
    }
    if( !foundFlag)
    {
      cout << "GUESS" << endl;
    }
  return 0;
}
