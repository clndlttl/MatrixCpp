#include "Matrix.h"
#include "MatrixTypes.h"
#include "Operations.h"

int main()
{

	vector<double> mat = { 1, -3,
						   4, -2 };

	Matrix2D<double> M(2,2,mat);

	LUdecomp<double> lu( 2, mat );
	lu.decompose();
	lu.show();

}

