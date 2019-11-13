#include <iostream>
#include <fstream>
#include "graph.h"
#include "user.cpp"
#include <vector>
#include <string>
using namespace std;

int main(){
	ifstream in ("input.txt");
	ofstream out ("output.txt");

	vector<graph<node>> v;
	string s;

	while(in >> s){
		if (s == "add_graph"){
			v.push_back(graph<node>());
			in >> v.back();
		} else
		if (s == "add_edge"){
			int gr, x1, y1, x2, y2; in >> gr >> x1 >> y1 >> x2 >> y2;
			if (v[gr - 1].addEdge(node(x1, y1), node(x2, y2))) out << "added\n";
			else out << "not added\n";
		} else
		if (s == "min_dist"){
			int gr, x1, y1, x2, y2; in >> gr >> x1 >> y1 >> x2 >> y2;
			out << v[gr - 1].minDist(node(x1, y1), node(x2, y2)) << '\n';
		}
	}

	return 0;
}
