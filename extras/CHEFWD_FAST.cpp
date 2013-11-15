#include <iostream>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define mod 1000000007

using namespace std;

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

int main( int argc, char** argv)
{
  int T;
  scanf( "%d", &T);
  long long int N;

  while( T--)
  {
    scanf( "%lld", &N);

    if( N == 1)
      printf( "0\n");
    else if( N == 2)
      printf( "5\n");
    else if( N == 3)
      printf( "18\n");
    else if( N == 4)
      printf( "44\n");
    else
    {
      Matrix<long long int> M(4,4);
      M.data[0] = 1; M.data[1] = 1; M.data[2] = 1; M.data[3] = 1;
      M.data[4] = 1; M.data[5] = 0; M.data[6] = 0; M.data[7] = 0;
      M.data[8] = 0; M.data[9] = 0; M.data[10] = 1; M.data[11] = 1;
      M.data[12] = 0; M.data[13] = 0; M.data[14] = 1; M.data[15] = 0;

      M = M^(N-4);

      for( int i=0; i<4; i++)
      {
        for( int j=0; j<4; j++)
          cout << M.data[i*4+j] << " ";
        cout << endl;
      }

      long long int sum = (M.data[0]*44) % mod;
      sum = (sum + (M.data[1]*18) % mod) % mod;
      sum = (sum + (M.data[2]*21) % mod) % mod;
      sum = (sum + (M.data[3]*13) % mod) % mod;

      printf( "%d\n", (int) sum);
    }
  }
  return 0;
}
