#pragma once

#include "graph.h"
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>

class node {
protected:
	double x, y;

public:
	node() { x = 0; y = 0; }
	node(const double& b, const double& c) { x = b; y = c; }
	node(const node& other) { x = other.x; y = other.y; }
	~node() {}

	double dist(const node& other) const {
		return sqrt((x - other.x) * (x - other.x) + (y - other.y) * (y - other.y));
	}

	bool operator < (const node& other) const {
		if (this -> x != other.x) return (this -> x < other.x);
		return (this -> y < other.y);
	}

	const node& operator = (const node& other) {
		this -> x = other.x;
		this -> y = other.y;
		return other;
	}
};

template <class type>
std::istream& operator >> (std::istream& in, graph<type>& g){
	std::string s; in >> s;
	int m; in >> m;

	std::vector<std::pair<type, type>> e;
	for(int i = 0; i < m; i++){
		int x1, y1, x2, y2; in >> x1 >> y1 >> x2 >> y2;
		e.push_back({type(x1, y1), type(x2, y2)});
	}

	g = graph<type>(s, e);
	return in;
}
