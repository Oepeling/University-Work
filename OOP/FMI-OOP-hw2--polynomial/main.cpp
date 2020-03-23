#include <fstream>
#include <iostream>
#include "polynomial.h"
// #include "polynomial_eval.h"

std::ifstream in("test.in");
std::ofstream out("test.out");

int main(){
try {
	// std::cerr << "##\n";
	polynomial<double> a;
	polynomial<double> b;
	in >> a >> b;

	// std::cerr << "##\n";

	// out << a << ' ' << b << std::endl;

	// std::cerr << "##\n";

	// polynomial<double> c = a / b;

	// std::cerr << "##\n";

	// polynomial<double> d = a % b;

	if (a / b * b + a % b == a) out << "DA\n";

	// std::cerr << "##\n";

	out << a + b << std::endl;
	// std::cerr << "##\n";

	out << a - b << std::endl;
	// std::cerr << "##\n";

	out << a * b << std::endl;
	// std::cerr << "##\n";

	// polynomial<double> c, d;

	// c = a / b;
	// std::cerr << "##\n";
	// d = a % b;
	// std::cerr << "##\n";

	// out << c << std::endl << d << std::endl;
	// std::cerr << "##\n";

	// out << b * c + d << std::endl;
	// std::cerr << "##\n";

	// out << a(3) << std::endl;
	// std::cerr << "##\n";

	// cout << polynomial_eval(a, 3) << std::endl;
	// cout << polynomial_eval(a, 3).is_root();


}
catch (const char* s){
	std::cerr << s << std::endl;
}

	return 0;
}
