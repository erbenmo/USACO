/*
PROB: concom
LANG: C++
*/
#include <iostream>
#include <fstream>

using namespace std;
ifstream fin("concom.in");
ofstream fout("concom.out");

double control[100][100];

int main() {
	for(int i=0; i<100; i++)
		for(int j=0; j<100; j++)
			control[i][j] = 0;

	int N; fin>>N;
	for(int i=0; i<N; i++) {
		int a, b; fin>>a>>b; a--, b--;
		double c; fin>>c; c/=100;
		control[a][b] = c;
	}
	
	bool ok=false;
	while(!ok) {
		ok=true;
		for(int i=0; i<100; i++) {
			for(int j=0; j<100; j++) {
				if(control[i][j] > 0.5)	continue;
				double sum=0;
				for(int k=0; k<100; k++) {
					if(control[i][k] > 0.5)	sum += control[k][j];
				}
				control[i][j] = sum;
				if(control[i][j] > 0.5)	ok=false;
			}
		}
	}


	for(int i=0; i<100; i++)
		for(int j=0; j<100; j++)
			if(control[i][j] > 0.5 && i!=j)	fout << i+1 << " " << j+1 << endl;
}
