
#ifndef VEC_H
#define VEC_H true

#include <vector>
#include <iostream>

using namespace std;

	/* Vec
	 *
	 */


template< class T >
class Vec
{
  protected:
	vector<T> data;

  public:
	Vec(){}
	Vec(int n){ data.resize(n); }
    Vec<T>(const vector<T>& v){ data = v; }

	// show data
	virtual void show();

	// get row vec
	vector<T>& getVec(){ return data; }

	// add element
	void add(T val){ data.push_back(val); }

	// read-only at[]
	T operator[](int idx) const { return data[idx]; }

	// checkDimensions
	void checkDimensions( int N, const char* file, int line );

	// get length of row
	int getLength() const { return data.size(); }

};


template <class T>
void Vec<T>::show()
{
	for(auto i : data)
	{
		cout << ' ' << i;
	}
	cout << endl << endl;
}


template <class T>
void Vec<T>::checkDimensions( int N, const char* file, int line )
{
	if ( N != data.size() )
	{
		cout << "Dimension mismatch! "
			 << data.size() << " != " << N << endl
			 << '\t' << file << ':' << line << endl;
	}
}


#endif // VEC_H
