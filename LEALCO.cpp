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

int R[17];
int table[18];

int calcFaults( int D[], int N, int M, int K)
{
  int count = 0;
  for( int i=0; i<N-K+1; i++)
  {
    int maxR = D[i];
    for( int k=i; k<K+i; k++)
      if( D[k] > maxR)
        maxR = D[k];

    int maxCount = 0;
    for( int k=i; k<K+i; k++)
      if( D[k] == maxR)
        maxCount++;

    if( maxCount >= M)
      count++;
  }
  return count;
}

int power(int num, int p)
{
  if( p == 0)
    return 1;

  if( p == 1)
    return num;

  if( p % 2 == 0)
  {
    int temp = power(num, p/2);
    return temp*temp;
  }
  else
    return power(num, p-1)*num;
}

void computeTable()
{
  for( int i=0; i<18; i++)
    table[i] = 1 << i;
}

int main( int argc, char** argv)
{
  int T = input.readInt();

  computeTable();

  while(T--)
  {
    int N = input.readInt();
    int K = input.readInt();
    int M = input.readInt();

    int minIndex;

    for (int i=0; i<N; i++)
      R[i] = input.readInt();

    if( M == 1)
    {
      output(-1, "\n");
      continue;
    }

    if( calcFaults(R, N, M, K) == 0)
    {
      output(0, "\n");
      continue;
    }

    int minOps = N;
    int bound = power(2, N+1);
    int D[N];

    for( int i=0; i<bound; i++)
    {
      int opsCount = 0;
      for( int j=0; j<N; j++)
      {
        if( (i & table[j]) > 0)
        {
          opsCount++;
          D[j] = R[j] + 1;
        }
        else
          D[j] = R[j];
      }
#if 0
      cout << i << "D: ";
      for( int l=0; l<N; l++) cout << D[l] << " ";
      cout << endl;
#endif

      if( opsCount < minOps && calcFaults(D, N, M, K) == 0)
      {
        minOps = opsCount;
        minIndex = i;
      }

      if( minOps == 0)
      {
        minIndex = i;
        break;
      }
    }
#if 0
    for( int j=0; j<N; j++)
    {
      if( (minIndex & table[j]) > 0)
        cout << R[j] + 1 << " ";
      else
        cout << R[j] << " ";
    }
    cout << endl;
#endif
    if( minOps == N)
      output( -1, "\n");
    else
      output( minOps, "\n");
  }
  return 0;
}
