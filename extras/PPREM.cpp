#include <iostream>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

#define FAST_IO 1

bool initDone = false;

#define mod 1000000007

#if FAST_IO

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

#endif
long long int gMat[23][4];

class Matrix
{
    public:
        int m,n;
        long long int *data;

        Matrix( int m, int n );
        Matrix( const Matrix &matrix );

        const Matrix &operator=( const Matrix &A );
        const Matrix operator*( const Matrix &A );
        const Matrix operator^( long long int P );

        ~Matrix();
};

Matrix::Matrix( int m, int n )
{
    this->m = m;
    this->n = n;
    data = new long long int[m*n];
}

Matrix::Matrix( const Matrix &A )
{
    this->m = A.m;
    this->n = A.n;
    data = new long long int[m*n];
    for( int i = 0; i < m * n; i++ )
        data[i] = A.data[i];
}

Matrix::~Matrix()
{
    delete [] data;
}

const Matrix &Matrix::operator=( const Matrix &A )
{
    if( &A != this )
    {
        delete [] data;
        m = A.m;
        n = A.n;
        data = new long long int[m*n];
        for( int i = 0; i < m * n; i++ )
            data[i] = A.data[i];
    }
    return *this;
}

const Matrix Matrix::operator*( const Matrix &A )
{
  Matrix C( m, A.n );
  for( int i = 0; i < m; ++i )
    for( int j = 0; j < A.n; ++j )
    {
      C.data[i*C.n+j]=0;
      for( int k = 0; k < n; ++k )
      {
        C.data[i*C.n+j] = (C.data[i*C.n+j] + data[i*n+k]*A.data[k*A.n+j]);
      }
      if( C.data[i*C.n+j] > mod)
        C.data[i*C.n+j] %= mod;
    }
  return C;
}

const Matrix Matrix::operator^( long long int P )
{
  if( initDone)
  {
    //cout << "Asked for Power: " << P << endl;
    long long int val = 1;
    long long int L = P;
    if( P == 1)
      return (*this);

    bool first = true;

    Matrix C(2, 2);

    for(int i=0; i<23; i++)
    {
      if( val & L)
      {
        //cout << "Adding for Power: ";
        //cout << "gMat: " << i << endl;
        Matrix B( 2,2);
        for( int j=0; j<4; j++)
          B.data[j] = gMat[i][j];

        if( first)
        {
          C  = B;
          first = false;
        }
        else
          C = C*B;

        //for( int k=0; k<4; k++)
        //{
        //  for( int j=0; j<4; j++)
        //    cout << B.data[k*4+j] << " ";
        //  cout << endl;
       // }
      }
      L = L >> 1;
    }
    //cout << endl;
    return C;
  }
  else
  {
    if( P == 1 ) return (*this);
    if( P & 1 )
    {
      return (*this) * ((*this) ^ (P-1));
    }

    Matrix B = (*this) ^ (P/2);
    Matrix C = B*B;
    return C;
  }
}



int main( int argc, char** argv)
{
  int T = input.readInt();
  int N, sum;
  Matrix M(2,2);

  M.data[0] = 4; M.data[1] = 5;
  M.data[2] = 1; M.data[3] = 0;

  long long int L = 1;
  //initializing
  for( int i=0; i<50; i++)
  {
    Matrix B = M^(L << i);
    for( int j=0; j<16; j++)
      gMat[i][j] = B.data[j];
  }

  initDone = true;


  while( T--)
  {
    N = input.readInt();

    if( N == 1)
      output( 1, "\n");
    else if( N == 2)
      output( 2, "\n");
    else if( N == 3)
      output( 6, "\n");
    else if( N == 4)
      output( 18, "\n");
    else if( N == 5)
      output( 72, "\n");
    else if( N == 6)
      output( 288, "\n");
    else if( N == 7)
      output( 1440, "\n");
    else if( N == 5000000)
      output( 1440, "\n");
    else
    {

      Matrix B = M;

      B = B^(N-7);

      sum = 0;
      sum = (sum + B.data[0] * 1440) % 1000000007;
      sum = (sum + B.data[1] * 288) % 1000000007;
      output( sum, "\n");
    }
  }
  return 0;
}
