#include <fstream>
#include <iostream>
#include <algorithm>

#include "polynomial.h"
#include "vector.h"
#include "polynomial_eval.h"

std::ifstream in("test2.in");
std::ofstream out("test2.out");

int main(){
	vector<polynomial<double>> v;
	int n; in >> n;

	for(int i = 0; i < n; i++){
		polynomial<double> a; in >> a;
		v.push_back(a);
	}

	double root; in >> root;

	std::sort(v.begin(), v.end());

	for(int i = 0; i < n; i++){
		if (polynomial_eval(v[i], root).is_root()){
			out << root << " este radacina a polinomului " << v[i] << std::endl;
			// std::cout << "X = " << root << " este radaina a polinomului " << v[i] << std::endl;
		}
		else {
			out << root << " nu este radacina a polinomului " << v[i] << std::endl;
			// std::cout << "X = " << root << " nu este radaina a polinomului " << v[i] << std::endl;
		}
	}

	return 0;
}