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

#define MAXN 100001

int STmin[100001][17];
int STmax[100001][17];

void makeSparseTableMin( int b[], int N)
{
  //Sparse table for RMQs
  int i, j;
  for( int i=0; i<N; i++)
    STmin[i][0] = i;

  for( int j=1; 1<<j <= N; j++)
    for( int i=0; i+(1<<j)-1 < N; i++)
      if( b[STmin[i][j-1]] < b[STmin[i + (1<<(j-1))][j-1]])
        STmin[i][j] = STmin[i][j-1];
      else
        STmin[i][j] = STmin[i + (1<<(j-1))][j-1];
}

int RMQmin(int b[], int i, int j)
{
  int k = (int) log2(j-i+1);
  if(b[STmin[i][k]] <= b[STmin[j-(1<<k)+1][k]]) return STmin[i][k];
  else return STmin[j-(1<<k)+1][k];
}

void makeSparseTableMax( int b[], int N)
{
  //Sparse table for RMQs
  int i, j;
  for( int i=0; i<N; i++)
    STmax[i][0] = i;

  for( int j=1; 1<<j <= N; j++)
    for( int i=0; i+(1<<j)-1 < N; i++)
      if( b[STmax[i][j-1]] > b[STmax[i + (1<<(j-1))][j-1]])
        STmax[i][j] = STmax[i][j-1];
      else
        STmax[i][j] = STmax[i + (1<<(j-1))][j-1];
}

int RMQmax(int b[], int i, int j)
{
  int k = (int) log2(j-i+1);
  if(b[STmax[i][k]] >= b[STmax[j-(1<<k)+1][k]]) return STmax[i][k];
  else return STmax[j-(1<<k)+1][k];
}


int main( int argc, char** argv)
{
  int N = input.readInt();
  int b[N];
  for( int i=0; i<N; i++)
    b[i] = input.readInt();

  makeSparseTableMin(b, N);
  makeSparseTableMax(b, N);

  int Q = input.readInt();

  while(Q--)
  {
    int L = input.readInt();
    int R = input.readInt();

    if( L > 0 && R < N-1)
    {
      double min  = (double) b[RMQmin(b, L, R)];
      double maxA = (double) b[RMQmax(b, 0, L-1)];
      double maxB = (double) b[RMQmax(b, L, R)];
      double maxC = (double) b[RMQmax(b, R+1, N-1)];
#if 0
      cout << "Min: "<< min << endl;
      cout << "MaxA: "<< maxA << endl;
      cout << "MaxB: "<< maxB << endl;
      cout << "MaxC: "<< maxC << endl;
#endif
      maxA += min; maxC += min; maxB = min + ((maxB - min)/2);

      if( maxA >= maxB && maxA >= maxC) printf("%.1f\n", maxA);
      else if( maxB >= maxA && maxB >= maxC) printf("%.1f\n", maxB);
      else if( maxC >= maxB && maxC >= maxA) printf("%.1f\n", maxC);
    }
    else if( L > 0)
    {
      double min  = (double) b[RMQmin(b, L, R)];
      double maxA = (double) b[RMQmax(b, 0, L-1)];
      double maxB = (double) b[RMQmax(b, L, R)];

      maxA += min; maxB = min + ((maxB - min)/2);

      if( maxA >= maxB) printf("%.1f\n", maxA);
      else printf("%.1f\n", maxB);
    }
    else if( R < N-1)
    {
      double min  = (double) b[RMQmin(b, L, R)];
      double maxB = (double) b[RMQmax(b, L, R)];
      double maxC = (double) b[RMQmax(b, R+1, N-1)];

      maxC += min; maxB = min + ((maxB - min)/2);

      if( maxB >= maxC) printf("%.1f\n", maxB);
      else printf("%.1f\n", maxC);
    }
    else
    {
      double min  = (double) b[RMQmin(b, L, R)];
      double maxB = (double) b[RMQmax(b, L, R)];
      maxB = min + ((maxB - min)/2);

      printf("%.1f\n", maxB);
    }
  }
  return 0;
}
