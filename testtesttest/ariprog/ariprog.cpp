/*
PROB: ariprog
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

bool hash[125001] = {false};
int dat[25000];
pair<int, int> ans[25000];

void mysort(int sum) {
	for(int i=0; i<sum; i++) {
		for(int j=i+1; j<sum; j++) {
			if(ans[i].second > ans[j].second)	swap(ans[i], ans[j]);
			else if(ans[i].second == ans[j].second && ans[i].first > ans[j].first)	swap(ans[i], ans[j]);
		}
	}
}

int main() {
	ifstream fin("ariprog.in");
	ofstream fout("ariprog.out");

	int N, M, total=0, largest, sum=0;
	fin>>N>>M;

	for(int i=0; i<=M; i++) {
		for(int j=0; j<=M; j++) {
			if(!hash[i*i+j*j])	dat[total++] = i*i+j*j;	
			hash[i*i+j*j] = 1;
		}
	}
	sort(dat, dat+total-1);
	largest = dat[total-1];

	for(int i=0; i<total; i++) {
		for(int j=i+1; j<total; j++) {
			int a = dat[i];
			int s = dat[j];
			int b = s-a;

			if(a+(N-1)*b > largest)	break;
			if(i+N-1 >= total)	break;

			bool ok=true;
			for(int k=2; k<=N-1; k++) {
				if(hash[a+k*b] == false) {
					ok=false;
					break;
				} 
			}
			if(ok)	ans[sum++] = make_pair(a, b);
		}
	}
	if(sum == 0){
		fout<<"NONE"<<endl;
		return 0;
	}
	mysort(sum);
	for(int i=0; i<sum; i++)	fout << ans[i].first << " " << ans[i].second << endl;
}
