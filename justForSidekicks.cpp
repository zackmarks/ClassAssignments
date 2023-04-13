#include <iostream>
#include <vector>
using namespace std;

int findLeftChild(int n){return 2*n;}
int findRightChild(int n){return 2*n + 1;}
int findParent(int n){return n/2;}
bool isLeft(int n){return (n%2 == 0);}
bool isRight(int n){return (n%2 == 1);}

void reCalcTree(vector<int>& m, int N){//recalculates the entire tree
	//m[N] through m[m.size()-1] filled in. fill in up to that backwards
	for(int i = N-1 ; i > 0 ; i--){
		m[i] = m[findLeftChild(i)] + m[findRightChild(i)];
	}
}


void replace(vector<int>& m, int loc, int newVal, int N){//replaces one gem with another
	loc += N;
	int diff = newVal - m[loc];
	while(loc >= 1){
		m[loc] += diff;
		loc = findParent(loc);
	}
}


long long int query(int l, int r, vector<int>& m, int N){//returns sum between l and r, inclusive
	long long int lSum(0), rSum(0);
	l += N - 1;
	r += N + 1;
	while(l/2 != r/2){
		if(isLeft(l))
			lSum += m[l+1];
		if(isRight(r))
			rSum += m[r-1];
		l /= 2;
		r /= 2;
	}
	return ( lSum + rSum );
}

long long int query2(int l, int r, vector<vector<int>>& v, int N, vector<int>& gemVals){ 
	long long int sum = 0;
	for(int i = 1 ; i <= 6 ; i++){
		sum += (query(l,r,v[i],N) * gemVals[i]);
	}
	return sum;
}


int main(){
	int n,q,N(1),vi;
	cin >> n >> q;

	while(N < n+2){
		N*=2;
	}

	//make 6 trees holding the amounts of each of those gems in that location
	vector<int> digits(2*N,0);
	vector<vector<int>> trees;
	for(int i = 0 ; i < 7 ; i++){
		trees.push_back(digits);
	}

	vector<int> gemVals(7);
	vector<int> gemLocs(n+1,0);
	for(int i = 1 ; i <= 6 ; i++){
		cin >> vi;
		gemVals[i] = vi;
	}

	//fill in vector
	string s;
	cin >> s;
	char ch;
	for(int i = 0 ; i < s.size() ; i++){
		ch = s[i];
		vi = (int(ch)) - '0';
		trees[vi][N+i+1] = 1;
		gemLocs[i+1] = vi;
	}

	//digits[N] through digits[digits.size()-1] filled in. fill in up to that backwards
	for(int i = 1 ; i <= 6 ; i++){
		reCalcTree(trees[i],N);
	}


	//start as all 0s, so no reason to fill in
	int a,b,c;
	for(int i = 0 ; i < q ; i++){
		cin >> a >> b >> c;
		if(a == 1){
			int currGem = gemLocs[b];
			replace(trees[currGem], b, 0, N);
			replace(trees[c],b,1,N);
			gemLocs[b] = c;
		}else if(a == 2){
			gemVals[b] = c;
		}else if(a == 3){
			cout << query2(b, c, trees, N, gemVals) << endl;
		}
	}
	return 0;
}
