/*
PROB: calfflac
LANG: C++
*/
#include <iostream>
#include <string>
#include <fstream>
#include <assert.h>

using namespace std;

int maxLength = -1, startIdx = -1, endIdx = -1;
int N;
string text = "";

bool isLetter(char c) {
	return (c<='z' && c>='a') || (c<='Z' && c>='A');
}

bool charComp(char a, char b) {
	return a==b || (a-b == 32);
}

void run(int start, int end, int length) {
	int idx = start;
	start--, end++;
	do {
		while(start>=0 && !isLetter(text[start]))	start--;
		while(end<=N-1 && !isLetter(text[end]))	end++;
		
		if(start == -1 || end == N) break; 
		else if(!charComp(text[start], text[end]))	break;
		length += 2;

	} while(charComp(text[start--], text[end++]));

	if(length > maxLength) {
		startIdx = start, endIdx = end;
		maxLength = length;
	}
}

int main() {
	ifstream fin("calfflac.in");
	ofstream fout("calfflac.out");
	string cur;

	while(fin.good()) {
		getline(fin, cur);
		text+=cur;
	}
	
	N = text.length();
	int start, end;
	for(int idx=0;idx<N-1; idx++) {
		if(isLetter(text[idx]) == false) continue;
		// single core
		run(idx, idx, 1);
		// double core
		cout << idx << "	" << idx+1 << endl;
		if(charComp(text[idx], text[idx+1]))	{
			run(idx, idx+1, 2);
		}
	}

	fout << maxLength << endl;
	for(int i=startIdx; i<=endIdx; i++)	fout << text[i];
	cout << maxLength << endl;
	for(int i=startIdx; i<=endIdx; i++)	cout << text[i];
	cout << endl;
	fout << endl;
}
