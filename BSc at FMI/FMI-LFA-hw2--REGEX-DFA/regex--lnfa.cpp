#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstring>
#include <tuple>
using namespace std;

class node{
public:
	int _id;
	vector<pair<char, node*>> _next;

	node(){
		_id = 0;
	}
};

pair<node*, node*> eval1(char* &s); /// desparte dupa |
pair<node*, node*> eval2(char* &s); /// desparte dupa concat
pair<node*, node*> eval3(char* &s); /// evalueaza chestii cu *
pair<node*, node*> eval4(char* &s); /// evalueaza termen

pair<node*, node*> eval1(char* &s){
	pair<node*, node*> ans = eval2(s);

	if (s[0] == '|'){
		pair<node*, node*> aux = {new node, new node};
		aux.first -> _next.push_back({'.', ans.first});
		ans.second -> _next.push_back({'.', aux.second});
		ans = aux;
	}

	while(s[0] == '|'){
		s++;
		pair<node*, node*> aux = eval2(s);

		ans.first -> _next.push_back({'.', aux.first});
		aux.second -> _next.push_back({'.', ans.second});
	}

	return ans;
}

pair<node*, node*> eval2(char* &s){
	pair<node*, node*> ans = eval3(s);

	while((s[0] >= 'a' && s[0] <= 'z') || s[0] == '('){ /// sau s[0] != '|' && s[0] != '*'
		pair<node*, node*> aux = eval3(s);
		ans.second -> _next.push_back({'.', aux.first});
		ans.second = aux.second;
	}

	return ans;
}

pair<node*, node*> eval3(char* &s){
	pair<node*, node*> ans;

	if (s[0] == '('){
		s++;
		ans = eval1(s);
		s++;

		if (s[0] == '*'){
			ans.second -> _next.push_back({'.', ans.first});
			ans.second = ans.first;
			s++;
		}
	}
	else {
		ans = eval4(s);

		if (s[0] == '*'){
			ans.first -> _next[0].second = ans.first;
			delete ans.second;
			ans.second = ans.first;
			s++;
		}
	}

	return ans;
}

pair<node*, node*> eval4(char* &s){
	pair<node*, node*> ans = {new node, new node};
	ans.first -> _next.push_back({s[0], ans.second});
	s++;

	return ans;
}

void eticheteaza(node* now, int &id, vector<tuple<int, char, int>> &edges){
	now -> _id = id;

	for(auto it : now -> _next){
		if (it.second -> _id == 0){
			id++;
			eticheteaza(it.second, id, edges);
		}
		edges.push_back(make_tuple(now -> _id, it.first, it.second -> _id));
	}
}

int main(){
	ifstream in ("test.in");
	ofstream out ("test.out");
	string s; in >> s;

	char* aux = new char[s.size() + 1];
	strcpy(aux, s.c_str());
	pair<node*, node*> ans = eval1(aux);
	
	int node_count = 1;
	vector<tuple<int, char, int>> edges;
	eticheteaza(ans.first, node_count, edges);

	out << node_count << '\n';
	for(int i = 1; i <= node_count; i++)
		out << i << ' ';
	out << '\n';

	out << "26 \n";
	for(char i = 'a'; i <= 'z'; i++)
		out << i << ' ';
	out << '\n';

	out << ans.first -> _id << "\n1\n" << ans.second -> _id << '\n';

	out << edges.size() << '\n';
	for(auto it : edges){
		out << get<0>(it) << ' ' << get<1>(it) << ' ' << get<2>(it) << '\n';
		// for(int i = 0; i < 2; i++)
			// out << get<i>(it) << ' ';
		// out << '\n';
	}

	return 0;
}

