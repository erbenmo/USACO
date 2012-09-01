/*
PROB: barn1
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <assert.h>
using namespace std;

struct empty {
	int front;
	int tail;
	int length;
};

empty holes[201];
bool isEmpty[201];
int main() {
	ifstream fin("barn1.in");
	ofstream fout("barn1.out");
	int M, S, C;
	int start, end;
	int prev = 201;
	int idx = 0;		// number of holes!
	fin>>M>>S>>C;
	M--;
	
	for(int i=0; i<C; i++) {
		int cur;
		fin>>cur;
		isEmpty[cur] = true;
	}

	for(int i=0; i<=201; i++) {
		if(isEmpty[i] == false)	continue;
		int cur = i;
		cout << cur << "		" << prev << endl;
		if(cur-1 > prev) {
			empty hole;
			hole.front = prev+1;
			hole.tail = cur-1;
			hole.length = cur-prev-1;
			holes[idx] = hole;
			idx++;
		}
		prev = cur;
	}

	for(int i=0; i<idx; i++) {
		for(int j=i+1; j<idx; j++) {
			if(holes[j].length < holes[i].length) {
				swap(holes[i].length, holes[j].length);
			}
		}
	}

	int count = C;
	for(int i=0; i<idx-M; i++)	count += holes[i].length;
	fout << count << endl;
//	cout << count << endl;
}
