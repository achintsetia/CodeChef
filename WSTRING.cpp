#include <iostream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

int cumHist[10000][26];
struct Hist
{
  int hist[26];
};

int maxHistRange(int start, int end)
{
  //start >= 0 and end <=N-1
  int lHist[26];
  int Max;
  if (start == 0)
  {
    Max = cumHist[end][0];
    for( int h=1; h<26; h++)
      if( cumHist[end][h] > Max) Max = cumHist[end][h];
  }
  else
  {
    Max = cumHist[end][0] - cumHist[start-1][0];
    for( int h=1; h<26; h++)
      if( cumHist[end][h] - cumHist[start-1][h] > Max)
        Max = cumHist[end][h] - cumHist[start-1][h];
  }
  return Max;
}

int main( int argc, char** argv)
{
  int T;
  cin >> T;

  while(T--)
  {
    string str; cin >> str; int strLen = str.size();

    int lhist[26];
    for( int h=0; h<26; h++) lhist[h] = 0;
    vector<Hist> vecHist;

    for( int i=0; i<strLen; i++)
      if( str[i] == '#')
      {
        Hist temp;
        for( int h=0; h<26; h++)
        {
          temp.hist[h] = lhist[h];
          lhist[h] = 0;
        }
        vecHist.push_back(temp);
      }
      else
        lhist[str[i] - 'a']++;
    Hist temp;
    for( int h=0; h<26; h++)
    {
      temp.hist[h] = lhist[h];
      lhist[h] = 0;
    }
    vecHist.push_back(temp);

    int vecSize = vecHist.size();
#if 0
    for( int i=0; i<vecSize; i++)
    {
      for( int h=0; h<26; h++) cout << vecHist[i].hist[h] << " ";
      cout << endl;
    }
#endif

    for( int h=0; h<26; h++)
      cumHist[0][h] = vecHist[0].hist[h];

    for( int i=1; i<vecSize; i++)
      for( int h=0; h<26; h++)
        cumHist[i][h] = cumHist[i-1][h] + vecHist[i].hist[h];

#if 0
  cout << "CumHist: "  << endl;
    for( int i=0; i<vecSize; i++)
    {
      for( int h=0; h<26; h++) cout << cumHist[i][h] << " ";
      cout << endl;
    }
#endif
    int A = maxHistRange(0,0);
    int B = maxHistRange(1,1);
    int C = maxHistRange(2,2);
    int D = maxHistRange(3,vecSize-1);
    int Max = 0;
    if( A>0 && B>0 && C>0 && D>0)
      Max = A+B+C+D;
    for(int i=1; i<vecSize-3; i++)
    {
      int A1 = maxHistRange(0,i);
      int B1 = maxHistRange(i+1,i+1);
      int C1 = maxHistRange(i+2,i+2);
      int D1 = maxHistRange(i+3,vecSize-1);
      if( A1>0 && B1>0 && C1>0 && D1>0 && A1+B1+C1+D1 > Max) Max = A1+B1+C1+D1;
    }
    if( Max > 0)
      cout << Max+3 << endl;
    else
      cout << 0 << endl;
  }
  return 0;
}
