#include <iostream>
#include <string.h>
#include <math.h>

using namespace std;

int main( int argc, char** argv)
{
  int N, K;
  cin >> N;
  cin >> K;
  bool open[N+1];
  for ( int i=0; i<=N; i++)
    open[i] = false;

  string str;
  int num;
  for( int i=0; i<K; i++)
  {
    cin >> str;
    if( !str.compare("CLICK"))
    {
      cin >> num;
      open[num] = (open[num] != true);
      int count = 0;
      for( int j=0; j<=N; j++)
      {
        if( open[j])
          count++;
      }
      cout << count << endl;
    }
    else if( !str.compare("CLOSEALL"))
    {
      for( int j=0; j<=N; j++)
          open[j] = false;
      cout << 0 << endl;
    }
  }
return 0;
}
