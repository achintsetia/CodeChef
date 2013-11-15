#include <iostream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

#define FASTIO 1

#ifdef FASTIO
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

struct Job
{
  int start;
  int end;
  int profit;
};

int opt[2001];
int qArray[2001];
vector< Job> jobVec;

int hourCount[49];

struct myclass
{
  bool operator() (Job a, Job b) { return (a.end < b.end);}
} jobComp;

void computeQ( int N)
{
  for( int i=1; i<49; i++)
    hourCount[i] += hourCount[i-1];

  for( int j=0; j<N; j++)
    qArray[j] = hourCount[jobVec[j].start];
}

void showQ( int N)
{
  cout << "Q: ";
  for( int i=0; i<N; i++)
    cout << qArray[i] << " ";
  cout << endl;
  cout << endl;
}

int maxComp( int j)
{
  if( j == 0)
    opt[0] = 0;
  else if( opt[j] == -1)
  {
    opt[j] = 0;

    int a = jobVec[j].profit + maxComp( qArray[j]);
    int b = maxComp( j-1);
    opt[j] = a > b ? a : b;
  }
  return opt[j];
}


int main( int argc, char** argv)
{
  int T = input.readInt();

  int N, S, E, C;

  jobVec.reserve( 2000);

  Job nullJob;

  nullJob.start = 0;
  nullJob.end = 0;
  nullJob.profit = 0;


  while( T--)
  {
    jobVec.clear();
    jobVec.push_back( nullJob);
    for( int i=0; i<49; i++)
      hourCount[i] = 0;

    N = input.readInt();

    for( int i=0; i<N+1; i++)
    {
      qArray[i] = 0;
      opt[i] = -1;
    }

    for( int i=1; i<=N; i++)
    {
      S = input.readInt();
      E = input.readInt();
      C = input.readInt();

      hourCount[E] += 1;

      Job temp;

      temp.start = S;
      temp.end   = E;
      temp.profit = C;

      jobVec.push_back( temp);
    }

    sort( jobVec.begin(), jobVec.begin()+N+1, jobComp);
    computeQ( N+1);
#if 0
    cout << "Jobs: " << endl;
    for( int i=0; i<1+N; i++)
      cout<< jobVec[i].start << " " << jobVec[i].end << " " << jobVec[i].profit << endl;
    cout << endl;
    showQ( N+1);
#endif
    output( maxComp( N), "\n");
  }
  return 0;
}
