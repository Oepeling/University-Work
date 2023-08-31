#include <fstream>
#include "polynomial.h"

std::ifstream cin("test.in");
std::ofstream cout("test.out");

int main(){
try {
	polynomial<double> a;
	polynomial<double> b;
	cin >> a >> b;

	cout << a + b << std::endl;
	cout << a - b << std::endl;
	cout << a * b << std::endl;

	polynomial<double> c, d;

	c = a / b;
	d = a % b;

	cout << c << std::endl << d << std::endl;

	cout << b * c + d << std::endl;

	cout << a(3) << std::endl;

	cout << polynomial_eval(a, 3) << std::endl;
	cout << polynomial_eval(a, 3).is_root();
}
catch (const char* s){
	std::cerr << s << std::endl;
}

	return 0;
}
