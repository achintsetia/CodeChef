#include <iostream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

string randPermute( string input)
{
  string output = string("");
  int inpLength = input.size();
  int outLength = inpLength + rand()%3 - 1;
  if( outLength < 8) outLength = 8;
  if( outLength > 12) outLength = 12;

  int min = (outLength<inpLength)?outLength:inpLength;
  for(int i=0; i<min; i++)
    output += input[i];

  if( min < outLength)
  {
    for( int i=min; i<outLength; i++)
      output += (char) (97 + rand()%26);
  }

  return output;
}

string genRandPassW(int length)
{
  string ret;
  for(int i=0; i<length; i++)
    ret += (char) (97 + rand()%26);
  return ret;
}

int main( int argc, char** argv)
{
  int T, N, H;

  scanf("%d", &T);
  scanf("%d", &N);
  scanf("%d", &H);

  string passwords[T][N];
  int S[T];
  int thresh = 10;

  for(int count=0; count<T; count++)
  {
    if( count < thresh)
    {
      for( int i=0; i<N; i++)
      {
        passwords[count][i] = genRandPassW( 8+rand()%5);
        printf("%s\n", passwords[count][i].c_str());
      }
      fflush(stdout);
      scanf("%d", &S[count]);
    }
    else
    {
      //pick the best submission
      int maxCount = 0;
      for( int i=0; i<count; i++)
        if( S[i] > S[maxCount])
          maxCount = i;

      for( int i=0; i<N; i++)
      {
        passwords[count][i] = randPermute(passwords[maxCount][i]);
        printf("%s\n", passwords[count][i].c_str());
      }
      fflush(stdout);
      scanf("%d", &S[count]);
    }
  }

  return 0;
}
