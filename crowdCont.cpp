//Zack Marks
//CS130B
//Crowd

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <utility>
#include <queue>
#include <unordered_map>
using namespace std;

struct Intersection{
	int id;
	vector<int> connections;
	vector<int> streets;
	bool visited;
};

struct Street{
	int capacity;
	int id;
	vector<int> intersections;
};

vector<int> streetOrder;

bool operator<(const Street& s1, const Street& s2){
    return s1.capacity < s2.capacity;
}

bool operator<(const pair<Street, int>& s1, const pair<Street, int>& s2){
	if(s1.first.capacity == s2.first.capacity)
		return (streetOrder[s1.second] > streetOrder[s2.second]);
    return s1.first.capacity < s2.first.capacity;
}

int getSameInt(int a, int b, vector<Street>& sts){//returns the common intersection of two streets
	Street sA = sts[a];
	Street sB = sts[b];
	if(sA.intersections[0] == sB.intersections[0] || sA.intersections[0] == sB.intersections[1])
		return sA.intersections[0];
	if(sA.intersections[1] == sB.intersections[0] || sA.intersections[1] == sB.intersections[1])
		return sA.intersections[1];	
	cout << "\nISSUE";
	return -1;
}

bool touches0(Street& s){
	return (s.intersections[0] == 0 || s.intersections[1] == 0);
}

int getOtherInt(Street& s, int intA){
	if(s.intersections[0] == intA)
		return s.intersections[1];
	if(s.intersections[1] == intA)
		return s.intersections[0];
	cout << "\nISSUE";
	return -1;}

void printVec(vector<int>& v){
	for(int e : v){
		cout << e << " ";
	}
}



int main(){
	ios_base::sync_with_stdio(false); 

	int streets, intersections;
	cin >> intersections >> streets;

	vector<Intersection> ins;//holds Intersections
	vector<Street> sts; // holds streets
	bool visited[streets] = {false}; //holds the streets that were visited
	int parentSt[streets] = {-1}; //holds the street's predecessor sts
	int parentIn[streets] = {-1}; //holds the street's predecessor ins
	int dijCap[streets] = {-1}; //holds the street's highest low point
	int intsParSt[intersections] = {-1}; //holds the intersection's parent street
	streetOrder.resize(streets, 0);
	int streetOrderCounter = 1;

	for(int i = 0 ; i < streets ; i++){
		visited[i] = false;
		parentSt[i] = -1;
		parentIn[i] = -1;
		dijCap[i] = -1;
	}

	//add intersections, don't provide any info
	for(int i = 0 ; i < intersections ; i++){
		Intersection in = {i, {}, {}, false};
		ins.push_back(in);
		parentIn[i] = -1;
		parentSt[i] = -1;
	}

	//read in streets
	int a,b,c;
	for(int i = 0 ; i < streets; i++){
		cin >> a >> b >> c;
		Street st = {c, i, {min(a,b), max(a,b)}};
		sts.push_back(st);
		ins[a].connections.push_back(b);
		ins[b].connections.push_back(a);
		ins[a].streets.push_back(i);
		ins[b].streets.push_back(i);
	}


	//start some form of Dijkstras, but instead of summing distance, 
	priority_queue<pair<Street, int>> dijQ;
	for(int i : ins[0].streets){
		Street stPoint = sts[i];
		dijQ.push({stPoint, -1});
		dijCap[i] = sts[i].capacity; //ignores -1s, sets capacity
	}

	while(!dijQ.empty()){
		Street curr = dijQ.top().first;
		int currId = curr.id;
		int visitFrom = dijQ.top().second;//street being visited from
		dijQ.pop();
		if(visited[currId]){
			continue;
		}
		visited[currId] = true;

		//update vars if first time touching
		if(visitFrom != -1 && touches0(sts[currId]) && touches0(sts[visitFrom])){//touches ins 0, not from ins[0]
			parentIn[currId] = getSameInt(currId, visitFrom, sts);
			parentSt[currId] = visitFrom;
			dijCap[currId] = min(curr.capacity, dijCap[visitFrom]);
			intsParSt[getOtherInt(curr, parentIn[currId])] = currId;
		}else if(touches0(curr)){//from ins[0]
			parentIn[currId] = 0;
			parentSt[currId] = -1;
			dijCap[currId] = curr.capacity;
			intsParSt[getOtherInt(curr, 0)] = currId;
		}else if(parentSt[currId] == -1){// doesn't touch ins[0], never visited
			parentSt[currId] = visitFrom;
			dijCap[currId] = min(curr.capacity, dijCap[visitFrom]);
			parentIn[currId] = getSameInt(currId, visitFrom, sts);
			intsParSt[parentIn[currId]] = visitFrom;
			intsParSt[getOtherInt(curr, parentIn[currId])] = currId;
		}

		streetOrder[currId] = streetOrderCounter;
		streetOrderCounter++;

		if(curr.intersections[0] == intersections-1 || curr.intersections[1] == intersections-1)
			break;

		//push neighbor streets
		for(int i : sts[currId].intersections ){
			for(int j : ins[i].streets){
				if(!visited[j]){
					dijQ.push({sts[j], currId});
				}
			}
		}
	}

 	int backTracking = intsParSt[intersections-1];
 	int count = 0;
 	unordered_map<int, int> stsTaken;
 	unordered_map<int, int> intsTouched;
 	unordered_map<int, int> stsTouched;

 	while(count < intersections && backTracking != -1 ){
 		intsTouched[sts[backTracking].intersections[0]] = 1;
 		intsTouched[sts[backTracking].intersections[1]] = 1;
 		stsTaken[backTracking] = 1;//backTracking;
 		backTracking = parentSt[backTracking];
 		count++;
 	}

 	for(auto e : intsTouched){
 		for(int s : ins[e.first].streets){
 			if(stsTaken[s] == 0)
 				stsTouched[s] = s;
 		}
 	}

 	vector<int> finalVec;
 	for(auto e : stsTouched){
 		finalVec.push_back(e.first);
 	}

 	if(finalVec.size() == 0){
 		cout << "none";
 	}else{
 		sort(finalVec.begin(), finalVec.end());
 		printVec(finalVec);	
 	}
	return 0;
}
