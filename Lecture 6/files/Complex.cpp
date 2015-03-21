#include "Complex.h"
#include <iostream>
#include <iomanip>

class ComplexInt;
using namespace std;

int
main(){

  ComplexInt a(1,3), b(3,8);
  ComplexInt c;
  ComplexInt cpb(5 + 3_i);
  5 + 3_i;

  cout<<c<<endl;
  cout<<a<<endl;
  cout<<b<<endl;

  cout<<(a+b)<<endl;
  cout<<a*b<<endl; 
  cout << 5 + 3_i << endl;

	ComplexInt ci(2, 7); // 2 + 7i
	cout << "12345678901234567890123456789" << endl;
	cout << setw(10) << ci << endl;
	
  return 0;
}
