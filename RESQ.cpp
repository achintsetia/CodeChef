#include <cstdlib>
#include <iostream>
#include <math.h>

using namespace std;

int main(int argc, char *argv[])
{
  int T;
  cin >> T;
  for( int i=0; i<T; i++)
  {
    int num;
    cin >> num;
    int sqrtNum = (int) sqrt((float) num);
    while(( num % sqrtNum != 0) && (sqrtNum > 0))
      sqrtNum--;

    if( sqrtNum == 1)
      cout << num - sqrtNum << endl;
    else
      cout << (int) abs( sqrtNum - (num / sqrtNum)) << endl;
  }
  //system("PAUSE");
  return 0;
}
