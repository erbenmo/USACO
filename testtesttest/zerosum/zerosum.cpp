/*
PROB: zerosum
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>

using namespace std;
ifstream fin("zerosum.in");
ofstream fout("zerosum.out");

int N, LEN;
char num[10] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
char src[3] = {' ', '+', '-'};

void eval(string str) {
	int sum=0, cur = 0, idx=0; bool op = true;  
	while(idx < str.length()) {
		for(; idx<str.length(); idx++) {
			if(str[idx]==' ') continue;
			if(str[idx]<='9' && str[idx]>='1')	{ cur = cur*10 + (str[idx]-'0');	}
			else	break;	
		}
		sum = (op)? (sum+cur):(sum-cur), cur = 0;
		if(idx<str.length())	op=(str[idx++] == '+'); 
	}
	if(sum==0)	fout << str << endl;
}

void search(int start, string cur) {
	if(start == LEN) {
		eval(cur);
		return;
	}
	if(start%2 == 0) {
		cur += num[start/2]; 
		search(start+1, cur);
	} else {
		for(int i=0; i<3; i++) {
			search(start+1, cur+src[i]);
		}
	}
}

int main() {
	fin>>N;
	LEN = N + N-1;
	search(0, "");
}
