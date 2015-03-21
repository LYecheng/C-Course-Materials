#include "async_accumulate_function.h"
#include <boost/progress.hpp>

#include <iostream>
using std::cout;
using std::endl;
using namespace mpcs51044;

int main()
{
	
  // std::vector<int> v; // Slower because needs to grow
  std::vector<int> v(50000000);
  for (int i = 0; i < 50000000; i++) {
    v.push_back(i);
  }
  {
    cout << "std::accumulate" << endl;
    boost::progress_timer tmr;
    cout << std::accumulate(v.begin(), v.end(), 0LL) << endl;
  }
  {
    cout << "async_accumulate with hw concurrency of " << std::thread::hardware_concurrency() << endl;
    boost::progress_timer tmr;
    cout << async_accumulate(v.begin(), v.end(), 0LL) << endl;
  }
}
