/*
PROB: hamming
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <vector>


using namespace std;
typedef vector<int> vi;
ifstream fin("hamming.in");
ofstream fout("hamming.out");

int N, B, D, limit;
bool table[256][266] = {false};
vi ans;

bool good(int i, int j) {
	int c = i^j;
	int cnt=0;
	for(int i=0; i<B; i++)
		if((c>>i)&1 == 1)	cnt++;
	
	return cnt>=D;
}

void build() {
	for(int i=0; i<limit; i++) {
		for(int j=i+1; j<limit; j++) {
			if(good(i, j))	table[i][j] = table[j][i] = true; 
		}
	}
}

void calc(int rest) {
	if(rest==0)	return;

	int i=ans[ans.size()-1]+1;
	for(; i<limit; i++) {
		bool ok=true;
		for(int idx=0; ok && idx<ans.size(); idx++) {
			if(!table[i][ans[idx]])	{
				ok=false;
			}
		}

		if(ok) {
			ans.push_back(i);
			break;
		}
	}

	if(i==limit) {
		printf("BAD! i:%d, limit:%d\n", i, limit);
		exit(1);
	}
	calc(rest-1);
}

int main() {
	fin>>N>>B>>D;
	limit=(1<<B);
	build();
	
	ans.push_back(0);
	calc(N-1);

	for(int i=0; i<N; i++) {
		if(i%10!=0)	fout << " ";
		fout<<ans[i];
		if((i+1)%10==0 || i==N-1)	fout << endl;
	}
}
