#include "Matrix.h"
#include "MatrixTypes.h"

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

	Eye<double> res( 5 );	
 
	res.show();

}
