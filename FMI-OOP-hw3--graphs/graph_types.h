#pragma once

#include <cassert>
#include <map>
#include <vector>
#include <queue>

// vezi indexarea. in dijkstra incepe de la 0
// la fel in lca cred

class edge_to {
public:
	int vertex;
	double dist;

	edge_to();
	edge_to(const edge_to& other);
	edge_to(int a, double b);

	bool operator < (const edge_to& other) const;
};

template <class node>
class base {
public:
	int no_of_edges;
	int no_of_vertices;
	bool should_update;

	std::map<node, int> extern_to_intern_vertex;
	std::vector<node> intern_to_extern_vertex;

	base();
	base(const base<node>& other);
	base(const std::vector<std::pair<node, node>>& edges);
	~base();

	virtual bool addEdge(const node& a, const node& b) { return false; }
	virtual double minDist(const node& a, const node& b) { return -1; }
	virtual base<node>* upgrade() {
		return new base<node>(*this);
	}
	virtual base<node>* clone() {
		return new base<node>(*this);
	}
	virtual const base<node>& operator = (const base<node>& other) {
		this -> no_of_edges = other.no_of_edges;
		this -> no_of_vertices = other.no_of_vertices;
		this -> should_update = other.should_update;

		this -> extern_to_intern_vertex.erase(this -> extern_to_intern_vertex.begin(), this -> extern_to_intern_vertex.end());
		this -> intern_to_extern_vertex.erase(this -> intern_to_extern_vertex.begin(), this -> intern_to_extern_vertex.end());

		this -> extern_to_intern_vertex = other.extern_to_intern_vertex;
		this -> intern_to_extern_vertex = other.intern_to_extern_vertex;

		return other;
	}
};

template <class node>
class chain : public base<node> {
protected:
	std::vector<double> partial_distances;

public:
	chain();
	chain(const chain& other);
	chain(const std::vector<std::pair<node, node>>& edges);
	~chain();

	bool addEdge(const node &a, const node &b);
	double minDist(const node &a, const node &b);
	base<node>* upgrade();
	base<node>* clone();
	const chain<node>& operator = (const chain<node>& other);
};

template <class node>
class tree : public base<node> {
protected:
	std::vector<std::vector<edge_to>> ancestors;
	std::vector<int> level;

public:
	tree();
	tree(const tree& other);
	tree(const std::vector<std::pair<node, node>>& edges);
	~tree();

	bool addEdge(const node &a, const node &b);
	double minDist(const node &a, const node &b);
	base<node>* upgrade();
	base<node>* clone();
	const tree<node>& operator = (const tree<node>& other);
};

template <class node>
class generic_graph : public base<node> {
public:
	std::vector<std::vector<edge_to>> undirected_edges;

	generic_graph();
	generic_graph(const generic_graph& other);
	generic_graph(const std::vector<std::pair<node, node>>& edges);
	~generic_graph();

	bool addEdge(const node &a, const node &b);
	double minDist(const node &a, const node &b);
	base<node>* upgrade();
	base<node>* clone();
	const generic_graph<node>& operator = (const generic_graph<node>& other);
};

template <class node>
class complete_graph : public base<node> {
public:
	std::vector<std::vector<double>> undirected_edges;

	complete_graph();
	complete_graph(const complete_graph& other);
	complete_graph(const std::vector<std::pair<node, node>>& edges);
	~complete_graph();

	bool addEdge(const node &a, const node &b);
	double minDist(const node &a, const node &b);
	base<node>* upgrade();
	base<node>* clone();
	const complete_graph<node>& operator = (const complete_graph<node>& other);
};

template <class node>
class dag : public base<node> {
public:
	std::vector<std::vector<edge_to>> directed_edges;

	dag();
	dag(const dag& other);
	dag(const std::vector<std::pair<node, node>>& edges);
	~dag();

