#include "Matrix.h"
#include "Operations.h"

int main()
{

	vector<double> row = {1,2,-3};
	vector<double> col = {4,-5,6};
	vector<double> mat = { 1,0,0,
					    0,1,0,
					    0,0,1 };

	Row<double> r(row);
	Column<double> c(col);
	Matrix2D<double> M(3,3,mat);

	Matrix2D<double> M2( 5, 5 );

	Matrix2D<double> res = M2^2;
 
	res.show();

}
