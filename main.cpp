#include "Matrix.h"
#include "MatrixTypes.h"
#include "Operations.h"

int main()
{

	vector<double> mat = { 1, 0, 0, 0,
						   0, 1, 0, 0,
						   0, 0, 1, 0,
					       0, 0, 0, 1 };

	Matrix2D<double> M(4,4,mat);

	LUdecomp<double> lu( 4, mat );
	lu.decompose();
	cout << lu.validate() << endl;

	cout << (M == lu) << endl;

}

