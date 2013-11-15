#include <iostream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

#define FASTIO 1

#if FASTIO
/////////////////////
////// INPUT ////////
////////////////////
class INPUT {
  static const int BUFSIZE = 1<<16;
  static char buffer[];
  char *bufpos;
  char *bufend;
  void grabBuffer();
  public:
  INPUT() { grabBuffer(); }
  bool eof() { return bufend==buffer; }
  char nextChar() { return *bufpos; }
  inline char readChar();
  inline void skipWS();
  long long int readUnsigned();
  long long int readInt();
};

char INPUT::buffer[INPUT::BUFSIZE];

void INPUT::grabBuffer() {
  bufpos = buffer;
  bufend = buffer + fread( buffer, 1,BUFSIZE,stdin);
}

char INPUT::readChar() {
  char res = *bufpos++;
  if(bufpos==bufend) grabBuffer();
  return res;
}

inline bool myisspace(char c) { return c<=' '; }

void INPUT::skipWS() {
  while(!eof() && myisspace(nextChar())) readChar();
}

long long INPUT::readUnsigned() {
  skipWS();
  long long res = 0;
  while(!eof() && isdigit(nextChar())) {
    res = 10u * res + (readChar()-'0');
  }
  return res;
}

long long int INPUT::readInt() {
  skipWS();
  bool neg = false;
  if(!eof() && nextChar()=='-') { neg=true; readChar(); }
  long long int res = static_cast<long long int>(readUnsigned());
  if(neg) res = -res;
  return res;
}

/////////////////////
////// OUTPUT //////
////////////////////

class OUTPUT {
  static const int BUFSIZE = 1<<16;
  static char buffer[];
  char *bufpos;
  char *BUFLIMIT;
  void flushBuffer();
  public:
  OUTPUT():bufpos(buffer),BUFLIMIT(buffer+BUFSIZE-100) {}
  ~OUTPUT() { flushBuffer(); }
  inline void operator()(char c);
  inline void operator()(unsigned x);
  inline void operator()(int x);
  inline void operator()(unsigned long long int x);
  inline void operator()(long long int x);
  inline void operator()(const char*s);
  void operator()(const string&s) { operator()(s.c_str()); }
  template<class A,class B>
    void operator()(const A& a,const B& b) {
      operator()(a); operator()(b);
    }
  template<class A,class B,class C>
    void operator()(const A& a,const B& b,const C&c) {
      operator()(a); operator()(b); operator()(c);
    }
  template<class A,class B,class C,class D>
    void operator()(const A& a,const B& b,const C&c,const D&d) {
      operator()(a); operator()(b); operator()(c); operator()(d);
    }
  template<class A,class B,class C,class D,class E>
    void operator()(const A& a,const B& b,const C&c,const D&d,const E&e) {
      operator()(a); operator()(b); operator()(c); operator()(d); operator()(e);
    }
  template<class A,class B,class C,class D,class E,class F>
    void operator()(const A& a,const B& b,const C&c,const D&d,const E&e,const F&f) {
      operator()(a); operator()(b); operator()(c); operator()(d); operator()(e); operator()(f);
    }
};

char OUTPUT::buffer[OUTPUT::BUFSIZE];

void OUTPUT::flushBuffer() {
  char *p = buffer;
  while(p < bufpos) {
    p += fwrite( p,1, bufpos-p,stdout);
  }
  bufpos = buffer;
}

void OUTPUT::operator()(char c) {
  *bufpos = c;
  ++bufpos;
  if(bufpos >= BUFLIMIT) flushBuffer();
}

void OUTPUT::operator()(unsigned x) {
  char *old = bufpos;
  do {
    *bufpos = char('0' + x % 10u);
    x /= 10u;
    ++bufpos;
  } while(x);
  reverse(old, bufpos);
  if(bufpos >= BUFLIMIT) flushBuffer();
}

void OUTPUT::operator()(int x) {
  if(x<0) { operator()('-'); x = -x; }
  operator()(static_cast<unsigned>(x));
}

void OUTPUT::operator()(unsigned long long int x) {
  char *old = bufpos;
  do {
    *bufpos = char('0' + x % 10u);
    x /= 10u;
    ++bufpos;
  } while(x);
  reverse(old, bufpos);
  if(bufpos >= BUFLIMIT) flushBuffer();
}

void OUTPUT::operator()(long long int x) {
  if(x<0) { operator()('-'); x = -x; }
  operator()(static_cast<unsigned long long int>(x));
}

void OUTPUT::operator()(const char*s) {
  while(*s) operator()(*s++);
}

INPUT input;
OUTPUT output;

#endif

long long int power( int num, int p)
{
  if( num == 0) return 0;
  if( p == 0) return 1;
  if( p == 1) return num;

  if( p%2 == 0)
  {
    long long int x = power( num, p/2);
    return x*x;
  }
  else return num*power(num, p-1);

}

#define MAX 1000001
#define RMAX 1000000000000LL

bool prime[MAX];
vector<int> primes;
vector<long long int> kissNums;

void preProcessing()
{
  primes.clear();

  memset( prime, true, sizeof(prime));

  for( int i=2; i<MAX; i++)
    if( prime[i] == true)
    {
      for( int j=2; j*i<MAX; j++)
        prime[j*i] = false;
    }

  for( int i=2; i<MAX; i++) if( prime[i]) primes.push_back(i);

  int sz = primes.size();
  long long int l;
  for( int i=0; i<sz; i++)
  {
    for( int j=1; l = power(primes[i], primes[j]-1), l>0&&l<=RMAX&&j<sz; j++)
      kissNums.push_back(l);
  }

  sort( kissNums.begin(), kissNums.end());

  //for( int i=0; i<kissNums.size(); i++)
  //  cout << kissNums[i] << endl;
}

int arr[MAX];

long long int primesBet( long long int L, long long int R)
{
  memset( arr, 0, sizeof(arr));
  long long int l=L, r=R;

  if( L < 2) l = 2;

  int sz = primes.size();
  int pNum;
  for( int i=0; i<sz; i++)
  {
    int pNum = primes[i];

    if( pNum > (sqrt(r)+1)) break;

    long long int j = (pNum >= l) ? 2*pNum : l + (pNum - l%pNum)%pNum;

    for( ; j<=r; j+=pNum) arr[j-l] = 1;
  }

  long long int ans = 0;
  for( long long int i=l; i<=r; i++) if(arr[i-l] == 0) ans++;

  return ans;
}

long long int solve( long long int L, long long int R)
{
  long long int ans;
  ans = upper_bound( kissNums.begin(), kissNums.end(), R) -
        lower_bound(kissNums.begin(), kissNums.end(), L);

  ans += primesBet( L, R);
  return ans;
}

int main( int argc, char** argv)
{
  preProcessing();
  int T = input.readInt();
  while(T--)
  {
    long long int L = input.readInt();
    long long int R = input.readInt();

    output( solve(L,R), "\n");
  }
  return 0;
}
