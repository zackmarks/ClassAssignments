//Zack Marks
//CS130B
//Bank Queue

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;

struct Person{
	int cash;
	int time;
};

bool sortPpl(Person& a, Person& b){
	return (a.cash > b.cash);
}

void fillArr(int loc, vector<int>& v, int& sum, int cash){
	while(v[loc] != 0 && loc >= 0){
		loc--;
	}
	if(loc != -1){
		v[loc] = cash;
		sum += cash; 
	}
}


int main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL);
	cout.tie(NULL);


	//sort people by cash, put each person in the last available slot


	int n, t;
	cin >> n >> t;
	vector<Person> vec;
	int ci, ti;
	for(int i = 0 ; i < n ; i++){
		cin >> ci >> ti;
		Person p = {ci, ti};
		vec.push_back(p);
	}
	sort(vec.begin(), vec.end(), sortPpl);



	int sum = 0;
	vector<int> money;
	money.resize(t,0);
	for(int i = 0 ; i < n ; i++){
		fillArr(min(t,vec[i].time), money, sum, vec[i].cash);
	}
	cout << sum;
	return 0;
}