	bool addEdge(const node &a, const node &b);
	double minDist(const node &a, const node &b);
	base<node>* upgrade();
	base<node>* clone();
	const dag<node>& operator = (const dag<node>& other);
};

// functii base

template <class node>
base<node>::base() {
	this -> no_of_edges = this -> no_of_vertices = 0;
	this -> should_update = false;
}

template <class node>
base<node>::base(const base<node>& other) {
	this -> no_of_edges = other.no_of_edges;
	this -> no_of_vertices = other.no_of_vertices;
	this -> should_update = other.should_update;

	this -> extern_to_intern_vertex.erase(this -> extern_to_intern_vertex.begin(), this -> extern_to_intern_vertex.end());
	this -> intern_to_extern_vertex.erase(this -> intern_to_extern_vertex.begin(), this -> intern_to_extern_vertex.end());

	this -> extern_to_intern_vertex = other.extern_to_intern_vertex;
	this -> intern_to_extern_vertex = other.intern_to_extern_vertex;
}

template <class node>
base<node>::base(const std::vector<std::pair<node, node>>& edges) {}

template <class node>
base<node>::~base() {}

// functii chain

template <class node>
chain<node>::chain() : base<node>() {}

template <class node>
chain<node>::chain(const chain& other) : base<node>(other) {
	this -> partial_distances = other.partial_distances;
}

template <class node>
chain<node>::chain(const std::vector<std::pair<node, node>>& edges) : base<node>() {
	this -> no_of_edges = edges.size();
	this -> should_update = false;

	std::vector<std::vector<int>> aux;
	std::vector<node> vertices;
	for(auto i : edges){
		if (this -> extern_to_intern_vertex.find(i.first) == this -> extern_to_intern_vertex.end()){
			this -> extern_to_intern_vertex[i.first] = vertices.size();
			vertices.push_back(i.first);
			aux.push_back(std::vector<int>());
		}
		if (this -> extern_to_intern_vertex.find(i.second) == this -> extern_to_intern_vertex.end()){
			this -> extern_to_intern_vertex[i.second] = vertices.size();
			vertices.push_back(i.second);
			aux.push_back(std::vector<int>());
		}

		aux[this -> extern_to_intern_vertex[i.first]].push_back(this -> extern_to_intern_vertex[i.second]);
		aux[this -> extern_to_intern_vertex[i.second]].push_back(this -> extern_to_intern_vertex[i.first]);
	}

	this -> no_of_vertices = vertices.size();
	assert(this -> no_of_vertices == this -> no_of_edges + 1);

	int curr_node = -1;
	for(int i = 0; i < this -> no_of_vertices; i++)
		if (aux[i].size() < 2){
			curr_node = i;
			break;
		}

	this -> extern_to_intern_vertex.erase(this -> extern_to_intern_vertex.begin(), this -> extern_to_intern_vertex.end());
	this -> intern_to_extern_vertex.resize(this -> no_of_vertices);

	double curr_dist = 0;
	int prev_node = curr_node;
	for(int i = 0; i < this -> no_of_vertices; i++){
		this -> intern_to_extern_vertex[i] = vertices[curr_node];
		this -> extern_to_intern_vertex[vertices[curr_node]] = i;
		this -> partial_distances.push_back(curr_dist);

		int new_node = -1;
		for(auto j : aux[curr_node])
			if (j != prev_node){
				new_node = j;
				break;
			}

		if (new_node == -1) break;

		curr_dist += vertices[curr_node].dist(vertices[new_node]);
		prev_node = curr_node;
		curr_node = new_node;
	}
}

template <class node>
chain<node>::~chain() {}

template <class node>
bool chain<node>::addEdge(const node &a, const node &b){
	if (this -> extern_to_intern_vertex.find(a) == this -> extern_to_intern_vertex.end()) return false;
	if (this -> extern_to_intern_vertex.find(b) == this -> extern_to_intern_vertex.end()) return false;
	if (std::abs(this -> extern_to_intern_vertex[a] - this -> extern_to_intern_vertex[b]) <= 1) return false;

	this -> should_update = true;
	return false;
}

