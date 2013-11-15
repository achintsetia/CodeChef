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

int matrix[300][300];

int rowsSel[300];
int colsSel[300];

int optRs[300];
int optCs[300];

long long int positiveSum;

long long int sum;

class Point
{
  public :
    Point( int a, int b, int c){ x =a; y = b; val = c;}
    int x;
    int y;
    int val;
};

vector<Point> posPoints;

struct myclass
{
  bool operator() (Point a, Point b) { return (a.val > b.val);}
} pointComp;

int optRSize, optCSize;
long long int totalSum;

void showSelStatus( int H, int W)
{
  cout << "SelStatus : Rows: ";
  for( int i=0; i<H; i++)
    cout << rowsSel[i] << " ";

  cout << "Cols: ";
  for( int i=0; i<W; i++)
    cout << colsSel[i] << " ";
  cout << endl;

  cout << "OptStatus: Rows: ";
  for( int i=0; i<optRSize; i++)
    cout << optRs[i] << " ";

  cout << "Cols: ";
  for( int i=0; i<optCSize; i++)
    cout << optCs[i] << " ";
  cout << endl;
}

void checkAndSelect( int x, int y, int H, int W)
{
  if( rowsSel[x] == 1 && colsSel[y] == 1)
    return;
  else if( rowsSel[x] == 1)
  {
    sum = 0;
    for( int i=0; i<optRSize; i++)
      sum += matrix[optRs[i]][y];

    if( sum > 0)
    {
      optCs[optCSize++] = y;
      totalSum += sum;
      colsSel[y] = 1;
    }
  }
  else if( colsSel[y] == 1)
  {
    sum = 0;
    for( int j=0; j<optCSize; j++)
      sum += matrix[x][optCs[j]];

    if( sum > 0)
    {
      optRs[optRSize++] = x;
      totalSum += sum;
      rowsSel[x] = 1;
    }
  }
  else
  {
    sum = 0;
    for( int i=0; i<optRSize; i++)
      sum += matrix[optRs[i]][y];

    for( int j=0; j<optCSize; j++)
      sum += matrix[x][optCs[j]];

    sum += matrix[x][y];

    if( sum > 0)
    {
      totalSum += sum;
      optRs[optRSize++] = x;
      optCs[optCSize++] = y;
      colsSel[y] = 1;
      rowsSel[x] = 1;
    }
  }
}

int main( int argc, char** argv)
{
  int H = input.readInt();
  int W = input.readInt();

  posPoints.reserve( H*W);
  positiveSum = 0;

  for( int i=0; i<H; i++) rowsSel[i] = 0;

  for( int j=0; j<W; j++) colsSel[j] = 0;

  for( int i=0; i<H; i++)
    for( int j=0; j<W; j++)
    {
      matrix[i][j] = input.readInt();
      if( matrix[i][j] > 0)
      {
        positiveSum += matrix[i][j];
        posPoints.push_back( Point( i, j, matrix[i][j]));
      }
    }

  int pSize = posPoints.size();

  sort( posPoints.begin(), posPoints.begin()+pSize, pointComp);

  int startFrom = 2;

  rowsSel[posPoints[startFrom].x] = 1;
  colsSel[posPoints[startFrom].y] = 1;

  totalSum = posPoints[startFrom].val;

  optRSize = 0;
  optCSize = 0;

  optRs[optRSize++] = posPoints[startFrom].x;
  optCs[optCSize++] = posPoints[startFrom].y;

  for( int i=0; i<pSize; i++)
    checkAndSelect( posPoints[i].x, posPoints[i].y, H, W);

  sort( optRs, optRs+optRSize);
  sort( optCs, optCs+optCSize);

  output( optRSize, " ", optCSize, "\n");
  for( int i=0; i<optRSize; i++)
    output( optRs[i], " ");
  output("\n");

  for( int j=0; j<optCSize; j++)
    output( optCs[j], " ");
  output("\n");

  return 0;
}
