/*
PROB: crypt1
LANG: C++
*/
#include <iostream>
#include <fstream>
using namespace std;

int N, total=0;
int dict[10] = {0};
int cur[5];

bool check() {
	if(cur[0] == 0)	return false;
	if(cur[3] == 0)	return false;
	int up = cur[0]*100 + cur[1]*10 + cur[2]*1;
	int down = cur[3]*10 + cur[4];
	int mid1 = up*cur[3];
	int mid2 = up*cur[4];
	int final = up*down;

	if(final >= 10000)	return false;
	if(mid1 >= 1000)	return false;
	if(mid1 <= 99)		return false;
	if(mid2 >= 1000)	return false;
	if(mid2 <= 99)		return false;
	if(dict[mid1%10] == 0)			return false;
	if(dict[(mid1%100)/10] == 0)	return false;
	if(dict[mid1/100] == 0)			return false;
	if(dict[mid2%10] == 0)			return false;
	if(dict[(mid2%100)/10] == 0)	return false;
	if(dict[mid2/100] == 0)			return false;
	if(dict[final%10] == 0)			return false;
	if(dict[(final%100)/10] == 0)	return false;
	if(dict[(final%1000)/100] == 0)	return false;
	if(dict[final/1000] == 0)		return false;
	return true;
}

void helper(int curSize) {
	if(curSize == 5) {
		if(check()) total++;	
		return;
	}

	for(int i=0; i<10; i++) {
		if(dict[i] == 0)	continue;
		cur[curSize] = i;
		helper(curSize+1);
	}

}
void generate() {
	int a[5];	
	helper(0);
}

int main() {
	ifstream fin("crypt1.in");
	ofstream fout("crypt1.out");
	fin>>N;
	for(int i=0; i<N; i++) {
		int temp; fin>>temp;
		dict[temp] = 1;
	}

	generate();
	fout << total << endl;
}
