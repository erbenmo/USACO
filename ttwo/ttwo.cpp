/*
LANG: C++
PROB: ttwo
*/
#include <iostream>
#include <fstream>

using namespace std;
ifstream fin("ttwo.in");
ofstream fout("ttwo.out");

int forest[12][12];

enum species {no, rock, john, cow};
enum direction {north, east, south, west}; 

void run(int& x, int& y, direction& dir) {
	if(dir==north && forest[x-1][y]==rock) 		{dir=east; return;}
	if(dir== east && forest[x][y+1]==rock)		{dir=south; return;}
	if(dir==south && forest[x+1][y]==rock)		{dir=west; return;}
	if(dir==west && forest[x][y-1]==rock)		{dir=north; return;}
	
	if(dir==north)	x--;
	if(dir==south)	x++;
	if(dir==west)	y--;
	if(dir==east)	y++;
	return;
}

void print() {
	for(int i=0; i<12; i++) {
		for(int j=0; j<12; j++)
			cout << forest[i][j];
		cout << endl;
	}
	exit(1);
}

int main() {

	for(int i=0; i<12; i++)	forest[i][0] = forest[i][11] = rock;
	for(int j=0; j<12; j++)	forest[0][j] = forest[11][j] = rock;

	int fi, fj, ci, cj;
	direction fdir=north, cdir=north;

	for(int i=1; i<=10; i++) {
		string cur; fin>>cur; 
		for(int j=1; j<=10; j++) {
			if(cur[j-1] == '.')	forest[i][j] = no;
			if(cur[j-1] == '*')	forest[i][j] = rock;
			if(cur[j-1] == 'F')	{forest[i][j] = john; fi=i, fj=j;} 
			if(cur[j-1] == 'C')	{forest[i][j] = cow; ci=i, cj=j;}
		}
	}
	
	int sum=0;
	while(++sum) {
		if(sum > 10000000)	{fout << 0 << endl; break;}
		run(fi, fj, fdir);
		run(ci, cj, cdir);
		if(fi==ci && fj==cj) {
			fout << sum << endl;
			break;
		}
	}
}

