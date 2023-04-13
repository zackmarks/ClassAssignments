#include <iostream>
#include <cmath>
using namespace std;
int main(){
	//find difference between input n and d, where d is the highest number divisible by n
	int n, counter(1);

	cin >> n;
	if(n == 1){
		cout << 0;
		return 0;
	}

	int s = sqrt(n);
	for(int i = 2 ; i <= s ; i++){
		if(n%i == 0){
			counter = n-n/i;
			cout << counter;
			return 0;
		}
	}
	cout << n-1;

	return 0;
}