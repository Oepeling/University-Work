#include <fstream>
#include "polynomial.h"
// #include "vector.h"

std::ifstream cin("test2.in");
std::ofstream cout("test2.out");

int main(){
	vector<polynomial<double>> v;
	int n; cin >> n;

	for(int i = 0; i < n; i++){
		polynomial<double> a; cin >> a;
		v.push_back(a);
	}

	double root; cin >> root;

	for(int i = 0; i < n; i++){
		if (polynomial_eval(v[i], root).is_root())
			cout << root << " este radacina a polinomului " << v[i] << std::endl;
		else cout << root << " nu este radacina a polinomului " << v[i] << std::endl;
	}

	return 0;
}