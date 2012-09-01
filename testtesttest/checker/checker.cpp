/*
PROB: checker
LANG: C++
*/
#include <iostream>
#include <fstream>

using namespace std;


int N, total=0;
bool luHash[25] = {0};
bool ruHash[25] = {0};
bool colHash[13] = {0};
int ans[13];

int times = 3;

ifstream fin("checker.in");
ofstream fout("checker.out");


bool okay(int n, int i) {
	int lu = n-i+N-1;
	int ru = n+i;

	return ((luHash[lu] == 0) && (ruHash[ru] == 0) && (colHash[i] == 0));
}

void mark(int n, int i) {
	ans[n] = i;
	int lu = n-i+N-1;
	int ru = n+i;
	luHash[lu] = 1;
	ruHash[ru] = 1;
	colHash[i] = 1;
}

void unmark(int n, int i) {
	int lu = n-i+N-1;
	int ru = n+i;
	luHash[lu] = 0;
	ruHash[ru] = 0;
	colHash[i] = 0;
}

void search(int n) {
	if(n==N) {
		total++;
		if(times> 0) {
			fout << ans[0]+1;
			for(int i=1; i<N; i++)	fout << " " << ans[i]+1;
			fout << endl;
			times--;
		}
		return;
	}
	
	int start = 0;
	if(n == N-1 && N!=6)	start = ans[0]+1;
	
	for(int i=start; i<N; i++) {
		if(!okay(n, i))
			continue;
		mark(n, i);
		search(n+1);
		unmark(n, i);
	}

}



int main() {
	fin>>N;

	search(0);
	if(N==6)	fout << total << endl;
	else		fout << total*2 << endl;
}