template <class node>
double chain<node>::minDist(const node &a, const node &b){
	if (this -> extern_to_intern_vertex.find(a) == this -> extern_to_intern_vertex.end()) return -1;
	if (this -> extern_to_intern_vertex.find(b) == this -> extern_to_intern_vertex.end()) return -1;
	
	int aa = this -> extern_to_intern_vertex[a];
	int bb = this -> extern_to_intern_vertex[b];
	if (aa > bb) std::swap(aa, bb);
	return this -> partial_distances[bb] - this -> partial_distances[aa];
}

template <class node>
base<node>* chain<node>::clone(){
	base<node>* ans = new chain(*this);
	return ans;
}

template <class node>
base<node>* chain<node>::upgrade(){
	generic_graph<node>* new_graph = new generic_graph<node>;
	
	new_graph -> no_of_vertices = this -> no_of_vertices;
	new_graph -> no_of_edges = this -> no_of_edges;
	new_graph -> should_update = false;
	new_graph -> extern_to_intern_vertex = this -> extern_to_intern_vertex;
	new_graph -> intern_to_extern_vertex = this -> intern_to_extern_vertex;

	new_graph -> undirected_edges.resize(new_graph -> no_of_vertices);
	for(int i = 1; i < this -> no_of_vertices; i++){
		new_graph -> undirected_edges[i].push_back(edge_to(i - 1, this -> partial_distances[i] - this -> partial_distances[i - 1]));
		new_graph -> undirected_edges[i - 1].push_back(edge_to(i, this -> partial_distances[i] - this -> partial_distances[i - 1]));
	}

	return new_graph;
}

template <class node>
const chain<node>& chain<node>::operator = (const chain<node>& other){
	this -> no_of_edges = other.no_of_edges;
	this -> no_of_vertices = other.no_of_vertices;
	this -> should_update = other.should_update;

	this -> extern_to_intern_vertex.erase(this -> extern_to_intern_vertex.begin(), this -> extern_to_intern_vertex.end());
	this -> intern_to_extern_vertex.erase(this -> intern_to_extern_vertex.begin(), this -> intern_to_extern_vertex.end());

	this -> extern_to_intern_vertex = other.extern_to_intern_vertex;
	this -> intern_to_extern_vertex = other.intern_to_extern_vertex;

	this -> partial_distances.erase(this -> partial_distances.begin(), this -> partial_distances.end());
	this -> partial_distances = other.partial_distances;

	return other;
}

// functii tree

template <class node>
tree<node>::tree() : base<node>() {}

template <class node>
tree<node>::tree(const tree& other) : base<node>(other) {
	this -> level = other.level;
	this -> ancestors = other.ancestors;
}

