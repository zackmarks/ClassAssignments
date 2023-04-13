#include <vector>
#include <iostream>
#include <algorithm>
#include <queue>
#include <utility>
using namespace std;


struct node{
	int id;
	bool isSink = false;
	bool isSource = false;
	vector<int> neighbors;
	vector<int> nnec;//(N,0);//neighboringNodeEdgeCapacities
	vector<int> flowOnEdge; //flow between nodes
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

int toyToNode(int toyNum, int n){
	return toyNum + n;
}

int catToNode(int catNum, int n, int m){
	return catNum + n + m;
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

	int n,m,p, k,ii,l(0),ti,r;
	cin >> n >> m >> p;
	/*
	node[0] = source
	nodes[1 : n] = kids 1-n
	nodes[n+1 : n+m] = toys 1-m
	nodes[n+m+1 : n+m+p] = categories 1-p
	node [n+m+p+1] = sink
	*/
	int size = n+m+p+2;
	int sink = size - 1;
	vector<node> nodeVec(size);

	vector<int> tempVec(size,0);
	for(int i = 0 ; i < size ; i++){
		nodeVec[i].nnec = tempVec;
		nodeVec[i].flowOnEdge = tempVec;
		nodeVec[i].id = i;
	}




	nodeVec[0].isSource = true;
	nodeVec[sink].isSink = true;
	for(int i = 1 ; i <= n ; i++){//make nodes for kids
		nodeVec[0].nnec[i] = 1;
		nodeVec[0].neighbors.push_back(i);
		nodeVec[i].neighbors.push_back(0);

		cin >> k;
		for(int j = 1 ; j <= k ; j++){
			cin >> ii;
			int toyNode = toyToNode(ii , n);
			nodeVec[i].nnec[toyNode] = 1;
			nodeVec[i].neighbors.push_back(toyNode);
			nodeVec[toyNode].neighbors.push_back(i);
		}

	}


	vector<bool> toyInCat(m+1,false);

	for(int i = 1 ; i <= p ; i++){//make nodes for toys
		cin >> l;
		int catNode = catToNode(i,n,m);
		for(int j = 1 ; j <= l ; j++){
			cin >> ti;
			int toyNode = toyToNode(ti,n);
			toyInCat[ti] = true;
			nodeVec[toyNode].neighbors.push_back(catNode);
			nodeVec[catNode].neighbors.push_back(toyNode);
			nodeVec[toyNode].nnec[catNode] = 1;
		}

		cin >> r;
		nodeVec[catNode].neighbors.push_back(sink);
		nodeVec[sink].neighbors.push_back(catNode);
		nodeVec[catNode].nnec[sink] = r;
	}


	for(int i = 1 ; i < toyInCat.size() ; i++){//make nodes for categories
		if(!toyInCat[i]){
			int toyNode = toyToNode(i,n);
			nodeVec[toyNode].neighbors.push_back(sink);
			nodeVec[sink].neighbors.push_back(toyNode);
			nodeVec[toyNode].nnec[sink] = 1;
		}
	}


	int totalFlow = 0;

	while(augPathBFS(0, nodeVec)){//do until no more augpaths
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
	cout << totalFlow << endl;

	return 0;
}
