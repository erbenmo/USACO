/*
PROG: namenum
LANG: C++
*/
#define pb push_back
#include <iostream>
#include <fstream>
#include <vector>
#include <set>

using namespace std;

char numMap[8][3] = {{'A', 'B', 'C'}, {'D', 'E', 'F'}, {'G', 'H', 'I'}, {'J', 'K', 'L'}, {'M', 'N', 'O'}, {'P', 'R', 'S'}, {'T', 'U', 'V'}, {'W', 'X', 'Y'}};
vector<set<string> > dict;
ofstream fout("namenum.out");
int temp = 0;
void run(string res, string numStr);
int main() {
	ifstream fin("namenum.in");
	ifstream din("dict.txt");

	for(int i=0; i<13; i++)	dict.pb(set<string>());	

	while(din.good()) {
		string word;
		getline(din, word);
		dict[word.length()].insert(word);
	}

	string numStr;
	fin>>numStr;

	run("", numStr);
	if(!temp)	fout << "NONE" << endl;
}

void run(string res, string numStr) {
	if(numStr.length() == 0) {
		if(dict[res.length()].find(res) != dict[res.length()].end()) {
			temp++;
			fout << res << endl;
		}
		return;
	}

	int cur = numStr.at(0) - '0';
	cur -= 2;

	for(int i=0; i<3; i++) {
		run(res+numMap[cur][i], numStr.substr(1));
	}
}
