#include <iostream>
#include <vector>
#include <queue>
using namespace std;

vector<vector<bool>> visited;

struct location{
	int y;
	int x;
};


bool isLegalJump(vector<vector<int>>& v, int yLoc, int xLoc){//returns true if v[yLoc][xLoc] is in v
	int maxX = v[0].size();
	int maxY = v.size();
	return (xLoc >= 0 && xLoc < maxX) && (yLoc >= 0 && yLoc < maxY);
}


void fillOceanWater(vector<vector<int>>& v, int yLoc, int xLoc, queue<location>& squares){
	//turning all ocean water to 3
	if(visited[yLoc][xLoc])//prevents repeats and infinite recursion
		return;
	if(v[yLoc][xLoc] != 0)//dont change land or ocean
		return;
	//if function gets here, current square is ocean
	visited[yLoc][xLoc] = true;
	v[yLoc][xLoc] = 3;

	location l;
	if(isLegalJump(v, yLoc+1, xLoc) && !visited[yLoc+1][xLoc]){//can go down
		l.y = yLoc+1;
		l.x = xLoc;
		squares.push(l);
	}
	if(isLegalJump(v, yLoc, xLoc+1) && !visited[yLoc][xLoc+1]){//can go right
		l.y = yLoc;
		l.x = xLoc+1;
		squares.push(l);
	}
	if(isLegalJump(v, yLoc-1, xLoc) && !visited[yLoc-1][xLoc]){//can go up
		l.y = yLoc-1;
		l.x = xLoc;
		squares.push(l);
	}
	if(isLegalJump(v, yLoc, xLoc-1) && !visited[yLoc][xLoc-1]){//can go left
		l.y = yLoc;
		l.x = xLoc-1;
		squares.push(l);
	}
	return;
}


int main(){
	int x(0), y(0);
	char le(' ');
	cin >> y >> x;
	vector<vector<int>> v;
	vector<int> topBottom(x+2,0); 
	v.push_back(topBottom);
	vector<bool> boolTopBottom(x+2, false);
	visited.push_back(boolTopBottom);
	visited.push_back(boolTopBottom);


	//load map. add a ring of water around it
	for(int i = 1 ; i <= y ; i++){
		v.push_back({0});
		visited.push_back(boolTopBottom);
		for(int j = 0 ; j < x ; j++){
			cin >> le;
			v[i].push_back(le-'0');
		}
		v[i].push_back(0);
	}
	v.push_back(topBottom);
	queue<location> squares;


	//with the ring of water, (0,0) is guaranteed to be ocean
	location l;
	l.y = 0;
	l.x = 0;
	squares.push(l);
	l.y = y+1;
	l.x = x+1;
	squares.push(l);

	
	//turn ocean squares into a 3
	while(!squares.empty()){
		location l = squares.front();
		squares.pop();
		fillOceanWater(v, l.y, l.x, squares);
	}

	int coastline = 0;
	//calc total length, including lakes
	for(int i = 1 ; i <= y ; i++){
		v.push_back({});
		for(int j = 1 ; j <= x ; j++){
			if(v[i][j] != 1)//ignore ocean. only counting land coastline
				continue;
			coastline += (v[i-1][j] == 3);//up
			coastline += (v[i+1][j] == 3);//down
			coastline += (v[i][j-1] == 3);//left
			coastline += (v[i][j+1] == 3);//right
		}
	}

	cout << coastline << endl;
	return 0;
}