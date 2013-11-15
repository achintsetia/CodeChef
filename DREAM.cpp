#include <iostream>
#include <fstream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <vector>

using namespace std;

int hashFunc(int k, int N)
{
  return (unsigned long long int) ((10 * k + 97) % 1000000007) % N;
}

struct list
{
  int val;
  vector<int> indexes;
};

struct hashlist
{
  vector<int> indexes;
};

int numCount = 0;
list* table = new list[100001];
hashlist* hash = new hashlist[100001];

void insertElem( int k, int N, int arrInd)
{
  unsigned int index = hashFunc(k, N);
  int chainSize = hash[index].indexes.size();

  if( chainSize == 0)
  {
    hash[index].indexes.push_back( numCount);
    table[numCount].val = k;
    table[numCount].indexes.push_back( arrInd);
    numCount++;
  }
  else
  {
    int i=0;
    while(( i<chainSize) && ( table[hash[index].indexes[i]].val != k))
      i++;
    if( i == chainSize)
    {
      hash[index].indexes.push_back( numCount);
      table[numCount].val = k;
      table[numCount].indexes.push_back( arrInd);
      numCount++;
    }
    else
      table[hash[index].indexes[i]].indexes.push_back( arrInd);
  }
}

int minPasses( int meals[], int N, int K)
{

  int count =0;

  for( int i=0; i<N; i++)
    insertElem(meals[i], N, i);

#if 0
  for( int i=0; i<numCount; i++)
  {
    cout << table[i].val ;
    for( int j=0; j<table[i].indexes.size(); j++)
      cout << " -> " << table[i].indexes[j];
    cout << endl;
  }
#endif

  for( int i=0; i<numCount; i++)
  {
    int indexSize = table[i].indexes.size();
    int j = 0;
    while( j<indexSize)
    {
      int k = j+1;
      while(( k < indexSize) && (table[i].indexes[k] - table[i].indexes[j] <= K-1))
        k++;

      //cout << "Cooked :" << table[i].indexes[j] << " to " << table[i].indexes[k-1] << " of time " << table[i].val << endl;
      count++;
      j = k;
    }
    //cout << endl;
  }
  return count;
}

int main( int argc, char** argv)
{
  int N, K;
  cin >> N;
  cin >> K;

  int meals[N];

  for ( int i=0; i<N; i++)
  {
    cin >> meals[i];
  }

  cout << minPasses( meals, N, K) <<  endl;

  return 0;
}
