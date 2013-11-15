#include <iostream>
#include <vector>
#include <stdio.h>
#include <algorithm>



using namespace std;

struct node
{
  int num;
  char name[16];
};

int main( int argc, char** argv)
{
  int N, pileSize = 0;
  int *minIndex = new int[1000000];

  minIndex[0] = 0;
  node *books = new node[1000000];
  node tempNode;

  scanf("%d", &N);

  while(N--)
  {
    scanf("%d", &tempNode.num);
    if( tempNode.num == -1)
    {
      printf("%d %s\n", pileSize-1 - minIndex[pileSize-1], books[minIndex[pileSize-1]].name);
      pileSize = minIndex[pileSize-1];
    }
    else
    {
      scanf("%s", tempNode.name);
      if( tempNode.num > 0)
      {
        books[pileSize] = tempNode;

        if( pileSize > 0)
        {
          if( books[pileSize].num <= books[minIndex[pileSize-1]].num)
            minIndex[pileSize] = pileSize;
          else
            minIndex[pileSize] = minIndex[pileSize-1];
        }
        pileSize++;
      }
    }
  }

  delete minIndex;
  delete books;
  return 0;
}
