/*
PROB: preface
LANG: C++
*/
#include <iostream>
#include <fstream>

using namespace std;
ifstream fin("preface.in");
ofstream fout("preface.out");

int ins[13]={1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
int dict[13][7] = { {0, 0, 0, 0, 0, 0, 1},
					{0, 0, 0, 0, 1, 0, 1},
					{0, 0, 0, 0, 0, 1, 0},
					{0, 0, 0, 0, 1, 1, 0},
					{0, 0, 0, 0, 1, 0, 0},
					{0, 0, 1, 0, 1, 0, 0},
					{0, 0, 0, 1, 0, 0, 0},
					{0, 0, 1, 1, 0, 0, 0},
					{0, 0, 1, 0, 0, 0, 0},
					{1, 0, 1, 0, 0, 0, 0},
					{0, 1, 0, 0, 0, 0, 0},
					{1, 1, 0, 0, 0, 0, 0},
					{1, 0, 0, 0, 0, 0, 0}}
					;
int letterFreq[7]={0};
char letter[7] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'}; 
int N;


void calc(int num) {
	for(int i=0; i<13; i++) {
		while(num >= ins[i]) {
			num -= ins[i];
			for(int j=0; j<7; j++)	letterFreq[j]+=dict[i][j];
		}
	}
}

int main() {
	fin>>N;
	for(int i=1; i<=N; i++)
		calc(i);
	
	for(int i=0; i<7; i++) {
		if(letterFreq[i] > 0) {
			fout << letter[i] << " " << letterFreq[i] << endl;
		}
	}
}
