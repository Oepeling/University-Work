#pragma once

#include <assert.h>
#include <fstream>
#include <iostream>
#define DEF_VALUE 10

template<class type>
class vector{
private:
	type* v;
	unsigned int _size;
	unsigned int _capacity;

public:
	vector(){
		_size = 0;
		_capacity = DEF_VALUE;
		v = new type[DEF_VALUE];
	}

	vector(const vector<type>& a){
		(*this) = a;
	}

	~vector(){
		_size = _capacity = 0;
		// std::cerr << "Stergem valoarea: " << v << '\n';
		delete[] v;
	}

	const unsigned int& size() const { return _size; }
	const unsigned int& capacity() const { return _capacity; }
	void clear(){ _size = 0; }
	void erase(){ (*this) = vector(); }
	// friend std::istream& operator >> (std::istream& in, vector<type>& x);

	void push_back(type x){
		if (_size == _capacity){
			type* w = new type[_capacity * 2];

			for(unsigned int i = 0; i < _size; i++)
				*(w + i) = *(v + i);

			delete[] v;
			v = w;

			_capacity *= 2;
		}

		*(v + _size) = x;
		_size++;
	}

	void pop_back(){
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

	void resize(unsigned int x){
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

	bool empty() const{
		return (_size == 0);
	}

	type& back() const {
		return v[_size - 1];
	}

	const vector<type>& operator = (const vector<type>& other){
		_size = other._size;
		_capacity = other._capacity;

		delete[] v;
		v = new type[_capacity];

		for(unsigned int i = 0; i < _size; i++)
			*(v + i) = *(other.v + i);

		return other;
	}

	type& operator [] (unsigned int x) const {
		assert(x < _size && x >= 0);
		return v[x];
	}

	type* begin(){
		return v;
	}

	type* end(){
		return (v + _size);
	}
};

template<class type>
std::istream& operator >> (std::istream& in, vector<type>& x){
	unsigned int n; in >> n;
	x.resize(n);

	for(int i = 0; i < n; i++)
		in >> x[i];

	return in;
}

