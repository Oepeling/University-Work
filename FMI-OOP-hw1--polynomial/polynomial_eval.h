#pragma once

#include <iostream>
#include <fstream>

#include "polynomial.h"

class polynomial_eval{
private:
	polynomial<double> P;
	double X;

public:
	polynomial_eval(){
		X = 0;
	}

	polynomial_eval(const polynomial<double>& a, const double& b){
		P = a;
		X = b;
	}

	polynomial_eval(const polynomial_eval& a){
		P = a.P;
		X = a.X;
	}

	bool is_root(){
		return (P(X) == 0);
	}

	friend std::istream& operator >> (std::istream& in, polynomial_eval& p);
	friend std::ostream& operator << (std::ostream& out, const polynomial_eval p);
};

std::istream& operator >> (std::istream& in, polynomial_eval& p){
	in >> p.P >> p.X;
	return in;
}

std::ostream& operator << (std::ostream& out, const polynomial_eval p){
	out << p.P << std::endl << p.X;
	return out;
}
