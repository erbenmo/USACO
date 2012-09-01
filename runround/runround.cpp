/*
PROB: runround
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;
ifstream fin("runround.in");
ofstream fout("runround.out");

bool check(vector<int>& curWord) {
	bool hash[10] = {false};
	for(int i=0; i<curWord.size(); i++) {
		if(curWord[i] == 0)	return false;
		if(hash[curWord[i]]==true)	return false;
		hash[curWord[i]] = true;
	}

	return true;
}

bool calc(unsigned long n) {
	int cur=n, size, i=0;
	vector<int> curWord;
	vector<bool> curLoop;
	bool hash[10] = {false};

	while(cur != 0) {
		int a=cur%10;
		if(a==0)	return false;
		if(hash[a] == true)	return false;
		hash[a] = true;
		curWord.push_back(a);
		cur = (cur-a) / 10;
	}
	

	reverse(curWord.begin(), curWord.end());
	size=curWord.size();
	for(int idx=0; idx<size; idx++)	curLoop.push_back(0);

	for(int idx=0; idx<size; idx++) {
		i = (i+curWord[i]) % size;	
		curLoop[i] = true;
	}

	if(i!=0)	return false;
	for(int idx=0; idx<size; idx++)
		if(curLoop[idx]==false)
			return false;

	return true;	
}

int main() {
	unsigned long n; fin>>n; n++;
	while(calc(n)==false)
		n++;
	fout << n << endl;
}
