/*
ID: erbenmo2
PROG: ride
LANG: C++
*/
#include <iostream>
#include <fstream>

using namespace std;

int count(string s) {
	int count = 1;
	for(int i=0; i<s.length(); i++) {
		count *= ((int)(s.at(i) - 'A') + 1);	
	}
	return count;
}
int main() {
	ofstream fout("ride.out");			
	ifstream fin("ride.in");

	string comet, group;
	fin >> comet >> group;

	int nComet = count(comet);
	int nGroup = count(group);

	if(nComet % 47 == nGroup % 47)	fout << "GO" << endl;
	else fout << "STAY" << endl;

	return 0;
}
