/*
LANG: C++
PROB: contact
*/
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>
#include <map>
#include <cmath>
#include <vector>

using namespace std;
ifstream fin("contact.in");
ofstream fout("contact.out");

struct comp {
	bool operator() (const int& a, const int &b) const
	{return a>b;}
};

bool bs[200000];
map<int, int> hash;
map<int, vector<int>, comp> inverted;

int A, B, N;
int len = 0;

int b2i(bool* b, int size) {
	int rst=1;
	for(int i=0; i<size; i++) {
		rst = rst*2 + b[i];
	}
	return rst;
}

void parse(int cur) {
	int bytenumber = (int) log2(cur) + 1;
	for(int i=bytenumber-2; i>=0; i--)
		if((cur>>i) & 1 == 1)	fout << 1;
		else					fout << 0;
}

int main() {
	fin>>A>>B>>N;
	string curl;
	while(getline(fin, curl)) {
		for(int i=0; i<curl.length(); i++) {
			bs[len++] = (curl[i] == '1');
		}
	}

	for(int i=0; i<len; i++) {
		for(int l=A; l<=B; l++) {
			if(i+l-1 > len-1)	continue;

			int curId = b2i(bs+i, l);
			hash[curId]++;
		}
	}

	for(map<int, int>::iterator it = hash.begin(); it != hash.end(); it++) {
		inverted[(*it).second].push_back((*it).first);		
	}

	int n = 1;
	for(map<int, vector<int>, comp>::iterator it = inverted.begin(); it != inverted.end(); it++) {
		fout << (*it).first << endl;

		bool virginagain = true;
		int count = 0;
		for(int i=0; i<(*it).second.size(); i++) {
			
			if(count++ == 6) {
				count = 1;
				fout << endl;
			} else {
				if(!virginagain)	fout << " ";
				else				virginagain=false;
			}

			parse((*it).second[i]);
		}

		fout << endl;
		if(n++ == N)	break;
	}
		
}
