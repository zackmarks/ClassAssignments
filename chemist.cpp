#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <queue>
using namespace std;

void fillMap(unordered_map<string, bool>& isElement);

void goThroughVec(vector<bool>& v){
	for(bool b : v){
		if(b)
			cout << "YES\n";
		else
			cout << "NO\n";
	}
}

int main(){
	ios::sync_with_stdio(false);
	cout.tie(NULL);

	int t, size;
	cin >> t;
	string curr, temp;

	vector<bool> ans(t,false);
	unordered_map<string, bool> isElement;
	fillMap(isElement);

	for(int i = 0 ; i < t ; i++){
		queue<int> q;//holds current startings loc of search 
		q.push(0);
		cin >> curr;
		size = curr.size();
		vector<bool> usedNumber(size,false);

		bool notAtEnd = true;
		while(!q.empty() && notAtEnd){
			//if size == 3, highest number in q should be 2 
			int f = q.front();
			q.pop();
			if(usedNumber[f])
				continue;
			usedNumber[f] = true;
			//cout << "\nreading from " << f;

			if(f >= size){//got to the end, all accounted for. shouldn't actually get here, but i have this just in case
				ans[i] = true;
				notAtEnd = false;
			}else if(f+1 == size){//checking last character
				temp = curr.substr(f,1);
				if(isElement[temp]){
					ans[i] = true;
					notAtEnd = false;
				}
			}else if(f+2 == size){//checking second to last character
				temp = curr.substr(f,2);
				if(isElement[temp]){//got to end
					ans[i] = true;
					notAtEnd = false;
				}
				temp = curr.substr(f,1);
				if(isElement[temp]){
					q.push(f+1);
				}
			}else{//normal case
				temp = curr.substr(f,1);
				if(isElement[temp])
					q.push(f+1);
				temp = curr.substr(f,2);
				if(isElement[temp])
					q.push(f+2);
			}
		}
	}


	goThroughVec(ans);
	return 0;
}


void fillMap(unordered_map<string, bool>& isElement){
	isElement["h"] = true;
	isElement["he"] = true;
	isElement["li"] = true;
	isElement["be"] = true;
	isElement["b"] = true;
	isElement["c"] = true;
	isElement["n"] = true;
	isElement["o"] = true;
	isElement["f"] = true;
	isElement["ne"] = true;
	isElement["na"] = true;
	isElement["mg"] = true;
	isElement["al"] = true;
	isElement["si"] = true;
	isElement["p"] = true;
	isElement["s"] = true;
	isElement["cl"] = true;
	isElement["ar"] = true;
	isElement["k"] = true;
	isElement["ca"] = true;
	isElement["sc"] = true;
	isElement["ti"] = true;
	isElement["v"] = true;
	isElement["cr"] = true;
	isElement["mn"] = true;
	isElement["fe"] = true;
	isElement["co"] = true;
	isElement["ni"] = true;
	isElement["cu"] = true;
	isElement["zn"] = true;
	isElement["ga"] = true;
	isElement["ge"] = true;
	isElement["as"] = true;
	isElement["se"] = true;
	isElement["br"] = true;
	isElement["kr"] = true;
	isElement["rb"] = true;
	isElement["sr"] = true;
	isElement["y"] = true;
	isElement["zr"] = true;
	isElement["nb"] = true;
	isElement["mo"] = true;
	isElement["tc"] = true;
	isElement["ru"] = true;
	isElement["rh"] = true;
	isElement["pd"] = true;
	isElement["ag"] = true;
	isElement["cd"] = true;
	isElement["in"] = true;
	isElement["sn"] = true;
	isElement["sb"] = true;
	isElement["te"] = true;
	isElement["i"] = true;
	isElement["xe"] = true;
	isElement["cs"] = true;
	isElement["ba"] = true;
	isElement["la"] = true;
	isElement["ce"] = true;
	isElement["pr"] = true;
	isElement["nd"] = true;
	isElement["pm"] = true;
	isElement["sm"] = true;
	isElement["eu"] = true;
	isElement["gd"] = true;
	isElement["tb"] = true;
	isElement["dy"] = true;
	isElement["ho"] = true;
	isElement["er"] = true;
	isElement["tm"] = true;
	isElement["yb"] = true;
	isElement["lu"] = true;
	isElement["hf"] = true;
	isElement["ta"] = true;
	isElement["w"] = true;
	isElement["re"] = true;
	isElement["os"] = true;
	isElement["ir"] = true;
	isElement["pt"] = true;
	isElement["au"] = true;
	isElement["hg"] = true;
	isElement["tl"] = true;
	isElement["pb"] = true;
	isElement["bi"] = true;
	isElement["po"] = true;
	isElement["at"] = true;
	isElement["rn"] = true;
	isElement["fr"] = true;
	isElement["ra"] = true;
	isElement["ac"] = true;
	isElement["th"] = true;
	isElement["pa"] = true;
	isElement["u"] = true;
	isElement["np"] = true;
	isElement["pu"] = true;
	isElement["am"] = true;
	isElement["cm"] = true;
	isElement["bk"] = true;
	isElement["cf"] = true;
	isElement["es"] = true;
	isElement["fm"] = true;
	isElement["md"] = true;
	isElement["no"] = true;
	isElement["lr"] = true;
	isElement["rf"] = true;
	isElement["db"] = true;
	isElement["sg"] = true;
	isElement["bh"] = true;
	isElement["hs"] = true;
	isElement["mt"] = true;
	isElement["ds"] = true;
	isElement["rg"] = true;
	isElement["cn"] = true;
	//isElement["nh"] = true;
	isElement["fl"] = true;
	//isElement["mc"] = true;
	isElement["lv"] = true;
	//isElement["ts"] = true;
	//isElement["og"] = true;
}