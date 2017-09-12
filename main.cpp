#include "Matrix.h"


int main()
{
	vector<int> m = {1,2,3,4,5,6,7,8,9};
	
	Row<int> R(m);

	auto R2 = R*5;
	R2.show();

}
