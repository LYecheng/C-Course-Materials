#include "Matrix.h"
#include <iostream>
#include <stdexcept>
#include <boost/progress.hpp>
using namespace mpcs51044;
using namespace std;

int main()
{
	boost::progress_timer howlong;
    try {
#if 0
      Matrix<3, 4> m = {
          { 1, 2, 3, 5 },
          { 4, 5, 6, 7 },
          { 7, 8, 9, 8 }
      };
#else
      Matrix<3, 3> m = {
          { 1, 2, 3, 4 },
          { 4, 5, 6 },
          { 7, 8, 9 }
      };
#endif
      static double total;
      for (int i = 0; i < 10000000; i++) {
        m(1, 1) = i;
        total += m.determinant();
      }
      cout << total << endl;
    } catch (exception const &e) {
      cout << "Exception: " << e.what() << endl;
    }
}