#include <iostream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

#define MAX 1001

void giveNomDenom( int A, int B, vector<int>& nom, vector<int>& denom)
{
  nom.clear();
  denom.clear();
  if( B < 0 || A < B)
  {
    nom.push_back(0);
    denom.push_back(1);
  }

  //B is always less than equal to A
  if( A-B < B)
  {
    for( int i=B+1; i<=A; i++)
        nom.push_back(i);

    for( int i=2; i<=A-B; i++)
        denom.push_back(i);
  }
  else
  {
    for( int i=A-B+1; i<=A; i++)
        nom.push_back(i);

    for( int i=2; i<=B; i++)
        denom.push_back(i);
  }
  nom.push_back(1);
  denom.push_back(1);
  return;
}

void cancelFactors( vector<int>& fA, vector<int>& fB)
{
  sort(fA.begin(), fA.end());
  sort(fB.begin(), fB.end());

  int n = 0, d=0;
  while(n<fA.size() && d<fB.size())
  {
    if( fA[n] < fB[d]) n++;
    else if( fA[n] > fB[d]) d++;
    else
    {
      fA[n++] = -1;
      fB[d++] = -1;
    }
  }
}

long double probHappy( int S, int N, int M, int K)
{
  vector<int> out_nom, out_denom;
  vector<int> nom, denom;
  vector<int> g_nom, g_denom;

  giveNomDenom( S-1, N-1, out_denom, out_nom);

  long double ans = 0.0;
  for( int i=K; i<=M-1; i++)
  {
    long double l_ans = 1.0;
    nom.clear(), denom.clear(), g_nom.clear(), g_denom.clear();

    giveNomDenom( M-1, i, nom, denom);
    if( nom[0] == 0) continue;
    for( int j=0; j<nom.size(); j++) g_nom.push_back(nom[j]);
    for( int j=0; j<denom.size(); j++) g_denom.push_back(denom[j]);
    nom.clear(), denom.clear();

    giveNomDenom( S-M, N-1-i, nom, denom);
    if( nom[0] == 0) continue;
    for( int j=0; j<nom.size(); j++) g_nom.push_back(nom[j]);
    for( int j=0; j<denom.size(); j++) g_denom.push_back(denom[j]);

    for( int j=0; j<out_nom.size(); j++) g_nom.push_back(out_nom[j]);
    for( int j=0; j<out_denom.size(); j++) g_denom.push_back(out_denom[j]);

    cancelFactors( g_nom, g_denom);

    for( int j=0, k=0; j<g_nom.size() || k<g_denom.size(); )
    {
      if( j<g_nom.size())
        while( g_nom[j] == -1) j++;

      if( j<g_nom.size())
        l_ans *= (long double) g_nom[j++];

      if( k<g_denom.size())
        while( g_denom[k] == -1) k++;
      if( k<g_denom.size())
        l_ans /= (long double) g_denom[k++];
    }

    ans += l_ans;
  }
  return ans;
}

int main( int argc, char** argv)
{
  int T;
  scanf("%d", &T);

  while(T--)
  {
    int S, N, M, K;

    scanf("%d", &S);
    scanf("%d", &N);
    scanf("%d", &M);
    scanf("%d", &K);

    if( N <= K) printf( "0.00000000\n");
    else if( S == N) printf( "1.00000000\n");
    else printf( "%0.8Lf\n", probHappy( S, N, M, K));
  }
  return 0;
}
