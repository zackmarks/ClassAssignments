#include <vector>
#include <string>
#include <iostream>
#include <queue>
using namespace std;

struct node{
	vector<int> pathsTo;
	int topoIncoming = 0;
};

void topoSort(vector<int>& nodeOrder, vector<node>& nodes){
	queue<int> q;
	for(int i = 0 ; i < nodes.size() ; i++){
		if(nodes[i].topoIncoming == 0)
			q.push(i);
	}

	while(!q.empty()){
		int t = q.front();
		q.pop();
		nodeOrder.push_back(t);
		for(int to : nodes[t].pathsTo){
			nodes[to].topoIncoming--;
			if(nodes[to].topoIncoming == 0){
				q.push(to);
			}
		}
	}
}


int main(){
	/*
	overall strategy:
	nodes are the locations that are either interesting or uninteresting. they have paths between them (not needed as an abstract data structure)
	isInteresting holds bool values representing if the ith node is interesting. score has the interesting-ness score for each node
	nodeOrder holds the topoOrder of the nodes. this is guaranteed to exist, since paths are directional and no loops exist (given)
	nodes holds the nodes

	program first reads in the string and marks each node as interesting or not
	then reads in the paths and fills in the info to the nodes. then toposorts into nodeOrder

	Loop goes through the nodes in the topo order. 
	add represents the interestingness additional value of the visited neighboring node. 
	each go through the loop updates the neighboring node approprietly (+1 if interesting, -1 if not, 0 is start or end node)
	updates the neighboring node based on whatever is more interesting, current value or prev value + new interestingness addition
	*/

	int v,e,add,e1,e2;
	string x;
	cin >> v >> e;
	cin >> x;
	vector<bool> isInteresting(v,false);
	vector<int> score(v,-999999);
	score[0] = 0;
	vector<int> nodeOrder;
	vector<node> nodes(v);


	for(int i = 0 ; i < v ; i++){
		if(x[i] == 'X')
			isInteresting[i] = true;
	}

	for(int i = 0 ; i < e ; i++){
		cin >> e1 >> e2;
		nodes[e2].topoIncoming++;
		nodes[e1].pathsTo.push_back(e2);
	}

	topoSort(nodeOrder, nodes);

	for(int i = 0 ; i < nodeOrder.size() ; i++){
		int currNode = nodeOrder[i];
		for(int to : nodes[currNode].pathsTo){
			if(to == v-1 || to == 0)
				add = 0;
			else if(isInteresting[to])
				add = 1;
			else
				add = -1;
			
			score[to] = max(score[to], score[currNode] + add);
		}
	}
	cout << score[v-1];

	return 0;
}