//creating a mst of secure buildings, then adding in secure ones 
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <utility>
#include <unordered_map>
using namespace std;


struct path{
	int lo;
	int hi;
	int cost;
};

struct building{
	int id;
	vector<int> neighbors;
	int costHere = -1;
	vector<path> paths;
	bool insecure = false;
};


bool operator<(const path& s1, const path& s2){
    return s1.cost > s2.cost;
}

int main(){
	int builCount, connCount, insecCount;
	cin >> builCount >> connCount >> insecCount;
	int secureCount = builCount - insecCount;
	int cost = 0;
	int doubleInsecCost = 0;


	vector<bool> insecures(builCount+1,false);
	vector<bool> inMST(builCount+1, false);
	unordered_map<int, building> m;
	vector<path> insecurePaths;


	int a, b, c;
	for(int i = 0 ; i < insecCount ; i++){
		cin >> a;
		insecures[a] = true;
	}

	if(secureCount == 0){//special cases
		if(builCount == 1){
			cout << 0;
		}else if(builCount == 2){
			int a;
			cin >> a;
			cin >> a;
			cin >> a;
			cout << a;
		}else if(insecCount >= 3){
		//all paths are insecures, more than 3, need all buildings to be connected
		//since no two paths go between the same 2 buildings, we know the max path count is n*(n-1)/2
		//if connCount == that, we good. if not, impossible
			if((builCount*(builCount-1))/2 != connCount){
				cout << "impossible";
				return 0;
			}//all paths are accounted for. return sum and end.
			int doubleInsecCost = 0;
			int a;
			for(int i = 0 ; i < connCount ; i++){
				cin >> a;
				cin >> a;
				cin >> a;
				doubleInsecCost += a;
			}
			cout << doubleInsecCost;
		}
		return 0;
	}
	for(int i = 0 ; i < connCount ; i++){//load in connections, fill out data structures
		cin >> a >> b >> c;
		path p;
		p.lo = min(a,b);
		p.hi = max(a,b);
		p.cost = c;

		if(insecures[a] || insecures[b]){// >= one of the end points is insecure. exclude from big grid for now.
			if(builCount == 2 || !insecures[a] || !insecures[b])//use insecure paths later
				insecurePaths.push_back(p);
			continue;
		}

		if(m.count(a) == 0){
			building bu;
			bu.id = a;
			m[a] = bu;
		}
		m[a].paths.push_back(p);
		m[a].neighbors.push_back(b);

		if(m.count(b) == 0){
			building bu;
			bu.id = b;
			m[b] = bu;
		}
		m[b].paths.push_back(p);
		m[b].neighbors.push_back(a);
	}


	//load first set of paths from first building for prims alg
	priority_queue<path> pq;
	int firstVisited = 1;
	for(firstVisited = 1 ; firstVisited <= builCount ; firstVisited++){
		if(!insecures[firstVisited]){
			inMST[firstVisited] = true;
			for(path pat : m[firstVisited].paths){
				pq.push(pat);
			}
			secureCount--;
			break;
		}
	}

	while(!pq.empty() && secureCount > 0){
		path pt = pq.top();
		pq.pop();
		if(inMST[pt.hi] && inMST[pt.lo])//path touches 2 buildings already in
			continue;
		if(!inMST[pt.hi]){
			for(path p1 : m[pt.hi].paths){
				if(!inMST[p1.hi] || !inMST[p1.lo])
					pq.push(p1);
			}
			inMST[pt.hi] = true;
		}
		if(!inMST[pt.lo]){
			for(path p1 : m[pt.lo].paths){
				if(!inMST[p1.hi] || !inMST[p1.lo])
					pq.push(p1);
			}
			inMST[pt.lo] = true;

		}
		cost += pt.cost;
		secureCount--;
	}

	priority_queue<path> pq2;
	for(path p1 : insecurePaths){
		pq2.push(p1);
	}
	while(!pq2.empty() && insecCount > 0){
		path pt = pq2.top();
		pq2.pop();
		if(inMST[pt.hi] && inMST[pt.lo])//path touches 2 buildings already in
			continue;
		inMST[pt.hi] = true;
		inMST[pt.lo] = true;
		cost += pt.cost;
		insecCount--;
	}
/*
	//at this point, if insecure count > 0, we need direct paths between all individual nodes
	//since no two paths go between the same 2 buildings, we know the max path count is n*(n-1)/2
	//if connCount == that, we good. if not, impossible
	if(insecCount > 0){
		if(connCount == (builCount * (builCount-1))/2){
			cout << doubleInsecCost;
		}else{
			cout << "impossible";
		}
	}else{
		cout << cost;
	}
*/


	if(insecCount > 0 || secureCount > 0)
		cout << "impossible";
	else
		cout << cost;




	return 0;
}