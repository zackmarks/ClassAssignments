#include <vector>
#include <iostream>
#include <unordered_map>

using namespace std;

struct branch{
	int id;
	vector<int> neighbors;
};

// bool contains(int n, vector<int>& v){
// 	for(int i : v){
// 		if(i == n)
// 			return true;
// 	}
// 	return false; 
// }

bool branchContains(int n, branch b){
	for(int i : b.neighbors){
		if(i == n)
			return true;
	}
	return false;
}

int mapContains(int n, unordered_map<int, branch> m){
	for(auto e : m){
		if(branchContains(n, e.second))
			return e.first;
	}
	return -1;
}

void printVec(vector<int>& v){
	for(int i : v){
		cout << i << " ";
	}
}

int main(){
	unordered_map<int, branch> m;
	string s;
	int startingLoc;
	cin >> startingLoc;

	//read in data, load map
	while(getline(cin, s)){
		//cout << s << "---" << s.length() << "---" << (int)(s[0]) <<endl ;
		if(s == "-1")
			break;
		if(s == "" || (int)(s[0]) == 13)
			continue;
		branch b;
		int i;

		b.id = 1;
		b.neighbors = {};

		bool readingFirstNumber = true;
		int loc = 0;
    	string currNum = "";
    	while(loc < s.size()){
        	if(s[loc] != ' '){
				currNum += s[loc];
        	}else{
        		if(readingFirstNumber){
        			b.id = stoi(currNum);
        			readingFirstNumber = false;
        		}else{
		            b.neighbors.push_back(stoi(currNum));
        		}
    	        currNum = "";
			}
			loc++;
		}
		if(currNum.size() != 0 ){
			b.neighbors.push_back(stoi(currNum));
		}

		m[b.id] = b;
	}

	//finding path back to root
	int safeGuardCount = 9999999;
	s = ""; 
	int currBranch = startingLoc;
	while(currBranch != -1  && safeGuardCount > 0){
		s += (to_string(currBranch) + " "); 
		currBranch = mapContains(currBranch, m);
		safeGuardCount--;
	}

	cout << s;

	return 0;
}