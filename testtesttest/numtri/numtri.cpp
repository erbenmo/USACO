/*
PROB: numtri
LANG: C++
*/
#include <iostream>
#include <fstream>

using namespace std;

int well[1000][1000];
int hash[1000][1000] = {0};
int N;

ifstream fin("numtri.in");
ofstream fout("numtri.out");

int main() {
	fin>>N;

	for(int i=0; i<N; i++) {
		for(int j=0; j<i+1; j++) {
			fin>>well[i][j];
		}
	}

	for(int i=N-1; i>=0; i--) {
		for(int j=0; j<i+1; j++) {
			if(i==N-1) {
				hash[i][j] = well[i][j];
			} else {
				hash[i][j] = well[i][j] + (max(hash[i+1][j], hash[i+1][j+1]));
			}
		}
	}

	fout << hash[0][0] << endl;
}
