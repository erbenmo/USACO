/*
PROB: frac1
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <map>
#include <cmath>
#include <algorithm>


using namespace std;

ifstream fin("frac1.in");
ofstream fout("frac1.out");

struct frac {
	frac(){};
	frac(int u, int d) {up=u, down=d, value=1.0*up/down;}
	int up;
	int down;
	double value;
};

map<double, bool> hash;
frac ans[40000];

void simplify(int& a, int& b) {
	int common=2;
	while(common<min(sqrt(a)+1, sqrt(b)+1)) {
		if(a%common == 0 && b%common == 0) {
			a/=common, b/=common;
		} else {
			common++;
		}
	}
}

bool frac_sort(frac l, frac r) {
	return l.value < r.value;
}

int main() {
	int N, numAns = 0;
	fin>>N;

	for(int i=0; i<=N; i++) {
		for(int j=i; j<=N; j++) {
			if(j==0)	continue;
			if(hash[1.0*i/j] == 0) {
				hash[1.0*i/j] = 1;
				frac cur(i, j);
				ans[numAns++] = cur;
			}
		}
	}

	cout << "end!\n";
	sort(ans, ans+numAns, frac_sort);
	
	for(int i=0; i<numAns; i++) {
		fout << ans[i].up << "/" << ans[i].down << endl;
	}
}
