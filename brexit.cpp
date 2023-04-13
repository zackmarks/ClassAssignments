#include <iostream>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;

struct country{
	int id;
	vector<int> partners;
	int alivePart;
	int deadPart;
};


bool willLeave(country& c){
	return (c.deadPart >= c.alivePart);
}


int main(){
	int c, p, x, l;
	cin >> c >> p >> x >> l;
	//c = country count
	//p = partnership count
	//x = home country
	//l = leaving first country
	if(x == l){
		cout << "leave";
		return 0;
	}


	unordered_map<int, country> m;
	vector<bool> inUnion(c + 1, true);
	queue<int> q;//q holds countries to be removed

	//load country map
	for(int i = 0 ; i < c ; i++){
		country co;
		co.id = i;
		co.partners = {};
		co.alivePart = 0;
		co.deadPart = 0;
		m[i] = co;
	}
	int a, b;

	//load partnerships
	for(int i = 0 ; i < p ; i++){
		cin >> a >> b;
		m[a].partners.push_back(b);
		m[a].alivePart++;
		m[b].partners.push_back(a);
		m[b].alivePart++;
	}

	//remove leaving partners
	q.push(l);
	while(!q.empty()){
		int t = q.front();//t = id of country being removed from union
		q.pop();

		if(!inUnion[t])//dont look at countries already out of the union
			continue;
		inUnion[t] = false;
		m[t].deadPart += m[t].alivePart;
		m[t].alivePart = 0;

		for(int i : m[t].partners){
			m[i].alivePart--;
			m[i].deadPart++;
			if(willLeave(m[i])){
				q.push(i);
			}
		}
	}

	if(inUnion[x]){
		cout << "stay";
	}else{
		cout << "leave";
	}


	return 0;
}