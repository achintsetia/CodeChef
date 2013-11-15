#include <iostream>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

using namespace std;

#define mod 1000000007

template< class T >
class Matrix
{
    public:
        int m,n;
        T *data;

        Matrix( int m, int n );
        Matrix( const Matrix< T > &matrix );

        const Matrix< T > &operator=( const Matrix< T > &A );
        const Matrix< T > operator*( const Matrix< T > &A );
        const Matrix< T > operator^( long long int P );

        ~Matrix();
};

template< class T >
Matrix< T >::Matrix( int m, int n )
{
    this->m = m;
    this->n = n;
    data = new T[m*n];
}

template< class T >
Matrix< T >::Matrix( const Matrix< T > &A )
{
    this->m = A.m;
    this->n = A.n;
    data = new T[m*n];
    for( int i = 0; i < m * n; i++ )
        data[i] = A.data[i];
}

template< class T >
Matrix< T >::~Matrix()
{
    delete [] data;
}

template< class T >
const Matrix< T > &Matrix< T >::operator=( const Matrix< T > &A )
{
    if( &A != this )
    {
        delete [] data;
        m = A.m;
        n = A.n;
        data = new T[m*n];
        for( int i = 0; i < m * n; i++ )
            data[i] = A.data[i];
    }
    return *this;
}

template< class T >
const Matrix< T > Matrix< T >::operator*( const Matrix< T > &A )
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

template< class T >
const Matrix< T > Matrix< T >::operator^( long long int P )
{
    if( P == 1 ) return (*this);
    if( P & 1 ) return (*this) * ((*this) ^ (P-1));
    Matrix B = (*this) ^ (P/2);
    Matrix C = B*B;
    return C;
}

long long int newPow( unsigned int base, unsigned long long int exponent)
{
  if( exponent == 0)
    return 1;
  else if( exponent % 2 == 0)
  {
    long long int half_pow = newPow(base, exponent / 2) % mod;
    half_pow *= half_pow % mod;
    return half_pow % mod;
  }
  else return (base * newPow(base, exponent - 1)) % mod;
}

int main( int argc, char** argv )
{
  int T;
  long long int N;

  scanf( "%d", &T);

  long long int sum = 0;

  while( T--)
  {
    scanf( "%lld", &N);
    sum = 0;

    if( N <= 2)
      cout << 0 << endl;
    else if( N == 3)
      cout << 1 << endl;
    else if( N == 4)
      cout << 3 << endl;
    else if( N == 5)
      cout << 8 << endl;
    else
    {

      sum = 0;
      Matrix<long long int> M(3, 3);
      M.data[0] = 1; M.data[1] = 1; M.data[2] = 1;
      M.data[3] = 1; M.data[4] = 0; M.data[5] = 0;
      M.data[6] = 0; M.data[7] = 1; M.data[8] = 0;

      M = M^(N-5);

      //for( int i=0; i<3; i++)
      //{
      //  for( int j=0; j<3; j++)
      //    cout << M.data[i*3+j] << " ";
      //  cout << endl;
      //}

      sum = ( newPow( 2, N)  - (M.data[0] * 24 + M.data[1] * 13 + M.data[2] * 7)) % mod;

      if( sum < 0)
        printf( "%d\n", (int) (mod + sum));
      else
        printf( "%d\n", (int) sum);
    }
  }
}

