#include <iostream>
#include <vector>

using namespace std;
int findLeftChild(int n){
	return 2*n;
}

int findRightChild(int n){
	return 2*n + 1;
}

int findParent(int n){
	return n/2;
}

bool isLeft(int n){
	return (n%2 == 0);
}

bool isRight(int n){
	return (n%2 == 1);
}


void flip(vector<int>& m, int loc, int N){
	loc += N;
	int diff = (m[loc] == 0) ? 1 : -1;
	while(loc >= 1){
		m[loc] += diff;
		loc = findParent(loc);
	}
}

int query(int l, int r, vector<int>& m, int N){
	int lSum(0), rSum(0);
	l += N - 1;
	r += N + 1;
	while(l/2 != r/2){
		if(isLeft(l))
		//if(l%2 == 0)
			lSum += m[l+1];
		//if(r%2 == 0)
		if(isRight(r))
			rSum += m[r-1];

		l /= 2;
		r /= 2;
	}
	return lSum + rSum;
}


int main(){
	int n,k,N(1);
	cin >> n >> k;


	while(N < n+2){
		N *= 2;
	}
	vector<int> digits(2*N + 1,0);
	//start as all 0s, so no reason to fill in
	char c;
	int a,b;
	for(int i = 0 ; i < k ; i++){
		cin >> c;
		cin >> a;
		if(c == 'F'){
			flip(digits, a, N);
		}else if(c == 'C'){
			cin >> b;
			cout << query(a,b,digits, N) << endl;
		}

	}

	return 0;
}