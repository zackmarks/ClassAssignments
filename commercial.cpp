//Zack Marks
//CS130B
//Radio Commercial

#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main(){
	ios_base::sync_with_stdio(false); 
	cin.tie(NULL);
	cout.tie(NULL);

	int n, p, currListeners;
	cin >> n >> p;
	int bigProf(0), curProf(0), indivProf(0);
	for(int i = 0 ; i < n ; i++){
		cin >> currListeners;
		indivProf = currListeners - p;
		curProf += indivProf;
		if(curProf < 0){
			curProf = 0;
		}else if(curProf > bigProf){
			bigProf = curProf;
		}

	}
	cout << bigProf;

	return 0;
}