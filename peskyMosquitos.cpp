#include <iostream>
#include <vector>
#include <unordered_map>
#include <cmath>
using namespace std;

struct loc{
	float x;
	float y;
};

float dist(loc& a, loc& b){
	float dx = pow(b.x - a.x,2);
	float dy = pow(b.y - a.y,2);
	return pow(dx + dy , .5);
}

void printVec(vector<int>& v){
	for(int i : v){
		cout << i << endl;
	}
}

void printVec(vector<loc>& v){
	for(loc i : v){
		cout << i.x << "\t" << i.y << endl;
	}
}

int run();
void findCenter1(loc& a, loc& b, vector<loc>& centers);
void findCenter2(loc& a, loc& b, vector<loc>& centers, float r);
void findCenter2SameX(loc& a, loc& b, vector<loc>& centers, float r);

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);
	int n;
	cin >> n;
	vector<int> answers(n);
	for(int i = 0 ; i < n ; i++){
		//cout << endl<<"trial " << i << endl;
		answers[i] = run();
	}
	printVec(answers);
	return 0;
}

int run(){
	int m;
	float d,lx,ly,r;
	cin >> m >> d;
	float margin = pow(10,-5);
	d += margin;
	r = d / 2;
	if(m <= 1)
		return m;
	loc l;
	vector<loc> locs(m);
	for(int i = 0 ; i < m ; i++){
		cin >> lx >> ly;
		l.x = lx;
		l.y = ly;
		locs[i] = l;
	}

	//find sets of pairs that can be in the same circle
	vector<loc> centersToCheck;
	for(int i = 0 ; i < m ; i++){
		for(int j = i+1 ; j < m ; j++){
			if(dist(locs[i],locs[j]) == 0){//same point
				centersToCheck.push_back(locs[i]);
			}else if(abs(dist(locs[i], locs[j]) - d) <= margin){//extreme opposite points on circle
				findCenter1(locs[i], locs[j], centersToCheck);
			}else if(dist(locs[i], locs[j]) <= d){//points within 1 circle diameter of each other
				if(locs[i].x == locs[j].x){
					findCenter2SameX(locs[i], locs[j], centersToCheck, r);
				}else{
					findCenter2(locs[i], locs[j], centersToCheck, r);
				}
			}

		}
	}
	int bigAmt = 0;
	for(loc c : centersToCheck){//for each center, check how many locs are within r of distance
		int curAmt = 0;
		for(loc l : locs){
			if(dist(l,c) <= r)
				curAmt++;
		}
		bigAmt = max(bigAmt,curAmt);
		if(bigAmt == m)
			return m;
	}


	return max(1,bigAmt);
}

void findCenter1(loc& a, loc& b, vector<loc>& centers){
	loc c;
	c.x = (a.x + b.x)/2.0;
	c.y = (a.y + b.y)/2.0;
	centers.push_back(c);
}



void findCenter2(loc& a, loc& b, vector<loc>& centers, float r){
	//add to centers c and d, the centers of 2 circles. c and d are in line with a and b and have one of those points on the circumference
	loc c, d, e, f;
	float dx = b.x - a.x;
	float dy = b.y - a.y;
	float angle = atan(dy/dx);
	float pdx = cos(angle) * r;
	float pdy = sin(angle) * r;
	c.x = a.x + pdx;
	c.y = a.y + pdy;
	d.x = a.x - pdx;
	d.y = a.y - pdy;
	e.x = b.x + pdx;
	e.y = b.y + pdy;
	f.x = b.x - pdx;
	f.y = b.y - pdy;

	if(dist(b,c) <= 2 * r)
		centers.push_back(c);	
	if(dist(b,d) <= 2 * r)
		centers.push_back(d);	
	if(dist(a,e) <= 2 * r)
		centers.push_back(e);	
	if(dist(a,f) <= 2 * r)
		centers.push_back(f);	

}


void findCenter2SameX(loc& a, loc& b, vector<loc>& centers, float r){
	loc c, d;
	float midY = (a.y + b.y)/2;
	float midX = (a.x + b.x)/2;
	c.y = midY;
	d.y = midY;

	float distToMid = a.y - midY;
	float dx = sqrt(pow(r,2) - pow(distToMid,2));

	c.x = midX + dx;
	d.x = midX - dx;

	centers.push_back(d);
	centers.push_back(c);
	
}
