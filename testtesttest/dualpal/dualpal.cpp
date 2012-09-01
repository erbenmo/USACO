/*
PROG: dualpal
LANG: C++
*/
#define pb push_back
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ifstream fin("dualpal.in");
ofstream fout("dualpal.out");

bool run(int num) {
	int B = 1;
	int shot = 0;
	int cur = num;

	while(shot < 2 && ++B <= 10) {
		bool ok = true; 
		vector<int> res;
		cur = num;	

		while(cur != 0) {
			res.pb(cur % B); 
			cur /= B;
		}
		reverse(res.begin(), res.end());
		
		for(int i=0; i<res.size() && ok; i++)
			if(res[i] != res[res.size() - 1 - i]) {
				ok = false;
			}
		
		if(ok)	{
			shot++;
		}
	}

	if(shot == 2)	return true;
	else return false;
}



int main() {
	int N, S, cur;
	fin>>N>>S;	
	cur = S+1;

	while(N>0) {
		if(run(cur)) {
			fout << cur << endl;
			N--;
		}
		cur++;
	}
}
