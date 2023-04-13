#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;
void run(int n, int m);
bool pathsIntersect(int xA, int yA, int xB, int yB);
void goThrough(vector<int> usedLines, vector<vector<bool>>& board, int xCoord, int yCoord, int n, int& count);

int main(){
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	int n,m;
	cin >> n >> m;
	while(n != 0 || m != 0){
		run(n,m);
		cin >> n >> m;
	}
	return 0;
}

void run(int n, int m){
	vector<vector<bool>> board(n, vector<bool>(n, false));
	vector<int> usedLines = {0, 0, 0, 0};
	int xi,yi;
	for(int i = 0 ; i < m ; i++){
		cin >> xi >> yi;
		board[yi][xi] = true;
	}

	int count = 0;
	goThrough(usedLines, board, 0,0,n, count);
	cout << count << endl;
}

void goThrough(vector<int> usedLines, vector<vector<bool>>& board, int xCoord, int yCoord, int n, int& count){
	if(xCoord == n){//passed the right side of the board. success
		count++;
		return;
	}
	if(xCoord > n){return;}//past end. shouldn't ever happen. just for safety
	if(yCoord >= n){return;}//reached the bottom of the board without adding a queen. end

	//dont add a queen. go to next y coord
	goThrough(usedLines, board, xCoord, yCoord+1, n, count);

	//several checks for if the current square isnt a hole and if no colinear queens already added
	if(board[yCoord][xCoord])
		return;


	int x = 1 << xCoord;
	if((x | usedLines[0]) == usedLines[0])//that x already used
		return;

	int y = 1 << yCoord;
	if((y | usedLines[1]) == usedLines[1])//that y already used
		return;

	int diag0 = 1 << (xCoord + yCoord);
	if((diag0 | usedLines[2]) == usedLines[2])//that diagonal already used
		return;

	int diag1 = 1 << (n - 1 + yCoord - xCoord);
	if((diag1 | usedLines[3]) == usedLines[3])//that diagonal already used
		return;

	usedLines[0] |= x; 
	usedLines[1] |= y;
	usedLines[2] |= diag0;
	usedLines[3] |= diag1;

	//success. add queen, go to next xCoord
	goThrough(usedLines, board, xCoord+1, 0, n, count);
	
	return;
}

