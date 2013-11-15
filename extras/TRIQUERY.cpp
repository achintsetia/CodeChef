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

#define MAX_P 300001
#define MAX_T 200001

#define F first
#define S second

typedef pair<int, int> p;

vector< p > P;
vector< p > auxP;
vector< pair< p, p > > T;
vector< pair< p, p > > auxT;
vector< p >::iterator itP;
vector< p >::iterator itAuxP;
vector< pair<p,p> >::iterator itT;
vector< pair<p,p> >::iterator itAuxT;

int* bitX;
int* bitY;
int* bitXY;
int results[MAX_T];

void update( int* tree, int val, int idx)
{
  while( idx < MAX_P)
  {
    tree[idx] += val;
    idx += (idx & -idx);
  }
}

int cumSum( int* tree, int idx)
{
  int sum = 0;
  while( idx)
  {
    sum += tree[idx];
    idx -= (idx & -idx);
  }
  return sum;
}

bool compXY(p a, p b)
{
  return (a.F + a.S) < (b.F + b.S);
}

bool compXYD( pair<p,p> a, pair<p,p> b)
{
  return ( a.F.F + a.F.S + a.S.F) < (b.F.F + b.F.S + b.S.F);
}

void getResults()
{
  sort( P.begin(), P.end(), compXY);
  sort( T.begin(), T.end(), compXYD);

  itP = P.begin();
  itT = T.begin();

  while( itP != P.end() && itT != T.end())
  {
    if( (itP->F + itP->S) <= (itT->F.F + itT->F.S + itT->S.F))
    {
      update( bitX, 1, itP->F);
      update( bitY, 1, itP->S);
      itP++;
    }
    else
    {
      int xNum = cumSum( bitX, itT->F.F-1);
      int yNum = cumSum( bitY, itT->F.S-1);
      int total = itP - P.begin();
      results[itT->S.S] = total - xNum - yNum;
      itT++;
    }
  }

  while( itT != T.end())
  {
    int xNum = cumSum( bitX, itT->F.F-1);
    int yNum = cumSum( bitY, itT->F.S-1);
    int total = itP - P.begin();
    results[itT->S.S] = total - xNum - yNum;
    itT++;
  }

  sort(auxP.begin(), auxP.end());
  sort(auxT.begin(), auxT.end());

  itAuxP = auxP.begin();
  itAuxT = auxT.begin();

  while( itAuxP != auxP.end() && itAuxT != auxT.end())
  {
    if((itAuxP->F < itAuxT->F.F) ||
      ((itAuxP->F == itAuxT->F.F) && (itAuxP->S <= itAuxT->F.S)))
    {
      update( bitXY, 1, itAuxP->S);
      itAuxP++;
    }
    else
    {
      results[itAuxT->S.S] += cumSum( bitXY, itAuxT->F.S);
      itAuxT++;
    }
  }

  while( itAuxT != auxT.end())
  {
    results[itAuxT->S.S] += cumSum( bitXY, itAuxT->F.S);
    itAuxT++;
  }
}

int main( int argc, char** argv)
{
  bitX = new int[MAX_P];
  bitY = new int[MAX_P];
  bitXY = new int[MAX_P];
  P.reserve(MAX_P);
  T.reserve(MAX_T);
  auxP.reserve(MAX_P);
  auxT.reserve(MAX_T);


  int N = input.readInt();
  int Q = input.readInt();


  for( int i=0; i<N; i++)
  {
    int A = input.readInt();
    int B = input.readInt();
    P.push_back(make_pair(A, B));
    auxP.push_back(P[i]);
  }

  for( int i=0; i<Q; i++)
  {
    int A = input.readInt();
    int B = input.readInt();
    int C = input.readInt();
    T.push_back( make_pair(make_pair(A, B), make_pair(C, i)));
    auxT.push_back(T[i]);
    auxT[i].F.F--;
    auxT[i].F.S--;
  }

  getResults();

  for( int i=0; i<Q; i++)
    output( results[i], "\n");
  return 0;
}
