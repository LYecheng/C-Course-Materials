#ifndef D_COMPLEX_HEADER
#define D_COMPLEX_HEADER 1

#include <ostream>
#include <iostream>


class ComplexInt{
	public:
		ComplexInt():re(0), im(0){}
		ComplexInt(int r):re(r), im(0){}
		ComplexInt(int r, int i):re(r),im(i){}
		ComplexInt(ComplexInt const &c){
			re = c.re;
			im = c.im;
		}

		ComplexInt&
			operator=(ComplexInt const &c){
				if(this != &c){
					re = c.re;
					im = c.im;
				}
				return *this;
			}

		int Real() const{
			return re;
		}

		int Imag() const{
			return im;
		}

		inline friend
			std::ostream&
			operator<<(std::ostream &os, ComplexInt const &a){
				os << a.re << "+" << a.im <<"i"; 
				return os;
			}

	private:
		int re;
		int im;

};

ComplexInt
operator+(ComplexInt const& cl, ComplexInt const& cr){
	return ComplexInt(cl.Real()+cr.Real(), cl.Imag()+cr.Imag());
}

ComplexInt
operator*(ComplexInt const& cl, ComplexInt const& cr){
	return ComplexInt(cl.Real()*cr.Real()-cl.Imag()*cr.Imag(),cl.Real()*cr.Imag()+cl.Imag()*cr.Real());
}

ComplexInt operator "" _i(unsigned long long x){
	return ComplexInt(0, x);
}

#endif  // D_COMPLEX_HEADER
