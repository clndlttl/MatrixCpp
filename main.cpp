#include "Matrix.h"


int main()
{

	vector<int> row = {1,2,-3};
	vector<int> col = {4,-5,6};
	vector<int> mat = { 1,0,0,
					    0,1,0,
					    0,0,1 };

	Row<int> r(row);
	Column<int> c(col);
	Matrix2D<int> M(3,3,mat);

	Matrix2D<int> M2( 5, 5 );

	Matrix2D<int> res = M2^2;
 
	res.show();

}