template <class node>
tree<node>::tree(const std::vector<std::pair<node, node>>& edges) : base<node>() {
	this -> should_update = false;
	this -> no_of_edges = edges.size();

	std::vector<std::vector<edge_to>> aux;
	for(auto i : edges){
		if (this -> extern_to_intern_vertex.find(i.first) == this -> extern_to_intern_vertex.end()){
			this -> extern_to_intern_vertex[i.first] = this -> intern_to_extern_vertex.size();
			this -> intern_to_extern_vertex.push_back(i.first);
			aux.push_back(std::vector<edge_to>());
		}
		if (this -> extern_to_intern_vertex.find(i.second) == this -> extern_to_intern_vertex.end()){
			this -> extern_to_intern_vertex[i.second] = this -> intern_to_extern_vertex.size();
			this -> intern_to_extern_vertex.push_back(i.second);
			aux.push_back(std::vector<edge_to>());
		}

		aux[this -> extern_to_intern_vertex[i.first]].push_back(edge_to(this -> extern_to_intern_vertex[i.second], i.first.dist(i.second)));
		aux[this -> extern_to_intern_vertex[i.second]].push_back(edge_to(this -> extern_to_intern_vertex[i.first], i.second.dist(i.first)));
	}

	this -> no_of_vertices = this -> intern_to_extern_vertex.size();
	assert(this -> no_of_vertices == this -> no_of_edges + 1);
	
	this -> ancestors.push_back(std::vector<edge_to>(this -> no_of_vertices));
	this -> level.resize(this -> no_of_vertices, -1);
	this -> level[0] = 0;
	std::queue<int> Q; Q.push(0);
	while(!Q.empty()){
		int curr_node = Q.front();
		Q.pop();

		for(auto new_node : aux[curr_node]){
			if (this -> level[new_node.vertex] == -1){
				this -> ancestors[0][new_node.vertex] = edge_to(curr_node, new_node.dist);
				Q.push(new_node.vertex);
				this -> level[new_node.vertex] = this -> level[curr_node] + 1;
			}
		}
	}

	while((1 << (this -> ancestors.size())) < this -> no_of_vertices)
		this -> ancestors.push_back(std::vector<edge_to>(this -> no_of_vertices));

	for(int i = 1; i < this -> ancestors.size(); i++)
		for(int j = 0; j < this -> no_of_vertices; j++)
			this -> ancestors[i][j] = edge_to(this -> ancestors[i - 1][this -> ancestors[i - 1][j].vertex].vertex, this -> ancestors[i - 1][j].dist + this -> ancestors[i - 1][this -> ancestors[i - 1][j].vertex].dist);
}

template <class node>
tree<node>::~tree() {}

template <class node>
bool tree<node>::addEdge(const node &a, const node &b){
	if (this -> extern_to_intern_vertex.find(a) == this -> extern_to_intern_vertex.end()) return false;
	if (this -> extern_to_intern_vertex.find(b) == this -> extern_to_intern_vertex.end()) return false;
	
	int aa = this -> extern_to_intern_vertex[a];
	int bb = this -> extern_to_intern_vertex[b];
	if (this -> ancestors[0][aa].vertex == bb || this -> ancestors[0][bb].vertex == aa) return false;

	this -> should_update = true;
	return false;
}

template <class node>
double tree<node>::minDist(const node &a, const node &b){
	if (this -> extern_to_intern_vertex.find(a) == this -> extern_to_intern_vertex.end()) return -1;
	if (this -> extern_to_intern_vertex.find(b) == this -> extern_to_intern_vertex.end()) return -1;
	
	int aa = this -> extern_to_intern_vertex[a];
	int bb = this -> extern_to_intern_vertex[b];

	if (this -> level[aa] > this -> level[bb]) std::swap(aa, bb);

	int p = this -> ancestors.size() - 1;
	double ans = 0;
	while(p >= 0){
		if (this -> level[this -> ancestors[p][bb].vertex] >= this -> level[aa]){
			ans += this -> ancestors[p][bb].dist;
			bb = this -> ancestors[p][bb].vertex;
		}
		p--;
	}

	if (aa == bb) return ans;

	p = this -> ancestors.size() - 1;
	while(p >= 0){
		if (this -> ancestors[p][bb].vertex != this -> ancestors[p][aa].vertex){
			ans += this -> ancestors[p][bb].dist + this -> ancestors[p][aa].dist;
			bb = ancestors[p][bb].vertex;
			aa = ancestors[p][aa].vertex;
		}
		p--;
	}

	ans += this -> ancestors[0][bb].dist + this -> ancestors[0][aa].dist;
	return ans;
}

template <class node>
base<node>* tree<node>::clone(){
	base<node>* ans = new tree(*this);
	return ans;
}

