#include<cstdio>
#include<iostream>
#include<cstdlib>
#include<cstring>
#include<string>
#define MAX 99999
#define ARRAY_SIZE(A) sizeof(A)/sizeof(A[0])

using namespace std;

struct prof
{
	int y;
	int p;
}a[MAX];

int compare (const void * a, const void * b)
{
  return ( ((struct prof*)a)->y - ((struct prof*)b)->y );
}


int CeilIndex(int A[], int l, int r, int key) {
    int m;
 
    while( r - l > 1 ) {
        m = l + (r - l)/2;
        (A[m] >= key ? r : l) = m; 
    }
 
    return r;
}
 
int LongestIncreasingSubsequenceLength(int A[], int size) {
 
    int *tailTable   = new int[size];
    int len; 
    int i;
 
    memset(tailTable, 0, sizeof(tailTable[0])*size);
 
    tailTable[0] = A[0];
    len = 1;
    for( i = 1; i < size; i++ ) {
        if( A[i] < tailTable[0] )
            
            tailTable[0] = A[i];
        else if( A[i] > tailTable[len-1] )
         
            tailTable[len++] = A[i];
        else
            
            tailTable[CeilIndex(tailTable, -1, len-1, A[i])] = A[i];
    }
 
    delete[] tailTable;
 
    return len;
}


int main()
{
	//typedef struct prof a[MAX];	
	//A a[MAX];
	int pub[MAX];
	int N,i;
	int yin, pin;
	int temp;
	scanf("%d", &N);
	for( i=0;i<N;++i)
	{
		scanf("%d %d", &yin, &pin);
		 a[i].y=yin;a[i].p=pin;
	}

	//qsort (a, N, sizeof(struct prof), compare);	
	//cout<<"hello"<<endl;exit(0);
	
	for(int i=0;i<N;++i)
	{
		for(int j=0;j<N;++j)
		{
			if (a[i].y==a[j].y)
			{
				if (a[i].p>a[j].p)
				{
					temp=a[i].p;
					a[i].p=a[j].p;
					a[j].p=temp;
					
				}
			}
			else if (a[i].y<a[j].y)
			{
				temp=a[i].p;
				a[i].p=a[j].p;
				a[j].p=temp;
				temp=a[i].y;
				a[i].y=a[j].y;
				a[j].y=temp;
				
			}
		}
	}
	
	
	
	for( i=0;i<N;++i)
	{
		pub[i]=a[i].p;
	//	cout<<pub[i]<<endl;
	}
	
	printf("%d\n",LongestIncreasingSubsequenceLength(pub, N));
	return 0;
}
