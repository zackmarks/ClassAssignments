//Zack Marks
//CS130B
//NarrowUsingArtGallery

#include <iostream>
#include <vector>
#include <climits>
using namespace std;

vector<vector<int>> gal; 
vector<vector<vector<int>>> partialSumArray;

int minOf3(int a, int b, int c){
	int small = a;
	if(b < small)
		small = b;
	if(c < small)
		small = c;
	return small;
}

int getMin(int kLeft , int rowUsing, bool usingR, int arr[][rowUsing][2]){
	if (rowUsing < 0)//used all rows. go back
		return INT_MAX;
	if(kLeft == 0)//no rooms left to close off
		return 0;
	if(arr[kLeft][rowUsing][usingR] != 0)//already did this
		return arr[kLeft][rowUsing][usingR];

	arr[kLeft][rowUsing][usingR]= minOf3(getMin(arr[kLeft-1][rowUsing-1][usingR], arr) + gal[rowUsing][usingR], getMin(kLeft, rowUsing-1, usingR, arr) , getMin(kLeft, rowUsing-1, !usingR, arr));
	//										choose curr room										dont choose, look same dir			dont choose look opp dir
	return partialSumArray[kLeft][rowUsing][usingR];
}


int main(){
	ios_base::sync_with_stdio(false); 
	//cin.tie(NULL);
	//cout.tie(NULL);

	int n, k;
	cin >> n >> k;
	int sum = 0;
	int a,b;
	for(int i = 0 ; i < n ; i++){
		cin >> a >> b;
		vector<int> temp {a,b};
		gal.push_back(temp);
		sum += a + b;
	}

	//now calculate min taken away
	//int partialSumArray[k+1][n][2];
	vector<vector<vector<int>>> partialSumArray;
	vector<int> in1 = {-1,-1};
	vector<vector<int>> in2;
	for(int i = 0 ; i < n ; i++){
		in2.push_back(in1);
	}
	for(int i = 0 ; i < k ; i++){
		partialSumArray.push_back(in2);
	}


	int minUsed = min(getMin(k, n-1, true , partialSumArray) , getMin(k, n-1, false , partialSumArray));
	cout << (sum - minUsed);

	return 0;
}