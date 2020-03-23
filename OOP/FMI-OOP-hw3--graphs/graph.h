#pragma once

#include "graph_types.h"
#include <string>

template<class node>
class graph {
private:
	base<node>* _graph;

public:
	graph();
	graph(const graph& other);
	graph(const std::string& type, const std::vector<std::pair<node, node>>& edges);
	~graph();

	bool addEdge(const node& a, const node& b);
	double minDist(const node& a, const node& b);
	const graph<node>& operator = (const graph<node>& other);
};

template <class node>
graph<node>::graph(){
	_graph = NULL;
}

template <class node>
graph<node>::graph(const graph& other){
	if (other._graph == NULL) _graph = NULL;
	else _graph = other._graph -> clone();
}

template <class node>
graph<node>::graph(const std::string& type, const std::vector<std::pair<node, node>>& edges){
	if (type == "chain")
		_graph = new chain<node>(edges);
	else
	if (type == "tree")
		_graph = new tree<node>(edges);
	else
	if (type == "dag")
		_graph = new dag<node>(edges);
	else
	if (type == "generic_graph")
		_graph = new generic_graph<node>(edges);
	else
	if (type == "complete_graph")
		_graph = new complete_graph<node>(edges);
	else assert(1);
}

template <class node>
graph<node>::~graph(){
	if (_graph != NULL) delete _graph;
}

template <class node>
double graph<node>::minDist(const node &a, const node &b){
	return _graph -> minDist(a, b);
}

template <class node>
bool graph<node>::addEdge(const node &a, const node &b){
	if (_graph -> addEdge(a, b)) return true;
	else
	if (_graph -> should_update){
		base<node>* aux = _graph -> upgrade();
		delete _graph;
		_graph = aux;
		return _graph -> addEdge(a, b);
	}
	else return false;
}

template <class node>
const graph<node>& graph<node>::operator = (const graph<node>& other) {
	if (other._graph == NULL) _graph = NULL;
	else _graph = other._graph -> clone();
	return other;
}