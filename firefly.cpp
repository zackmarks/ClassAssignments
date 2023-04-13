#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;


int main(){
    int n,h,a;
    cin >> n >> h;

    vector<int> v;
    vector<int> fromTop (h+1,0);
    vector<int> fromBottom (h+1,0);
    int bestLevelCount(0), bestBreaks(INT_MAX);

    for(int i = 0 ; i < n ; i++){
        cin >> a;
        v.push_back(a);
        if(i%2 == 0)
            fromBottom[a]++;
        else
            fromTop[h-a]++;
    }


    //check minbreaks from top
    //sum up all breaks fromtop greater, frombottom lesser
    vector<int> breaks;
    int break0 = 0;
    for(int i : fromBottom){
        break0 += i;
    }
    breaks.push_back(break0);

    for(int i = 1 ; i <= h ; i++){
        int currBreak = breaks[i-1] + fromTop[i-1] - fromBottom[i-1];
        breaks.push_back(currBreak);
        if(currBreak < bestBreaks){
            bestBreaks = currBreak;
            bestLevelCount = 1;
        }else if(currBreak == bestBreaks){
            bestLevelCount++;
        }
    }
    cout << bestBreaks << " " << bestLevelCount;

    return 0;
}