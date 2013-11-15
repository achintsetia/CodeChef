#include <iostream>
#include <string.h>
#include <cmath>
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

#define MOD 1000000007

int log2(int N)
{
    int ans = 0;
    while( N>>=1)
        ans++;
    return ans;
}

int exp2(int N)
{
    return 1 << N;
}

int A[100000];

int Min[100000][20];
int Max[100000][20];


void process2Min(int N)
{
  int i, j;

  //initialize M for the intervals with length 1
  for (i = 0; i < N; i++)
    Min[i][0] = i;
  //compute values from smaller to bigger intervals
  for (j = 1; 1 << j <= N; j++)
    for (i = 0; i + (1 << j) - 1 < N; i++)
      if (A[Min[i][j - 1]] < A[Min[i + (1 << (j - 1))][j - 1]])
        Min[i][j] = Min[i][j - 1];
      else
        Min[i][j] = Min[i + (1 << (j - 1))][j - 1];
}

void process2Max(int N)
{
  int i, j;

  //initialize M for the intervals with length 1
  for (i = 0; i < N; i++)
    Max[i][0] = i;
  //compute values from smaller to bigger intervals
  for (j = 1; 1 << j <= N; j++)
    for (i = 0; i + (1 << j) - 1 < N; i++)
      if (A[Max[i][j - 1]] > A[Max[i + (1 << (j - 1))][j - 1]])
        Max[i][j] = Max[i][j - 1];
      else
        Max[i][j] = Max[i + (1 << (j - 1))][j - 1];
}

int RMQMax(int i, int j)
{
  int k= log2(j-i+1);

  if(A[Max[i][k]] >= A[Max[j-exp2(k)+1][k]])
    return Max[i][k];
  else
    return Max[j-exp2(k)+1][k];
}

int RMQMin(int i, int j)
{
  int k=log2(j-i+1);

  if(A[Min[i][k]] <= A[Min[j-exp2(k)+1][k]])
    return Min[i][k];
  else
    return Min[j-exp2(k)+1][k];
}

int main( int argc, char** argv)
{
  int N = input.readInt();

  for( int i=0; i<N; i++)
    A[i] = input.readInt();

  process2Min( N);
  process2Max( N);

  long long int prod = 1;

  for( int i=0; i<N-1; i++)
    for( int j=i+1; j<N; j++)
    {
        prod *= (A[RMQMax(i, j)] - A[RMQMin(i, j)]) % MOD;
        if( prod == 0) break;
    }

    output( prod, "\n");

  return 0;
}
