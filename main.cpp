#include "VectorTypes.h"
#include "MatrixTypes.h"

#include "Kalman.h"

using namespace std;

int main()
{
	using T = double;

	vector<T> a = { 1, 0, 0, 0, 1, 0, 0, 0, 1 };
	vector<T> h = { 0.1, 0.2, 0.3 };

	vector<T> q = { 0.1, 0.0, 0.0, 0.1 };
	T r = 0.1;

	vector<T> p = { 1.0, 0.0, 0.0, 1.0 };
	vector<T> x = {1.0, 1.0, 1.0};

	Square<T> A( 3, a );
	Row<T> H( h );
	Square<T> Q( 3, q );
	Square<T> P( 3, p );
	Column<T> X( x );

	KalmanFilter<T> kf( A, H, Q, r, P, X );
	
}

