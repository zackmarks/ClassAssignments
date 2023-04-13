#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

int main(){
	int n;
	int a;
	int count = 0;
	vector<int> v;
	cin >> n;
	for(int i = 0 ; i < n ; i++){
		cin >> a;
		v.push_back(a);
	}
	vector<int> sorted = v;
	sort(sorted.begin(), sorted.end());
	int greatestSoFar = INT_MIN;
	for(int i = 0 ; i < n ; i++){
		if(v[i] >= greatestSoFar && v[i] == sorted[i]){
			count++;
		}
		greatestSoFar = max(greatestSoFar, v[i]);
	}
	cout << count;
}