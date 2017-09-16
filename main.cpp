#include "Matrix.h"
#include "MatrixTypes.h"
#include "Operations.h"

int main()
{

	vector<double> row = {1,2,-3};
	vector<double> col = {4,-5,6};
	vector<double> mat = { 1,2,-3,
					       4,-1,6,
					       -2,0,1 };

	Row<double> r(row);
	Column<double> c(col);
	Matrix2D<double> M(3,3,mat);

	LUdecomp<double> lu( 3, mat );
	lu.decompose();
	lu.show(); // still shows input mat
}

