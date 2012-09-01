/*
PROB: milk3
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

bool hash[210000];
int capacity[3];
vector<int> ans;

struct state {
	state(int a, int b, int c)	{data[0]=a; data[1]=b; data[2]=c;}
	int data[3];
};

int toHash(int a, int b, int c) {
	return a*10000+b*100+c;
}

void pour(int from, int to, state& cur) {
	int amount = min(cur.data[from], capacity[to]-cur.data[to]);
	cur.data[from] -= amount, cur.data[to] += amount;
}

int main() {
	ifstream fin("milk3.in");
	ofstream fout("milk3.out");

	stack<state> states;
	fin>>capacity[0]>>capacity[1]>>capacity[2];
	
	int a=0, b=0, c=capacity[2];
	state first(a, b, c); states.push(first);
	
	while(!states.empty()) {
		state cur = states.top(); states.pop();
		if(hash[toHash(cur.data[0], cur.data[1], cur.data[2])] == true)	continue;
		if(cur.data[0] == 0)	ans.push_back(cur.data[2]);	
		hash[toHash(cur.data[0], cur.data[1], cur.data[2])] = 1;

		{state tp = cur; pour(0, 1, tp); states.push(tp);}
		{state tp = cur; pour(1, 0, tp); states.push(tp);}
		{state tp = cur; pour(0, 2, tp); states.push(tp);}
		{state tp = cur; pour(2, 0, tp); states.push(tp);}
		{state tp = cur; pour(1, 2, tp); states.push(tp);}
		{state tp = cur; pour(2, 1, tp); states.push(tp);}
	}

	sort(ans.begin(), ans.end());
	if(ans.size() > 0)	fout << ans[0];
	for(int i=1; i<ans.size(); i++)	fout << " " << ans[i]; 
	fout << endl;
}

