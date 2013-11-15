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

#define f first
#define s second

bool bpGraph[1001][1001];

bool bpm(int M, int N, int u, bool seen[], int matchR[])
{
  // Try every job one by one
  for (int v = 0; v < N; v++)
  {
    // If applicant u is interested in job v and v is
    // not visited
    if (bpGraph[u][v] && !seen[v])
    {
      seen[v] = true; // Mark v as visited

      // If job 'v' is not assigned to an applicant OR
      // previously assigned applicant for job v (which is matchR[v]) 
      // has an alternate job available. 
      // Since v is marked as visited in the above line, matchR[v] 
      // in the following recursive call will not get job 'v' again
      if (matchR[v] < 0 || bpm(M, N, matchR[v], seen, matchR))
      {
        matchR[v] = u;
        return true;
      }
    }
  }
  return false;
}

// Returns maximum number of matching from M to N
int maxBPM(int M, int N)
{
  // An array to keep track of the applicants assigned to
  // jobs. The value of matchR[i] is the applicant number
  // assigned to job i, the value -1 indicates nobody is
  // assigned.
  int matchR[N];

  // Initially all jobs are available
  memset(matchR, -1, sizeof(matchR));

  int result = 0; // Count of jobs assigned to applicants
  for (int u = 0; u < M; u++)
  {
    // Mark all jobs as not seen for next applicant.
    bool seen[N];
    memset(seen, 0, sizeof(seen));

    // Find if the applicant 'u' can get a job
    if (bpm(M, N, u, seen, matchR))
      result++;
  }
  return result;
}

int main( int argc, char** argv)
{
  int T = input.readInt();

  vector<pair<int, int> > points;

  while( T--)
  {
    map<int,int> mapX;
    map<int,int> mapY;

    points.clear();
    int N = input.readInt();
    int xCount = 0, yCount=0;
    for( int i=0; i<N; i++)
    {
      int X = input.readInt();
      int Y = input.readInt();
      if( mapX.find(X) == mapX.end()) mapX[X] = xCount++;
      if( mapY.find(Y) == mapY.end()) mapY[Y] = yCount++;
      points.push_back(make_pair(X,Y));
    }

    for( int i=0; i<xCount; i++)
      for( int j=0; j<yCount; j++)
        bpGraph[i][j] = false;

    for( int i=0; i<N; i++)
      bpGraph[mapX[points[i].f]][mapY[points[i].s]] = true;

#if 0
    for( int i=0; i<xCount; i++)
    {
      for( int j=0; j<yCount; j++)
        cout << bpGraph[i][j] << " ";
      cout << endl;
    }
#endif

    output( maxBPM(xCount, yCount), "\n");
  }
  return 0;
}