template <class node>
base<node>* tree<node>::upgrade(){
	generic_graph<node>* ans = new generic_graph<node>;

	ans -> no_of_vertices = this -> no_of_vertices;
	ans -> no_of_edges = this -> no_of_edges;
	ans -> should_update = false;

	ans -> intern_to_extern_vertex = this -> intern_to_extern_vertex;
	ans -> extern_to_intern_vertex = this -> extern_to_intern_vertex;

	ans -> undirected_edges.resize(this -> no_of_vertices);
	for(int i = 1; i < this -> no_of_vertices; i++){
		ans -> undirected_edges[i].push_back(this -> ancestors[0][i]);
		ans -> undirected_edges[this -> ancestors[0][i].vertex].push_back(edge_to(i, this -> ancestors[0][i].dist));
	}

	return ans;
}

template <class node>
const tree<node>& tree<node>::operator = (const tree<node>& other) {
	this -> no_of_edges = other.no_of_edges;
	this -> no_of_vertices = other.no_of_vertices;
	this -> should_update = other.should_update;

	this -> extern_to_intern_vertex.erase(this -> extern_to_intern_vertex.begin(), this -> extern_to_intern_vertex.end());
	this -> intern_to_extern_vertex.erase(this -> intern_to_extern_vertex.begin(), this -> intern_to_extern_vertex.end());

	this -> extern_to_intern_vertex = other.extern_to_intern_vertex;
	this -> intern_to_extern_vertex = other.intern_to_extern_vertex;

	this -> ancestors.erase(this -> ancestors.begin(), this -> ancestors.end());
	this -> ancestors = other.ancestors;

	this -> level.erase(this -> level.begin(), this -> level.end());
	this -> level = other.level;

	return other;
}

// funtii generic_graph

template <class node>
generic_graph<node>::generic_graph() : base<node>() {}

template <class node>
generic_graph<node>::generic_graph(const generic_graph& other) : base<node>(other) {
	this -> undirected_edges = other.undirected_edges;
}

template <class node>
generic_graph<node>::generic_graph(const std::vector<std::pair<node, node>>& edges) : base<node>() {
	this -> should_update = false;
	this -> no_of_edges = edges.size();

	for(auto i : edges){
		if (this -> extern_to_intern_vertex.find(i.first) == this -> extern_to_intern_vertex.end()){
			this -> extern_to_intern_vertex[i.first] = this -> intern_to_extern_vertex.size();
			this -> intern_to_extern_vertex.push_back(i.first);
			this -> undirected_edges.push_back(std::vector<edge_to>());
		}
		if (this -> extern_to_intern_vertex.find(i.second) == this -> extern_to_intern_vertex.end()){
			this -> extern_to_intern_vertex[i.second] = this -> intern_to_extern_vertex.size();
			this -> intern_to_extern_vertex.push_back(i.second);
			this -> undirected_edges.push_back(std::vector<edge_to>());
		}

		this -> undirected_edges[this -> extern_to_intern_vertex[i.first]].push_back(edge_to(this -> extern_to_intern_vertex[i.second], i.first.dist(i.second)));
		this -> undirected_edges[this -> extern_to_intern_vertex[i.second]].push_back(edge_to(this -> extern_to_intern_vertex[i.first], i.second.dist(i.first)));
	}

	this -> no_of_vertices = this -> intern_to_extern_vertex.size();
}

template <class node>
generic_graph<node>::~generic_graph() {}

template <class node>
bool generic_graph<node>::addEdge(const node &a, const node &b){
	if (this -> extern_to_intern_vertex.find(a) == this -> extern_to_intern_vertex.end()) return false;
	if (this -> extern_to_intern_vertex.find(b) == this -> extern_to_intern_vertex.end()) return false;
	
	int aa = this -> extern_to_intern_vertex[a];
	int bb = this -> extern_to_intern_vertex[b];
	
	for(auto it : this -> undirected_edges[aa])
		if (it.vertex == bb) return false;

	this -> undirected_edges[aa].push_back(edge_to(bb, a.dist(b)));
	this -> undirected_edges[bb].push_back(edge_to(aa, b.dist(a)));
	this -> no_of_edges++;

	if (this -> no_of_edges == this -> no_of_vertices * (this -> no_of_vertices + 1) / 2)
		this -> should_update = true;

	return true;
}

