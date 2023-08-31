#pragma once

#include <assert.h>
#include <fstream>
#include <iostream>
#define DEF_VALUE 10

template<class type>
class vector{
protected:
	type* v;
	unsigned int _size;
	unsigned int _capacity;

public:
	typedef type* iterator;

	vector(){
		_size = 0;
		_capacity = DEF_VALUE;
		v = new type[DEF_VALUE];
	}

	vector(const unsigned int& x, const type& val = type()){
		_size = 0;
		_capacity = DEF_VALUE;
		v = new type[DEF_VALUE];
		
		resize(x);

		for(int i = 0; i < _size; i++)
			v[i] = val;
	}

	vector(const iterator& first, const iterator& last){
		(*this) = vector();

		for(iterator it = first; it != last; it++)
			this -> push_back(*it);
	}

	vector(const vector<type>& a){
		this -> erase();
		this -> resize(a.size());

		for(int i = 0; i < a.size(); i++)
			(*this)[i] = a[i];
	}

	~vector(){
		_size = _capacity = 0;
		delete[] v;
	}

	virtual const unsigned int& size() const { return _size; }
	virtual const unsigned int max_size() const { return (0 - 1); }
	virtual const unsigned int& capacity() const { return _capacity; }
	virtual void clear(){ _size = 0; }
	
	virtual void erase(){
		delete[] v;
		_size = 0;
		_capacity = DEF_VALUE;
		v = new type[DEF_VALUE];
	}
	virtual void erase(const iterator& x){
		for(iterator it = x; it != rbegin(); it++)
			(*it) = *(it + 1);
		this -> pop_back();
	}
	virtual void erase(const iterator& first, const iterator& last){
		for(iterator it1 = first, it2 = last; it2 != end(); it1++, it2++)
			(*it1) = (*it2);
		while(end() != last)
			this -> pop_back();
	}

	virtual void push_back(type x){
		if (_size == _capacity){
			type* w = new type[_capacity * 2];

			for(unsigned int i = 0; i < _size; i++)
				*(w + i) = *(v + i);

			delete[] v;
			v = w;

			_capacity *= 2;
		}

		v[_size] = x;
		_size++;
	}

	virtual void pop_back(){
		_size--;

		if (_size * 3 < _capacity && _capacity > DEF_VALUE){
			type* w = new type[_capacity / 2];

			for(unsigned int i = 0; i < _size; i++)
				*(w + i) = *(v + i);

			delete[] v;
			v = w;

			_capacity /= 2;
		}
	}

	virtual void resize(const unsigned int& x){
		if (x > _capacity){
			unsigned int new_capacity = _capacity;

			while(new_capacity < x) new_capacity *= 2;

			type* w = new type[new_capacity];

			for(unsigned int i = 0; i < _size; i++)
				*(w + i) = *(v + i);

			delete[] v;
			v = w;
		}

		for(int i = _size; i < x; i++)
			*(v + i) = type();

		_size = x;

		if (_size * 3 < _capacity && _capacity > DEF_VALUE){
			type* w = new type[_capacity / 2];

			for(unsigned int i = 0; i < _size; i++)
				*(w + i) = *(v + i);

			delete[] v;
			v = w;

			_capacity /= 2;
		}
	}

	virtual void reserve(const unsigned int& x){
		if (x <= _capacity) return;

		type* w = new type[x];

		for(unsigned int i = 0; i < _size; i++)
			*(w + i) = *(v + i);

		delete[] v;
		v = w;
		
		_capacity = x;
	}

	virtual void shrink_to_fit(){
		unsigned int new_capacity = _size;

		type* w = new type[new_capacity];

		for(unsigned int i = 0; i < _size; i++)
			*(w + i) = *(v + i);

		delete[] v;
		v = w;

		_capacity = new_capacity;
	}

	virtual bool empty() const{
		return (_size == 0);
	}

	virtual type& back() const {
		return v[_size - 1];
	}

	virtual const vector<type>& operator = (const vector<type>& other){
		this -> erase();
		this -> resize(other.size());

		for(int i = 0; i < other.size(); i++)
			(*this)[i] = other[i];

		return other;
	}

	virtual const type operator [] (const int& x) const {
		return v[x];
	}

	virtual type& operator [] (const int& x){
		assert(x < _size && x >= 0);
		return v[x];
	}

	virtual type& at(const unsigned int& x){
		return (*this)[x];
	}

	virtual type& front(){
		return v[0];
	}

	virtual type& back(){
		return v[_size - 1];
	}

	virtual type* data(){
		return v;
	}

	virtual void assign(const unsigned int& n, const type& x){
		(*this) = vector(n, x);
	}

	virtual void swap(vector<type>& other){
		type* aux = this -> v;
		this -> v = other.v;
		other.v = aux;

		unsigned int aux2 = this -> _size;
		this -> _size = other._size;
		other._size = aux2;

		aux2 = this -> _capacity;
		this -> _capacity = other._capacity;
		other._capacity = aux2;
	}

	virtual vector<type> operator + (const vector<type>& other) const {
		vector<type> ans;
		unsigned int n = std::min(this -> _size, other._size);

		for(unsigned int i = 0; i < n; i++)
			ans.push_back((*this)[i] + other[i]);

		for(unsigned int i = n; i < this -> _size; i++)
			ans.push_back((*this)[i]);

		for(unsigned int i = n; i < other._size; i++)
			ans.push_back(other[i]);

		return ans;
	}

	virtual vector<type> operator - (const vector<type>& other) const {
		vector<type> ans;
		unsigned int n = std::min(this -> _size, other._size);

		for(unsigned int i = 0; i < n; i++)
			ans.push_back((*this)[i] - other[i]);

		for(unsigned int i = n; i < this -> _size; i++)
			ans.push_back((*this)[i]);

		for(unsigned int i = n; i < other._size; i++)
			ans.push_back(type()-other[i]);

		return ans;
	}

	virtual type operator * (const vector<type>& other) const {
		type ans;
		unsigned int n = std::min(this -> _size, other._size);

		for(unsigned int i = 0; i < n; i++)
			ans = ans + ((*this)[i] * other[i]);

		return ans;
	}

	iterator begin(){ return v; }
	iterator end(){ return (v + _size); }
	iterator rbegin(){ return (v + _size - 1); }
	iterator rend(){ return (v - 1); }
};

template<class type = double>
std::istream& operator >> (std::istream& in, vector<type>& x){
	unsigned int n; in >> n;
	x.resize(n);

	for(int i = 0; i < n; i++)
		in >> x[i];

	return in;
}

template<class type = double>
std::ostream& operator << (std::ostream& out, const vector<type>& x){
	if (x.empty()){
		out << '0';
		return out;
	}

	for(int i = 0; i < x.size(); i++)
		out << x[i] << ' ';

	return out;
}