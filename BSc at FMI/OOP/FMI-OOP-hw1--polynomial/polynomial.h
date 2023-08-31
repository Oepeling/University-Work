#pragma once

#include <fstream>
#include <iostream>
#include <exception>
#include <sstream>

#include "vector.h"

const unsigned int& max(const unsigned int& a, const unsigned int& b){
	if (a > b) return a;
	else return b;
}

const unsigned int& min(const unsigned int& a, const unsigned int& b){
	if (a < b) return a;
	return b;
}

template<class type = double>
class polynomial{
private:
	vector<type> constants;

public:
	polynomial(unsigned int n = 0){
		constants.resize(n);
	}

	polynomial(const vector<type>& v){
		constants = v;
	}

	polynomial(unsigned int n, ...){
		va_list v;
		va_start(v, n);

		for(int i = 0; i <= n; i++)
			constants.push_back(va_arg(v, type));

		va_end(v);
	}

	polynomial(const polynomial<type>& x){
		(*this) = x;
	}

	~polynomial(){
		// constants.erase();
	}

	int degree() const { return (int) constants.size() - 1; }
	const unsigned int& size() const { return constants.size(); }
	void clear(){ constants.clear(); }
	void erase(){ constants.erase(); }

	void insert(type a){
		constants.push_back(a);
	}

	void insert(type a, unsigned int pos){
		if (pos >= constants.size())
			constants.resize(pos + 1);
		constants[pos] = a;
	}

	const polynomial<type>& operator = (const polynomial<type>& other) {
		constants = other.constants;
		return other;
	}

	type& operator [] (int pos) const{
		assert(pos < constants.size() && pos >= 0);
		return constants[pos];
	}

	polynomial<type> operator + (const polynomial<type>& other) const {
		polynomial<type> ans;
		unsigned int n = min(constants.size(), other.constants.size());

		for(unsigned int i = 0; i < n; i++)
			ans.insert(constants[i] + other.constants[i]);

		for(unsigned int i = n; i < constants.size(); i++)
			ans.insert(constants[i]);

		for(unsigned int i = n; i < other.constants.size(); i++)
			ans.insert(other.constants[i]);

		while(!ans.constants.empty() && ans.constants.back() == type())
			ans.constants.pop_back();

		return ans;
	}

	polynomial<type> operator - (const polynomial<type>& other) const {
		polynomial<type> ans;
		unsigned int n = min(size(), other.size());

		for(unsigned int i = 0; i < n; i++)
			ans.insert((*this)[i] - other[i]);

		for(unsigned int i = n; i < size(); i++)
			ans.insert((*this)[i]);

		for(unsigned int i = n; i < other.size(); i++)
			ans.insert(-other[i]);

		while(!ans.constants.empty() && ans.constants.back() == type())
			ans.constants.pop_back();

		return ans;
	}

	polynomial<type> operator * (const polynomial<type>& other) const{
		polynomial<type> ans;

		if (this -> size() == 0 || other.size() == 0)
			return ans;

		ans.constants.resize(this -> degree() + other.degree() + 1);

		for(unsigned int i = 0; i <= this -> degree(); i++)
			for(unsigned int j = 0; j <= other.degree(); j++)
				ans[i + j] += (*this)[i] * other[j];

		while(!ans.constants.empty() && ans.constants.back() == type())
			ans.constants.pop_back();

		return ans;
	}

	polynomial<type> operator / (const polynomial<type>& other) const {
		polynomial<type> ans;

		if (other.size() == 0) throw "Impartire la zero";
		// assert(other.size() != 0);

		if (this -> size() == 0)
			return ans;

		ans.constants.resize(this -> degree() - other.degree() + 1);

		polynomial<type> aux;
		aux = (*this);

		for(int i = this -> degree(); i >= other.degree(); i--){
			type x = aux[i] / other[other.degree()];
			ans[i - other.degree()] = x;

			for(int j = other.degree(); j >= 0; j--)
				aux[i - (other.degree() - j)] = aux[i - (other.degree() - j)] - x * other[j];
		}

		while(!ans.constants.empty() && ans.constants.back() == type())
			ans.constants.pop_back();

		return ans;
	}

	polynomial<type> operator % (const polynomial<type>& other) const {
		polynomial<type> ans;

		if (other.size() == 0) throw "Impartire la zero";
		// assert(other.size() != 0);

		if (this -> size() == 0)
			return ans;

		ans = (*this);

		for(int i = this -> degree(); i >= other.degree(); i--){
			type x = ans[i] / other[other.degree()];

			for(int j = other.degree(); j >= 0; j--)
				ans[i - (other.degree() - j)] = ans[i - (other.degree() - j)] - x * other[j];
		}

		while(!ans.constants.empty() && ans.constants.back() == type())
			ans.constants.pop_back();

		return ans;
	}

	void operator += (const polynomial<type>& other){ (*this) = (*this) + other; }
	void operator -= (const polynomial<type>& other){ (*this) = (*this) - other; }
	void operator *= (const polynomial<type>& other){ (*this) = (*this) * other; }
	void operator /= (const polynomial<type>& other){ (*this) = (*this) / other; }
	void operator %= (const polynomial<type>& other){ (*this) = (*this) % other; }

	template<class variable_type = type, class answer_type = variable_type>
	answer_type operator () (const variable_type& x) const {
		answer_type ans = answer_type();
		variable_type x_pow = x;

		for(unsigned int i = 0; i < size(); i++){
			if (i == 0) ans = ans + (*this)[i];
			else {
				ans = ans + x_pow * (*this)[i];
				x_pow = x_pow * x;
			}
		}

		return ans;
	}

	bool operator == (const polynomial<type>& other) const {
		if (degree() != other.degree()) return false;

		for(unsigned int i = 0; i < size(); i++)
			if ((*this)[i] != other[i]) return false;

		return true;
	}

	bool operator != (const polynomial<type>& other) const {
		return (true ^ ((*this) == other));
	}

	bool operator < (const polynomial<type>& other) const {
		if (degree() < other.degree()) return true;
		if (degree() > other.degree()) return false;

		for(int i = degree(); i >= 0; i--){
			if ((*this)[i] < other[i]) return true;
			if ((*this)[i] > other[i]) return false;
		}

		return false;
	}

	// std::ostream& print_to_stream(std::ostream& out, bool show) {
	// 	if (size() == 0){
	// 		out << "0";
	// 		return out;
	// 	}
		
	// 	for(unsigned int i = 0; i < size(); i++){
	// 		out << (*this)[i]; 

	// 		if (show){
	// 			out << " * X ^ " << i;
	// 			if (i < degree()) out << " + ";
	// 		}
	// 		else out << ' ';
	// 	}

	// 	return out;
	// }
	// 
	// std::string pretty() {
	// 	stringstream ss;
	// 	print_to_stream(ss, true);
	// 	return ss.getline();
	// }

	friend class polynomial_eval;
};

template<class type>
std::istream& operator >> (std::istream& in, polynomial<type>& p){
	unsigned int n; in >> n;

	for(unsigned int i = 0; i <= n; i++){
		type x; in >> x;
		p.insert(x);
	}

	return in;
}

template<class type>
std::ostream& operator << (std::ostream& out, const polynomial<type>& p){
	// return p.print_to_stream(out, false);

	if (p.size() == 0){
		out << "0";
		return out;
	}
		
	for(unsigned int i = 0; i < p.size(); i++){
		out << p[i]; 
		out << ' ';
		// if (out == std::cout){
		// 	out << " * X ^ " << i;
		// 	if (i < p.degree()) out << " + ";
		// }
		// else out << ' ';
	}

	return out;
}
