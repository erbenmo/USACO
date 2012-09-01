/*
LANG: C++
PROB: agrinet
*/
#include <iostream>
#include <fstream>
#define LARGEDIST 100000000

using namespace std;
ifstream fin("agrinet.in");
ofstream fout("agrinet.out");
int N;
int LEN = 0;
int rdist[100][100];
int circlem[100];


void update(int id) {
	circlem[id] = -2;
	for(int i=0; i<N; i++) {
		if(circlem[i] == -2)	continue;
		circlem[i] = min(circlem[i], rdist[id][i]);
	}
}

int findNext(int& id) {
	int curmin = LARGEDIST; 
	id = -1;
	for(int i=0; i<N; i++) {
		if(circlem[i] == -2)	continue;
		if(circlem[i] < curmin) {
			curmin = circlem[i];
			id = i;
		}
	}
}

int main() {
	fin>>N;
	for(int i=0; i<N; i++)
		for(int j=0; j<N; j++)
			fin>>rdist[i][j];
	for(int i=0; i<100; i++)	circlem[i] = LARGEDIST;	

	int cur = 0;
	while(true) {
		update(cur);
		findNext(cur);
		if(cur == -1)	break;
		LEN += circlem[cur]; 
	}

	fout << LEN << endl;	
}
