#include "VectorTypes.h"
#include "MatrixTypes.h"

using namespace std;

template <class T>
class KalmanFilter
{
public:

	// multiple meas
	KalmanFilter( Square<T>& A_in, Matrix2D<T>& H_in, 
				  Square<T>& Q_in, Square<T>& R_in, 
				  Square<T>& P_in,
				  Column<T>& x_in )
	{
		Eye<T> tmp( A_in.getNumRows() );
		I = tmp;

		A = A_in;
		H = H_in;

		Q = Q_in;
		R = R_in;

		P = P_in;
		x_est = x_in;
	}

	// single meas
	KalmanFilter( Square<T>& A_in, Row<T>& h_in, 
				  Square<T>& Q_in, T& r_in, 
				  Square<T>& P_in,
				  Column<T>& x_in )
	{
		Eye<T> tmp( A_in.getNumRows() );
		I = tmp;

		A = A_in;
		h = h_in;

		Q = Q_in;
		r = r_in;

		P = P_in;
		x_est = x_in;
	}

	// multiple meas
	void advance( Column<T>& z )
	{
		K = P*H.t()*( H*P*H.t() + R )^(-1);
		x_new = x_est + K*( z - H*x_est );

		x_new.show();

		P = ( I - K*H ) * P;
		x_est = A * x_new;
		P = A * P * A.t() + Q;
		
	}

	// single meas
	void advance( T z )
	{
		k = P*h.t()*( 1.0 / (h*P*h.t() + r ));
		x_new = x_est + k*( z - h*x_est );

		x_new.show();

		P = ( I - k*h ) * P;
		x_est = A * x_new;
		P = A * P * A.t() + Q;
	}

private:
	
	Eye<T> I;
	Matrix2D<T> A;

	Row<T> h;
	Matrix2D<T> H;

	T r;
	Matrix2D<T> R;
	Matrix2D<T> Q;

	Column<T> k;
	Matrix2D<T> K; 

	Matrix2D<T> P;
	Column<T> x_est;

	Column<T> x_new;
};