template <class node>
double generic_graph<node>::minDist(const node &a, const node &b){
	if (this -> extern_to_intern_vertex.find(a) == this -> extern_to_intern_vertex.end()) return -1;
	if (this -> extern_to_intern_vertex.find(b) == this -> extern_to_intern_vertex.end()) return -1;
	
	int aa = this -> extern_to_intern_vertex[a];
	int bb = this -> extern_to_intern_vertex[b];

	std::priority_queue<edge_to> heap;
	std::vector<double> dist; dist.resize(this -> no_of_vertices, -1);

	dist[aa] = 0;
	heap.push(edge_to(aa, 0));

	while(!heap.empty() && heap.top().vertex != bb){
		edge_to now = heap.top();
		heap.pop();
		if (now.dist != dist[now.vertex]) continue;

		for(auto it : undirected_edges[now.vertex])
			if (dist[it.vertex] == -1 || dist[it.vertex] > dist[now.vertex] + it.dist){
				dist[it.vertex] = dist[now.vertex] + it.dist;
				heap.push(edge_to(it.vertex, dist[it.vertex]));
			}
	}

	return dist[bb];
}

template <class node>
base<node>* generic_graph<node>::clone(){
	base<node>* ans = new generic_graph(*this);
	return ans;
}

template <class node>
base<node>* generic_graph<node>::upgrade(){
	complete_graph<node>* ans = new complete_graph<node>;

	ans -> no_of_vertices = this -> no_of_vertices;
	ans -> no_of_edges = this -> no_of_edges;
	ans -> should_update = true;

	ans -> intern_to_extern_vertex = this -> intern_to_extern_vertex;
	ans -> extern_to_intern_vertex = this -> extern_to_intern_vertex;

	ans -> undirected_edges.resize(this -> no_of_vertices, std::vector<double>(this -> no_of_vertices, 0));
	for(int i = 0; i < this -> no_of_vertices; i++)
		for(auto j : this -> undirected_edges[i])
			ans -> undirected_edges[i][j.vertex] = j.dist;

	return ans;
}

template <class node>
const generic_graph<node>& generic_graph<node>::operator = (const generic_graph<node>& other) {
	this -> no_of_edges = other.no_of_edges;
	this -> no_of_vertices = other.no_of_vertices;
	this -> should_update = other.should_update;

	this -> extern_to_intern_vertex.erase(this -> extern_to_intern_vertex.begin(), this -> extern_to_intern_vertex.end());
	this -> intern_to_extern_vertex.erase(this -> intern_to_extern_vertex.begin(), this -> intern_to_extern_vertex.end());

	this -> extern_to_intern_vertex = other.extern_to_intern_vertex;
	this -> intern_to_extern_vertex = other.intern_to_extern_vertex;

	this -> undirected_edges.erase(this -> undirected_edges.begin(), this -> undirected_edges.end());
	this -> undirected_edges = other.undirected_edges;

	return other;
}

// functii complete graph

template <class node>
complete_graph<node>::complete_graph() : base<node>() {}

template <class node>
complete_graph<node>::complete_graph(const complete_graph& other) : base<node>(other) {
	this -> undirected_edges = other.undirected_edges;
}

