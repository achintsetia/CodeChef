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

#define MAX 10000001
int passwords[350][350];
int flags[350][350];
int visited[350][350];

int primes[MAX][2];

void gridMechanism( int i, int j, int N, int index)
{
  visited[i][j] = true;

  if( i>0 && flags[i-1][j] == index && visited[i-1][j] == false)
    gridMechanism(i-1, j, N, index);

  if( i<N-1 && flags[i+1][j] == index && visited[i+1][j] == false)
    gridMechanism(i+1, j, N, index);

  if( j>0 && flags[i][j-1] == index && visited[i][j-1] == false)
    gridMechanism(i, j-1, N, index);

  if( j<N-1 && flags[i][j+1] == index && visited[i][j+1] == false)
    gridMechanism(i, j+1, N, index);
}

int main( int argc, char** argv)
{
  int T = input.readInt();


  //generate all primes and their unsucessful trials
  for(int i=0; i<MAX; i++) primes[i][0] = 1;
  for(int i=2; i<=3163; i++)
    if (primes[i][0])
      for(int j=i; j*i<MAX; j++) primes[i*j][0] = 0;

  primes[0][0] = 0;
  primes[1][0] = 0;
  int count = 0;
  for(int i=2; i<MAX; i++)
    if( primes[i][0] == 1)
      primes[i][1] = count++;

  while( T--)
  {
    int N = input.readInt();

    for( int i=0; i<N; i++)
      for( int j=0; j<N; j++)
      {
        passwords[i][j] = input.readInt();
        visited[i][j] = false;
        if( primes[passwords[i][j]][0] == 1)
          flags[i][j] = 0;
        else if( passwords[i][j] % 2 == 0)
          flags[i][j] = 1;
        else
          flags[i][j] = 2;
      }
#if 0
    cout << "Flags: " << endl;
    for( int i=0; i<N; i++)
    {
      for( int j=0; j<N; j++)
        cout << flags[i][j] << " ";
      cout << endl;
    }
#endif
    long long int trials = 0;
    //cout << "counts: " << endl;

    for( int i=0; i<N; i++)
    {
      for( int j=0; j<N; j++)
      {
        int num = 0;
        if( flags[i][j] == 0) // The password is prime
        {
          trials += primes[passwords[i][j]][1];
          visited[i][j] = true;
          //num += primes[passwords[i][j]][1];
        }
        else
        {
          if( visited[i][j] == false)
          {
            if( flags[i][j] == 1)
            {
              trials += passwords[i][j] / 2;
              gridMechanism(i, j, N, 1);
              //num = passwords[i][j] / 2;
            }
            else
            {
              trials += (passwords[i][j] + 3) /2;
              gridMechanism(i, j, N, 2);
              //num = (passwords[i][j] + 3) / 2;
            }
          }
        }
        //cout << num << " ";
      }
      //cout << endl;
    }
    printf( "%lld\n", trials);
  }
  return 0;
}
