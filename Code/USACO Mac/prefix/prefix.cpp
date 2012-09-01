/*
PROB: prefix
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
ifstream fin("prefix.in");
ofstream fout("prefix.out");

vector<string> dict;
string cur = "";
int dat[200000] = {0};
int cumuMax[200000] = {0};
int SIZE;

int calc(int start) {
	if(start >= SIZE) return 0;
	if(dat[start] != 0)	return dat[start];

	int noSkip = 0;
	for(int i=0; i<dict.size(); i++) {
		int localMax, length = dict[i].length();
		if(start + length > cur.length())	continue;
		bool ok = true;
		for(int j=0; ok && j<length; j++) {
			if(cur[start+j] != dict[i][j])
				ok = false;
		}
		if(!ok)	continue;
		localMax = length + calc(start+length);
		noSkip = max(localMax, noSkip);
	}
	dat[start] = noSkip;
	return dat[start];
}

int main() {
	string src, curLine;
	while(fin>>src && src!=".")	
		dict.push_back(src);
	while(fin>>curLine && curLine!="")
		{cur+=curLine; curLine="";}
	SIZE = cur.length();

	int maxV = -1;
	for(int i=SIZE-1; i>=0; i--)	calc(i);

	fout << calc(0) << endl;

}
