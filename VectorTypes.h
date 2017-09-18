
#ifndef VECTORTYPES_H
#define VECTORTYPES_H true

#include <vector>
#include "Row.h"
#include "Column.h"

using namespace std;

	/* Ones
 	 *
 	 */


template< class T >
class Ones : public Row<T>
{

  public:
	Ones<T>( int size )
	{
		this->data = vector<T>( size, static_cast<T>(1) );
	}

};


#endif // ROW_H

