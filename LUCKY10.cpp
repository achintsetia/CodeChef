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

int histA[10];
int histB[10];

void showHists()
{
  cout << "Hist A: ";
  for( int i=0; i<10; i++)
    cout << histA[i] << " ";
  cout << endl;
  cout << "Hist B: ";
  for( int i=0; i<10; i++)
    cout << histB[i] << " ";
  cout << endl;

}

int main( int argc, char** argv)
{
  int T = input.readInt();
  char c;
  int num7A, num4A, num7B, num4B;
  int num56A, num0123A;
  int num56B, num0123B;
  c = input.readChar();

  while( T--)
  {
    for( int i=0; i<10; i++)
    {
      histA[i] = 0;
      histB[i] = 0;
    }

    c = input.readChar();
    while( c != '\n')
    {
      histA[ (int) (c - '0')]++;
      c = input.readChar();
    }

    c = input.readChar();
    while( c != '\n')
    {
      histB[ (int) (c - '0')]++;
      c = input.readChar();
    }

    num56A = histA[5]+histA[6];
    num56B = histB[5]+histB[6];

    num0123A = histA[0]+histA[1]+histA[2]+histA[3];
    num0123B = histB[0]+histB[1]+histB[2]+histB[3];


    num7A = num56B;

    if( num7A < histA[7])
    {
      num7A += num0123B;
      if( num7A >= histA[7])
      {
        num0123B = num7A - histA[7];
        num7A = histA[7];
      }
      else
      {
        num0123B = 0;
        num7A += histB[4];
        if( num7A >= histA[7])
        {
          histB[4] = num7A - histA[7];
          num7A = histA[7];
        }
        else
          histB[4] = 0;

        if( num7A < histA[7])
        {
          num7A += histB[7];
          if( num7A >= histB[7])
          {
            histB[7] = num7A - histA[7];
            num7A = histA[7];
          }
          else
            histB[7] = 0;
        }
      }
    }
    else
      num7A = histA[7];

//////////////////
    num7B = num56A;

    if( num7B < histB[7])
    {
      num7B += num0123A;
      if( num7B >= histB[7])
      {
        num0123A = num7B - histB[7];
        num7B = histB[7];
      }
      else
      {
        num0123A = 0;
        num7B += histA[4];
        if( num7B >= histB[7])
        {
          histA[4] = num7B - histB[7];
          num7B = histB[7];
        }
        else
          histA[4] = 0;
      }
    }
    else
      num7B = histB[7];

    num4A = num0123B;

    if( num4A >= histA[4])
      num4A = histA[4];
    else
    {
      num4A += histB[4];
      if( num4A >= histB[4])
      {
        histB[4] = num4A - histA[4];
        num4A = histA[4];
      }
      else
        histB[4] = 0;
    }

    num4B = num0123A;

    if( num4B >= histB[4])
      num4B = histB[4];

    for( int i=0; i<num7A+num7B; i++)
      output( "7");
    for( int i=0; i<num4A+num4B; i++)
      output( "4");

    output( "\n");
  }
  return 0;
}
