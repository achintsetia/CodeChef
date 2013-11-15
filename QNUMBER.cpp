#include <iostream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX_SIZE 10000000
static char input[MAX_SIZE];
struct Scanner
{
  Scanner()
  {
    int sz = fread(input, 1, sizeof(input), stdin);
    curPos = input;
  }
  long long int nextInt()
  {
    int gap = input + MAX_SIZE - curPos;
    if (gap < 100)
    {
      memcpy(input, curPos, gap);
      fread(input + gap, 1, sizeof(input) - gap, stdin);
      curPos = input;
    }
    while (*curPos < '0') curPos++;

    long long int res = 0;
    while (*curPos >= '0')
    {
      res = res * 10 + (*curPos) - '0';
      curPos++;
    }
    return res;
  }
  char* curPos;
};

#define MAX 1000000
typedef long long int ll;

bool primes[MAX];

ll* temp = new ll[100*2];

void generatePrimes()
{
  for( int i=0; i<MAX; i++) primes[i] = 1;
  int sqrtN = (int)sqrt(MAX);
  for( int i=2; i<=sqrtN; i++)
    if( primes[i])
    {
      for( int j=i; j*i<MAX; j++)
        primes[i*j] = 0;
    }
}

int getPrimeFactors( ll num, ll* &array)
{
  if( num == 1)
  {
    array[0]= 1;
    array[1]= 0;
    return 1;
  }

  int sqrtN = (int) sqrt(num);
  ll temp = num;
  int arrayCount = 0;
  for( int i=2; i<=sqrtN; i++)
  {
    if( primes[i] && temp % i == 0)
    {
      int count = 0;
      do
      {
        count++;
        temp /= i;
      }
      while( temp % i == 0);

      array[arrayCount*2+0] = i; array[arrayCount*2+1] = count;
      arrayCount++;
      sqrtN = sqrt(temp);
    }
  }
  if( temp != 1)
  {
    array[arrayCount*2+0] = temp; array[arrayCount*2+1] = 1;
    arrayCount++;
  }
  return arrayCount;
}

void printFacs( int NFacSize, ll* NFactors)
{
  for( int i=0; i<NFacSize; i++)
    cout << NFactors[i*2+0] <<"^"<< NFactors[i*2+1] << " * ";
  cout << endl;
}

ll numDivisors( ll* array, int size)
{
  if( size == 0)
    return 0;
  ll sum = 1;
  for( int i=0; i<size; i++)
    sum *= (array[2*i+1]+1);
  return sum;
}

ll gcd( ll a, ll b)
{
  if (b==0) return a;
  return gcd(b,a%b);
}

int getPrimeFactors( ll K, ll* &NFactors, int NFacSize, ll* &array)
{
  if( K == 0)
    return 0;

  if( K == 1)
  {
    array[0] = 1;
    array[1] = 0;
    return 1;
  }

  int arrayCount = 0;
  ll temp = K;
  for( int i=0; i<NFacSize; i++)
  {
    if( temp % NFactors[2*i+0] == 0)
    {
      int count = 0;
      do
      {
        count++;
        temp /= NFactors[2*i+0];
      }
      while( temp % NFactors[2*i+0] == 0);

      array[arrayCount*2+0] = i; array[arrayCount*2+1] = count;
      arrayCount++;
    }
  }
  return arrayCount;
}

ll numDivisors( ll num, ll* NFactors, int NFacSize)
{
  int facSize =  getPrimeFactors( num, NFactors, NFacSize, temp);
  return numDivisors( temp, facSize);
}

int main( int argc, char** argv)
{
  generatePrimes();

  ll N, K;
  int Q, T;

  Scanner sc;

  N = sc.nextInt();
  Q = (int) sc.nextInt();

  //scanf("%lld %d", &N, &Q);

  ll* NFactors = new ll[100*2];
  int NFacSize = getPrimeFactors( N, NFactors);

  //printFacs( NFacSize, NFactors);
  ll NDivisors = numDivisors( NFactors, NFacSize);

  ll gcdNK;

  while( Q--)
  {
    T = (int) sc.nextInt();
    K = sc.nextInt();
    //scanf( "%d %lld", &T, &K);

    if( T == 1)
    {
      if( N%K == 0)
        gcdNK = K;
      else
        gcdNK = gcd(N, K);

      if( gcdNK == 1)
        printf( "1\n");
      else
        printf("%lld\n", numDivisors( gcdNK, NFactors, NFacSize));
    }
    else
    {
      if( T == 2)
      {
        if( N%K == 0)
        {
          if( K!=1)
            printf("%lld\n", numDivisors( N/K, NFactors, NFacSize));
          else
            printf("%lld\n", NDivisors);
        }
        else
          printf("0\n");
      }
      else
      {
        if( N%K == 0)
        {
          if( K!=1)
            printf("%lld\n", NDivisors - numDivisors( N/K, NFactors, NFacSize));
          else
            printf("0\n");
        }
        else
          printf("%lld\n", NDivisors);
      }
    }
  }
  return 0;
}
