#include <iostream>
#include <string.h>
#include <math.h>

using namespace std;

int main( int argc, char** argv)
{
  int T;
  cin >> T;

  for( int i=0; i<T; i++)
  {
    int N, leftCand;
    cin >> N;
    cin >> leftCand;

    int A[N];
    for( int k=0; k<N; k++)
    {
      cin >> A[k];
    }

    int k=0;
    while( leftCand >= 0)
    {
      leftCand -= A[k];
      k++;
    }
    if( k > N)
      cout << "Yes" << endl;
    else
      cout << "No" << endl;
  }
}
