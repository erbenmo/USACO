/*
PROB: palsquare
LANG: C++
*/
#define pb push_back
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
char dict[11] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K'};
ifstream fin("palsquare.in");
ofstream fout("palsquare.out");

void run(int num, int B) {
	int cur = num*num;	
	vector<int> res;
	
	while(cur != 0) {
		res.pb(cur % B);
		cur /= B;
	}
	reverse(res.begin(), res.end());
	
	for(int i=0; i<res.size(); i++)
		if(res[i] != res[res.size() - 1 - i])
			return;
	
	vector<int> nonres;
	while(num != 0) {
		nonres.pb(num % B);
		num /= B;
	}
	reverse(nonres.begin(), nonres.end());

	for(int i=0; i<nonres.size(); i++) {
		if(nonres[i] <= 9)	fout << nonres[i];
		else	fout << dict[nonres[i] - 10];
	}
	fout << " ";
	for(int i=0; i<res.size(); i++) {
		if(res[i] <= 9)	fout << res[i];
		else	fout << dict[res[i] - 10];
	}
	fout << endl;
}

int main() {
	int B; fin>>B;

	for(int i=1; i<300; i++) {
		run(i, B);
	}

	return 0;
}
