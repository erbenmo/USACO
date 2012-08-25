/*
PROB: money
LANG: C++
*/
#include <iostream>
#include <fstream>

using namespace std;
ifstream fin("money.in");
ofstream fout("money.out");
int V, N;
int coin[25] = {0};
long long hash[25][10001] = {0};

long long calc(int start, int num) {
	if(start == V)	return 0;
	if(num<0)		return 0;
	if(num==0)		return 1;
	if(hash[start][num] != -1)
					return hash[start][num];
	
	hash[start][num] = calc(start+1, num) + calc(start, num-coin[start]);
	return hash[start][num];

}
int main() {
	fin>>V>>N;
	for(int i=0; i<V; i++)	fin>>coin[i];
	for(int i=0; i<25; i++)
		for(int j=0; j<10001; j++)
			hash[i][j] = -1;

	for(int i=V-1; i>=0; i--)
		for(int j=0; j<=N; j++)
			calc(i, j);

	fout << hash[0][N] << endl;
}
