#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<cmath>
typedef unsigned long long int int64;
using namespace std;
int64 mulmod(int64 a,int64 b,int64 c);
int64 modulo(int64 a ,int64 pow,int64 n)
{
  int64 y,u;
  y=1;
  u=a;
  //cout<<"y"<<" "<<"u"<<" "<<"pow"<<"\n";
  while(pow > 0)
  {
    //cout<<y<<" "<<u<<" "<<pow<<"\n";
    if(pow%2 == 1)
      y=mulmod(y,u,n);
    u = mulmod(u,u,n);
    pow/=2;
  }
  return y%n;

}
int64 mulmod(int64 a,int64 b,int64 c)
{
  int64 x=0,y=a%c;
  while(b>0)
  {
    if(b%2==1)
    {
      x = (x+y)%c;
    }
    y = (y*2)%c;
    b/=2;
  }
  return x%c;
}

bool miller(int64 n,int it)
{
  if(n<2)
    return false;
  if(n!=2 and n%2==0)
    return false;
  int64 s=n-1;
  while(s%2==0) s/=2;

  for(int i=0;i<it;i++)
  {
    int64 a = rand()%(n-1)+1,temp=s;
    int64 mod = modulo(a,temp,n);
    while(temp!=n-1 && mod!=1 && mod!=n-1)
    {
      mod = mulmod(mod,mod,n);
      temp*=2;
    }
    if(mod!=n-1 and temp%2==0)
    {
      return false;
    }
  }
  return true;
}

int main()
{
  int64 n;
  int t;
  scanf("%d",&t);
  while(t--)
  {
    scanf("%llu",&n);
    if( n == 2)
    {
      printf("2\n"); continue;
    }
    if(n!=2 and n%2==0)
      n--;
    while(!miller(n,2)) n-=2;
    printf("%llu\n",n);
  }
  return 0;
}