template <class node>
complete_graph<node>::complete_graph(const std::vector<std::pair<node, node>>& edges) : base<node>() {
	this -> should_update = false;
	this -> no_of_edges = edges.size();

	for(auto i : edges){
		if (this -> extern_to_intern_vertex.find(i.first) == this -> extern_to_intern_vertex.end()){
			this -> extern_to_intern_vertex[i.first] = this -> intern_to_extern_vertex.size();
			this -> intern_to_extern_vertex.push_back(i.first);
		}
		if (this -> extern_to_intern_vertex.find(i.second) == this -> extern_to_intern_vertex.end()){
			this -> extern_to_intern_vertex[i.second] = this -> intern_to_extern_vertex.size();
			this -> intern_to_extern_vertex.push_back(i.second);
		}
	}

	this -> no_of_vertices = this -> intern_to_extern_vertex.size();
	assert(this -> no_of_edges == this -> no_of_vertices * (this -> no_of_vertices - 1) / 2);

	this -> undirected_edges.resize(this -> no_of_vertices, std::vector<double>(this -> no_of_vertices));
	for(int i = 0; i < this -> no_of_vertices; i++)
		for(int j = i + 1; j < this -> no_of_vertices; j++)
			this -> undirected_edges[i][j] = this -> undirected_edges[j][i] = (this -> intern_to_extern_vertex[i].dist(this -> intern_to_extern_vertex[j]));
}

template <class node>
complete_graph<node>::~complete_graph() {}

template <class node>
bool complete_graph<node>::addEdge(const node &a, const node &b){
	if (this -> should_update == false) return false;

	int aa = this -> extern_to_intern_vertex[a], bb = this -> extern_to_intern_vertex[b];

	this -> undirected_edges[aa][bb] = this -> undirected_edges[bb][aa] = a.dist(b);
	this -> no_of_edges++;
	this -> should_update = false;
	return true;
}

template <class node>
double complete_graph<node>::minDist(const node &a, const node &b){
	if (this -> extern_to_intern_vertex.find(a) == this -> extern_to_intern_vertex.end()) return -1;
	if (this -> extern_to_intern_vertex.find(b) == this -> extern_to_intern_vertex.end()) return -1;
	return this -> undirected_edges[this -> extern_to_intern_vertex[a]][this -> extern_to_intern_vertex[b]];
}

template <class node>
base<node>* complete_graph<node>::clone() {
	base<node>* ans = new complete_graph(*this);
	return ans;
}

template <class node>
base<node>* complete_graph<node>::upgrade() {
	base<node>* ans = this -> clone();
	ans -> should_update = false;
	return ans;
}

template <class node>
const complete_graph<node>& complete_graph<node>::operator = (const complete_graph<node>& other) {
	this -> no_of_edges = other.no_of_edges;
	this -> no_of_vertices = other.no_of_vertices;
	this -> should_update = other.should_update;

	this -> extern_to_intern_vertex.erase(this -> extern_to_intern_vertex.begin(), this -> extern_to_intern_vertex.end());
	this -> intern_to_extern_vertex.erase(this -> intern_to_extern_vertex.begin(), this -> intern_to_extern_vertex.end());

	this -> extern_to_intern_vertex = other.extern_to_intern_vertex;
	this -> intern_to_extern_vertex = other.intern_to_extern_vertex;

	this -> undirected_edges.erase(this -> undirected_edges.begin(), this -> undirected_edges.end());
	this -> undirected_edges = other.undirected_edges;

	return other;
}

// functii dag

template <class node>
dag<node>::dag() : base<node>() {}

template <class node>
dag<node>::dag(const dag& other) : base<node>(other) {
	this -> directed_edges = other.directed_edges;
}

template <class node>
dag<node>::dag(const std::vector<std::pair<node, node>>& edges) : base<node>() {
	this -> should_update = false;
	this -> no_of_edges = edges.size();

	for(auto i : edges){
		if (this -> extern_to_intern_vertex.find(i.first) == this -> extern_to_intern_vertex.end()){
			this -> extern_to_intern_vertex[i.first] = this -> intern_to_extern_vertex.size();
			this -> intern_to_extern_vertex.push_back(i.first);
			this -> directed_edges.push_back(std::vector<edge_to>());
		}
		if (this -> extern_to_intern_vertex.find(i.second) == this -> extern_to_intern_vertex.end()){
			this -> extern_to_intern_vertex[i.second] = this -> intern_to_extern_vertex.size();
			this -> intern_to_extern_vertex.push_back(i.second);
			this -> directed_edges.push_back(std::vector<edge_to>());
		}

		this -> directed_edges[this -> extern_to_intern_vertex[i.first]].push_back(edge_to(this -> extern_to_intern_vertex[i.second], i.first.dist(i.second)));
	}

	this -> no_of_vertices = this -> intern_to_extern_vertex.size();
}

