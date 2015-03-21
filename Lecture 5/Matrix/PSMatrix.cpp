#include "PSMatrix.h"
#include <boost/progress.hpp>
using namespace mpcs51044;

int main()
{
	boost::progress_timer howlong;
	Matrix<double, 3, 3> m = { 
			{ 1, 2, 3 }, 
			{ 4, 5, 6 }, 
			{ 7, 8, 9 } 
	};
	static double total;
	for (int i = 0; i < 10000000; i++) {
		m(1, 1) = i;
		total += m.determinant();
	}
}