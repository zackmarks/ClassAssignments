#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <utility>
#include <climits> 
using namespace std;


struct node{
	int id;
	bool isSink = false;
	bool isSource = false;
	vector<int> neighbors;
	vector<int> nnec;//(N,0);//neighboringNodeEdgeCapacities
	vector<int> flowOnEdge; //flow between nodes
	vector<int> enteringEdges;
	vector<int> leavingEdges;
	int par = -1;
};

struct edgesUsed{
	int nodeFrom;
	int nodeTo;
	int flowOnEdge;
};


int augPathBFS(int source, vector<node>& nodeVec){//check if an augmented path exists
	queue<int> q;
	q.push(source);
	vector<bool> vis(nodeVec.size(), false);
	vis[source] = true;
	while(!q.empty()){
		int f = q.front();
		q.pop();
		if(nodeVec[f].isSink)
			return true;
		for(int ne : nodeVec[f].neighbors){//direction doesnt matter
			int ca = nodeVec[f].nnec[ne];
			if(ca <= 0 || vis[ne])//ensures that paths arent doubled and only viable paths are taken
				continue;
			q.push(ne);
			nodeVec[ne].par = f;
			vis[ne] = true;
		}
	}
	return false;
}


void printVec(vector<int> v){
	cout << endl;
	for(int i : v){
		cout << i << endl;
	}
}


int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n, m, source, sink;
	cin >> n >> m >> source >> sink;

	if(source == sink){//edge case
		cout << "2 0 0";
		return 0;
	}

	vector<node> nodeVec(n);
	nodeVec[source].isSource = true;
	nodeVec[sink].isSink = true;

	vector<int> tempVec(n,0);
	for(int i = 0 ; i < n ; i++){
		nodeVec[i].nnec = tempVec;
		nodeVec[i].flowOnEdge = tempVec;
		nodeVec[i].id = i;
	}

	int a, b, c;
	for(int i = 0; i < m; i++){
		cin >> a >> b >> c;
		nodeVec[a].nnec[b] = c;
		nodeVec[a].neighbors.push_back(b);
		nodeVec[b].neighbors.push_back(a);
		nodeVec[a].leavingEdges.push_back(i);
		nodeVec[b].enteringEdges.push_back(i);
	}


	int totalFlow = 0;

	while(augPathBFS(source, nodeVec)){//do until no more augpaths
		int chokepointVal = 99999999;
		int curr = sink;
		while(!nodeVec[curr].isSource){//trace back path, find the chokepoint
			int par = nodeVec[curr].par;
			int ca = nodeVec[par].nnec[curr];
			chokepointVal = min(ca,chokepointVal);
			curr = par;
		}
		curr = sink;
		while(!nodeVec[curr].isSource){//adjust the path by the chokepoint val
			int par = nodeVec[curr].par;
			nodeVec[par].flowOnEdge[curr] += chokepointVal;
			nodeVec[curr].flowOnEdge[par] -= chokepointVal;
			nodeVec[par].nnec[curr] -= chokepointVal;
			nodeVec[curr].nnec[par] += chokepointVal;
			curr = par;
		}
		totalFlow += chokepointVal;
	}

	//printing
	vector<edgesUsed> ed;
	edgesUsed e;
	for(int i = 0 ; i < n ; i++){//go through flow on edge list, check if pos, add to vec if so
		for(int j = 0 ; j < n ; j++){
			if(i == j)
				continue;
			if(nodeVec[i].flowOnEdge[j] > 0){
				e.nodeFrom = i;
				e.nodeTo = j;
				e.flowOnEdge = nodeVec[i].flowOnEdge[j];
				ed.push_back(e);
			}
		}
	}

	cout << n << " " << totalFlow << " " << ed.size();
	for(edgesUsed e : ed){
		cout << endl << e.nodeFrom << " " << e.nodeTo << " " << e.flowOnEdge;
	}

	return 0;
}
