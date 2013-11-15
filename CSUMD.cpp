#include <iostream>
#include <string.h>
#include <math.h>
#include <stdlib.h>

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
        const Matrix< T > operator^( int P );

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
      if( C.data[i*C.n+j] > 1000000007)
        C.data[i*C.n+j] %= 1000000007;
    }
  return C;
}

template< class T >
const Matrix< T > Matrix< T >::operator^( int P )
{
    if( P == 1 ) return (*this);
    if( P & 1 ) return (*this) * ((*this) ^ (P-1));
    Matrix B = (*this) ^ (P/2);
    Matrix C = B*B;
    return C;
}

int main( int argc, char** argv)
{
  int t;
  cin >> t;
  int N;

  for( int i=0; i<t; i++)
  {
    cin >> N;
    if( N == 1)
      cout << 1 << endl;
    else if( N == 2)
      cout << 3 << endl;
    else
    {
      Matrix<unsigned long long int> M(2,2);
      M.data[0] = 2; M.data[1] = 2;
      M.data[2] = 1; M.data[3] = 0;

      M = M^(N-2);
      cout << (M.data[0] * 3 + M.data[1]) % 1000000007 << endl;
    }
  }
  return 0;
}
