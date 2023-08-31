#include <fstream>
#include <iostream>
#include <algorithm>

#include "polynomial.h"
#include "vector.h"

std::ifstream in("test2.in");
std::ofstream out("test2.out");

int main(){
	vector<polynomial<double>> v;
	int n; in >> n;

	for(int i = 0; i < n; i++){
		polynomial<double> a; in >> a;
		v.push_back(a);
	}

	std::sort(v.begin(), v.end());

	for(vector<polynomial<double>>::iterator it = v.begin(); it != v.end(); it++){
		out << (*it) << '\n';
	}

	return 0;
}