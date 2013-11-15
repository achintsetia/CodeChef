#include <iostream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

#define mod 1000000007

string DecimalToBinaryString(int a, int bits)
{
  string binary = "";
  int mask = 1;
  for(int i = 0; i < bits; i++)
  {
    if((mask&a) >= 1)
      binary = "1"+binary;
    else
      binary = "0"+binary;
    mask<<=1;
  }
  return binary;
}

long long int newPow( unsigned int base, int exponent)
{
  if( exponent == 0)
    return 1;
  else if( exponent % 2 == 0)
  {
    long long int half_pow = newPow(base, exponent / 2) % mod;
    half_pow *= half_pow % mod;
    return half_pow % mod;
  }
  else return (base * newPow(base, exponent - 1)) % mod;
}

bool analyse( int i, int bits)
{
  string binary = DecimalToBinaryString( i, bits);

  bool isWrong = false;

  for( int i=2; i<binary.size(); i++)
    if( binary[i] == '1' && binary[i-1] =='1' && binary[i-2] == '1')
      isWrong = true;

  if( isWrong)
  {
    for( int i=binary.size()-1; i>=0; i--)
    {
      if( binary[i] == '1')
        cout << binary.size() - i << " ";
    }
    cout << endl;
  }

  return isWrong;
}

int main( int argc, char** argv)
{
  int T, count = 0;
  scanf( "%d", &T);

  int range = newPow( 2, T);

  for( int i=0; i<range; i++)
  {
    if( analyse( i, T))
      count++;
  }
  cout << "Count: " << count << endl;
  return 0;
}