template <class node>
dag<node>::~dag() {}

template <class node>
bool dag<node>::addEdge(const node &a, const node &b){
	if (this -> extern_to_intern_vertex.find(a) == this -> extern_to_intern_vertex.end()) return false;
	if (this -> extern_to_intern_vertex.find(b) == this -> extern_to_intern_vertex.end()) return false;
	
	int aa = this -> extern_to_intern_vertex[a];
	int bb = this -> extern_to_intern_vertex[b];
	
	if (aa == bb) return false;

	for(auto it : this -> directed_edges[aa])
		if (it.vertex == bb) return false;

	if (this -> minDist(b, a) != -1) return false;

	this -> directed_edges[aa].push_back(edge_to(bb, a.dist(b)));
	this -> no_of_edges++;

	return true;
}

template <class node>
double dag<node>::minDist(const node& a, const node& b){
	if (this -> extern_to_intern_vertex.find(a) == this -> extern_to_intern_vertex.end()) return -1;
	if (this -> extern_to_intern_vertex.find(b) == this -> extern_to_intern_vertex.end()) return -1;
	
	int aa = this -> extern_to_intern_vertex[a];
	int bb = this -> extern_to_intern_vertex[b];

	std::priority_queue<edge_to> heap;
	std::vector<double> dist; dist.resize(this -> no_of_vertices + 1, -1);

	dist[aa] = 0;
	heap.push(edge_to(aa, 0));

	while(!heap.empty() && heap.top().vertex != bb){
		edge_to now = heap.top();
		heap.pop();
		if (now.dist != dist[now.vertex]) continue;

		for(auto it : directed_edges[now.vertex])
			if (dist[it.vertex] == -1 || dist[it.vertex] > dist[now.vertex] + it.dist){
				dist[it.vertex] = dist[now.vertex] + it.dist;
				heap.push(edge_to(it.vertex, dist[it.vertex]));
			}
	}

	return dist[bb];
}

template <class node>
base<node>* dag<node>::clone(){
	base<node>* ans = new dag(*this);
	return ans;
}

template <class node>
base<node>* dag<node>::upgrade() {
	base<node>* ans = this -> clone();
	ans -> should_update = false;
	return ans;
}

template <class node>
const dag<node>& dag<node>::operator = (const dag<node>& other) {
	this -> no_of_edges = other.no_of_edges;
	this -> no_of_vertices = other.no_of_vertices;
	this -> should_update = other.should_update;

	this -> extern_to_intern_vertex.erase(this -> extern_to_intern_vertex.begin(), this -> extern_to_intern_vertex.end());
	this -> intern_to_extern_vertex.erase(this -> intern_to_extern_vertex.begin(), this -> intern_to_extern_vertex.end());

	this -> extern_to_intern_vertex = other.extern_to_intern_vertex;
	this -> intern_to_extern_vertex = other.intern_to_extern_vertex;

	this -> directed_edges.erase(this -> directed_edges.begin(), this -> directed_edges.end());
	this -> directed_edges = other.directed_edges;

	return other;
}

// functii edge to

edge_to::edge_to(){
	this -> vertex = 0;
	this -> dist = 0;
}

edge_to::edge_to(const edge_to& other){
	this -> vertex = other.vertex;
	this -> dist = other.dist;
}

edge_to::edge_to(int a, double b){
	this -> vertex = a;
	this -> dist = b;
}

bool edge_to::operator < (const edge_to& other) const {
	if (this -> dist != other.dist)
		return (this -> dist > other.dist);
	else return (this -> vertex > other.dist);
}
