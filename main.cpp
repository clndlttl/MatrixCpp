#include "VectorTypes.h"
#include "MatrixTypes.h"

using namespace std;

int main()
{
	using T = double;

	vector<T> y_val = { -3.6, -2.7, -1.2, 0.5, 1.7, 1.9, 3.7, 4.1, 6.0 };
	Column<T> y_col( y_val );

	vector<T> x_val = { -3.2, -2.8, -1.5, 0.4, 1.3, 2.6, 3.2, 4.4, 5.8 };

	Ones<T> offset( 9 );

	Matrix2D<T> A;
	A.addRow( x_val );
	A.addRow( offset );
	A = A.t();

	Square<T> A2 = A.t() * A;

	Column<T> m_and_b = ( A2.inv() * A.t() ) * y_col;
	m_and_b.show();
}

