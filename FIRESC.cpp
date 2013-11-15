#include <iostream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>
#include <map>

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

class UnionFind //Doesn't do path compression
{
  public :
    UnionFind(int N);
    ~UnionFind();
    int count();
    int find(int p);
    bool connected( int p, int q);
    void Union( int p, int q);
    int* id;    // id[i] = parent of i
    int* sz;    // sz[i] = number of objects in subtree rooted at i
    int components;   // number of components
};

// Create an empty Union find data structure with N isolated sets.
UnionFind :: UnionFind(int N)
{
  components = N;
  id = new int[N];
  sz = new int[N];
  for (int i = 0; i < N; i++)
  {
    id[i] = i;
    sz[i] = 1;
  }
}

UnionFind :: ~UnionFind()
{
  delete[] id;
  delete[] sz;
}

// Return the number of disjoint sets.
int UnionFind :: count()
{
  return components;
}

// Return component identifier for component containing p
int UnionFind :: find(int p)
{
  while (p != id[p])
    p = id[p];
  return p;
}

// Are objects p and q in the same set?
bool UnionFind :: connected(int p, int q)
{
  return find(p) == find(q);
}

// Replace sets containing p and q with their Union.
void UnionFind :: Union(int p, int q)
{
  int i = find(p);
  int j = find(q);
  if (i == j) return;

  // make smaller root point to larger one
  if   (sz[i] < sz[j]) { id[i] = j; sz[j] += sz[i]; }
  else                 { id[j] = i; sz[i] += sz[j]; }
  components--;
}

#define MOD 1000000007;

int main( int argc, char** argv)
{
  int T = input.readInt();

  while( T--)
  {
    int N = input.readInt();
    int M = input.readInt();
    int numGates = 0;

    UnionFind* ufObj = new UnionFind( N);
    map<int, int> hash;

    for( int i=0; i<M; i++)
      ufObj->Union( input.readInt()-1, input.readInt()-1);

    numGates = ufObj->count();

    for( int i=0; i<N; i++)
    {
      ufObj->id[i] = ufObj->find( i);
      hash[ ufObj->id[i]] = 0;
      //cout << ufObj->id[i] << " ";
    }
    //cout << endl;

    for( int i=0; i<N; i++)
      hash[ ufObj->id[i]]++;

    long long int numWays = 1;

    map<int, int>::iterator it;
    for( it = hash.begin(); it != hash.end(); it++)
      numWays = (numWays * it->second) % MOD;

    output( numGates, " ", (int) numWays, "\n");
    delete ufObj;
  }
  return 0;
}


