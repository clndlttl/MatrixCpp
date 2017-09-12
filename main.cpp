#include "Matrix.h"


int main()
{
	vector<int> m = {1,2,3,4,5,6,7,8,9};

	Row<int> R(m);	
	Column<int> C(m);

	Row<int> R2 = R*2;
	Column<int> C2 = C*3;

	R2.show();
	C2.show();

}
