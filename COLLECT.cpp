#include <iostream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

#define MAXN  3000001
#define MAXM   100001
#define MOD   3046201

long long int factorials[MAXN];
long long int invFactorials[MAXM];
long long int invNumbers[MAXM];
int tree[MAXM];

long long int powInt(int num, int p)
{
  if( num == 1) return 1;
  if( p == 0) return 1;
  else if( p == 1) return num;
  if( p%2 == 0)
  {
    long long int x = powInt(num, p/2);
    return (x*x)%MOD;
  }
  else
    return (num*powInt(num, p-1))%MOD;
}

void preProcess()
{
  factorials[0] = 1;
  factorials[1] = 1;
  for(int i=2; i<=MAXN; i++)
    factorials[i] = (factorials[i-1]*i) % MOD;

  invNumbers[1] = 1;
  for(int i=2; i<MAXM; i++)
    invNumbers[i] = powInt(i, 3046199);

  invFactorials[0] = 1;
  invFactorials[1] = 1;
  for(int i=2; i<MAXM; i++)
    invFactorials[i] = (invFactorials[i-1]*invNumbers[i])%MOD;
}

void updateTree( int idx, int val)
{
  while( idx<=MAXM)
  {
    tree[idx] += val;
    idx += (idx & -idx);
  }
}

int readTree( int idx)
{
  int sum = 0;
  while( idx > 0)
  {
    sum += tree[idx];
    idx -= (idx & -idx);
  }
  return sum;
}
int readSingle(int idx)
{
  int sum = tree[idx]; // sum will be decreased
  if (idx > 0)
  { // special case
    int z = idx - (idx & -idx); // make z first
    idx--; // idx is no important any more, so instead y, you can use idx
    while (idx != z)
    { // at some iteration idx (y) will become z
      sum -= tree[idx];
      // substruct tree frequency which is between y and "the same path"
      idx -= (idx & -idx);
    }
  }
  return sum;
}

long long int getAns(int L, int R)
{
  int N = readTree(R) - readTree(L-1);
  int M = R-L+1;
  int B = N%M;
  int P = N/M;

  long long int ans = factorials[N];
  ans = (ans*factorials[M]) % MOD;
  ans = (ans*invFactorials[B])%MOD;
  ans = (ans*invFactorials[M-B])%MOD;
  ans = (ans*powInt(invFactorials[P], M)) % MOD;
  ans = (ans*powInt(invNumbers[P+1], B))%MOD;
  return ans;
}

int main( int argc, char** argv)
{
  preProcess();

  int N; scanf("%d", &N);
  for( int i=1; i<=N; i++)
    tree[i] = 0;

  int num;
  for( int i=1; i<=N; i++)
  {
    scanf("%d", &num);
    updateTree( i, num);
  }

  int Q; scanf("%d", &Q);

  char query[10]; int A, B;
  for(int i=0; i<Q; i++)
  {
    scanf("%s %d %d", query, &A, &B);

    if( query[0] == 'c')
    {
      int val = readSingle(A);
      updateTree(A, B-val);
    }
    else
      printf("%lld\n", getAns(A, B));
  }
  return 0;
}
