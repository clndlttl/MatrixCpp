#include "VectorTypes.h"
#include "MatrixTypes.h"

using namespace std;

int main()
{
	using T = double;

	vector<T> mat = { 1, 0, 0, -3,
					  0, 1, -1, 0,
   					  -1, 0, 1, 0,
   					  0, 2, 0, 1 };

	Square<T> M( 4, mat );
	M.show();
	(M^-1).show();

	LU<T> lu( M );
	lu.show();
	cout << "valid " << lu.isValid() << endl;

	Square<T> Minv = lu.inv();
	Minv.show();

	Square<T> back = Minv.inv(); // not working
	back.show();
}

