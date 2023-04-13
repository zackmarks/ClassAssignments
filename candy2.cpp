#include <iostream>
#include <cmath>
using namespace std;

long long gcd2(long long a, long long b);
void invMod(long long a, long long b);

int main(){
	int t;
	long long k,c;
	cin >> t;
	for(int i = 0 ; i < t ; i++){
		cin >> k >> c;
		if(c == 1){//one candy per bag. get k+1 bags
			cout << k+1 << endl;
		}else if(k == 1){//one kid gets k-1 candies, 1 extra
				cout << "1\n";
		}else{
			invMod(c,k);
		}
	}
	return 0;
}

long long gcd2(long long a, long long b) {    
	while (b != 0) {
		long long temp = b;
		b = a % b;
		a = temp;
	}
	return a;
}

long long gcd3(long long a, long long b){
	if(a%b == 0)
		return b;
	return gcd3(b,a%b);
}

void invMod(long long a, long long b){
	long long gcd = gcd2(a,b);
	if(gcd != 1){
		cout << "IMPOSSIBLE\n";
		return;
	}
	long long origB (b), c(0), d(1), e(1), f(0), g(0), h(0);
	while(b > 0){
		g = a/b;
		h = b;
		b = a % b;
		a = h;

		h = c;
		c *= g * -1;
		c += d;
		d = h;

		h = e;
		e *= g * -1;
		e += f;
		f = h;
	}
	h = d % origB;
	if(h < 0)
		h += origB;
	cout << h << endl;
	return;
}
