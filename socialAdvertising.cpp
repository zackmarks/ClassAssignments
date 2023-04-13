#include <iostream>
#include <vector>
using namespace std;

struct person{
	vector<int> friends;
};

void run();
void goThrough(int currPpl, int addPer, int addedPpl, vector<person>& people, int& fullPpl, int& minSize, int adGroup);


int main(){
	int c;//cases
	cin >> c;
	for(int i = 0 ; i < c ; i++){//run c code c times
		run();
	}
	return 0;
}

void run(){
	int n,d,f;
	bool quickExit = false;
	cin >> n;
	vector<person> people(n+1);
	for(int i = 1 ; i <=n ; i++){
		cin >> d;
		if(d + 1 == n)
			quickExit = true;
		for(int j = 0 ; j < d ; j++){//push back friends to each person
			cin >> f;
			people[i].friends.push_back(f);
		}
	}
	if(quickExit){//if person p is friends w all, give ad to p
		cout << "1\n";
		return;
	}

	int fullPpl = (1 << (n+1)) - 2;
	int minSize = n;
	goThrough(0, 1, 0, people, fullPpl, minSize,0);
	cout << minSize << endl;
	return;
}

void goThrough(int currGroup, int addPer, int currSize, vector<person>& ppl, int& fullPpl, int& minSize, int adGroup){
	//0/1 int of ppl in friend group, next person to add to friend group, size of group given ads, all people
	//int of the complete set of people for comparison, size of smallest complete group, 0/1 of ppl getting the ad


	if(currGroup == fullPpl){//all ppl already in group
		minSize = min(minSize, currSize);
		return;
	}

	if(currSize > minSize){//a smaller ad group already exists
		return;
	}

	if(addPer >= ppl.size()){//after the last person and not all people are in currGroup. end
		return;
	}

	//main cases


	//dont add the person to the group
	goThrough(currGroup, addPer + 1, currSize, ppl, fullPpl, minSize, adGroup);
	

	int addedFriend = 1 << addPer;
	int newGroup = currGroup;
	newGroup |= addedFriend;
	adGroup |= addedFriend;

	//add the person to the group
	//int newGroup = currGroup;
	for(int f : ppl[addPer].friends){
		addedFriend = 1 << f;
		newGroup |= addedFriend;
	}

	if(newGroup == fullPpl){//all ppl already in group
		minSize = min(minSize, currSize+1);
		return;
	}

	goThrough(newGroup, addPer + 1, currSize + 1, ppl, fullPpl, minSize, adGroup);
	return;
}
