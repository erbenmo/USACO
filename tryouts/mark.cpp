#include <iostream>

using namespace std;

int main() {
	int total;
	cin>>total;
	int i = 0;
	while(total--) {
		i++;
		cout << "Case #" << i << ": ";
		int N, pd, pg;
		cin>>N>>pd>>pg;
		if(pd==100 || pg==100) {
			cout << "Possible\n";
		} else {
		bool possible = (int)(N*pd / 100) / (100 - pg) * 100 > N;
		if(!possible)	cout <<"Possible\n";
		else cout << "Broken\n";
		}
	}

}
