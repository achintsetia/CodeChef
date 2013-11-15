#include <iostream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <list>
#include <algorithm>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;

// scanfs
#define SUL(x) scanf("%lu", &x)
#define SLL(x) scanf("%lld", &x)
#define SULL(x) scanf("%llu", &x)

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
  unsigned readUnsigned();
  int readInt();
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

unsigned INPUT::readUnsigned() {
  skipWS();
  unsigned res = 0;
  while(!eof() && isdigit(nextChar())) {
    res = 10u * res + (readChar()-'0');
  }
  return res;
}

int INPUT::readInt() {
  skipWS();
  bool neg = false;
  if(!eof() && nextChar()=='-') { neg=true; readChar(); }
  int res = static_cast<int>(readUnsigned());
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

struct intPoint
{
  int val;
  int diff;
  int pair;
};

int size;
int maxVal, minVal;

void printList( list<intPoint> mylist)
{
  list<intPoint>::iterator it = mylist.begin();
  cout << "NULL-";
  for( it = mylist.begin();   it != mylist.end(); it++)
    cout << "-|" << (*it).val << "|" << (*it).diff << "|-";
  cout << "-NULL" << endl;
}

void insert( list<intPoint>& mylist, int x, int y, int z, int N)
{
  if( mylist.empty())
  {
    intPoint temp;
    temp.val = 1;
    temp.diff = 0;
    temp.pair = N;
    mylist.push_back(temp);

    temp.val = N;
    temp.diff = 0;
    temp.pair = 1;
    mylist.push_back(temp);

    minVal = 1;
    maxVal = N;
  }
  else
  {
    list<intPoint>::iterator it = mylist.begin();
    while( it != mylist.end() && (*it).val < x)
      it++;

    list<intPoint>::iterator leftP = it;
    //cout << "leftP point to: " << (*it).val << endl;

    intPoint newLP, newRP;

    newLP.val = x;
    newLP.pair = y;
    if( leftP != mylist.begin())
    {
      leftP--;
      if( (*leftP).pair >= x)
        newLP.diff = z + (*leftP).diff;
      else
        newLP.diff = z;
      leftP++;
    }
    else
      newLP.diff = z;

    mylist.insert( leftP, newLP);
    //cout << "After insert leftP point to: " << (*it).val << endl;

    while( it != mylist.end() && (*it).val < y)
        it++;

    list<intPoint>::iterator rightP = it;
    //cout << "rightP point to: " << (*rightP).val << endl;

    if( rightP == leftP)
    {
      newRP.val = y;
      newRP.diff = newLP.diff;
      newRP.pair = x;
      mylist.insert( rightP, newRP);
    }
    else
    {
      newRP.val = y;
      rightP--;
      if( (*rightP).pair >= y)
        newRP.diff = z + (*rightP).diff;
      else
      newRP.diff = z;
      newRP.pair = x;
      rightP++;
      mylist.insert( rightP, newRP);
    }
    while( leftP != mylist.end())
    {
      if( (*leftP).val < y && (*leftP).val != x)
      {
        (*leftP).diff += z;
        //cout << "Increasin: " << (*leftP).val << " by: " << z << endl;
        leftP++;
      }
      else
        break;
    }

  }
  //printList( mylist);
}

int findRange( list<intPoint> mylist)
{
  list<intPoint>::iterator it = mylist.begin();
  list<intPoint>::iterator prev = it;
  maxVal = (*it).val + (*it).diff;
  minVal = (*it).val + (*it).diff;

  it++;
  for( ;   it != mylist.end(); it++)
  {
    if( (*prev).val == (*it).val)
      (*it).diff += (*prev).diff;

    if( (*it).val + (*it).diff > maxVal)
      maxVal = (*it).val + (*it).diff;

    if( (*it).val + (*it).diff < minVal)
      minVal = (*it).val + (*it).diff;

    //cout << maxVal << " " << minVal << endl;
    prev++;
  }
  return maxVal - minVal;
}

int main( int argc, char** argv)
{
  int T, N, M, w, x, y, z;

  T = input.readInt();

  while(T--)
  {
    list<intPoint> mylist;
    N = input.readInt();
    M = input.readInt();

    if( N == 1)
    {
      while(M--)
      {
        w = input.readInt();
        x = input.readInt();
        y = input.readInt();
        z = input.readInt();
      }
      output( 0, "\n");
      continue;
    }

    size = 0;
    insert( mylist, 1, N, 1, N);
    maxVal  = 0;
    minVal  = 1000;

    while(M--)
    {
      w = input.readInt();
      x = input.readInt();
      y = input.readInt();
      z = input.readInt();
#if 0
      if( x > 1 && y<N)
        insert( x-1, y+1, 0, N);
      else if( x == 1 && y<N)
        insert( x, y+1, 0, N);
      else if( y == N && x>1)
        insert( x-1, y, 0, N);
#endif
      if( w == 1)
        insert( mylist, x, y, z, N);
      else
        insert( mylist, x, y, -z, N);
    }

    output( findRange( mylist), "\n");
  }
  return 0;
}
