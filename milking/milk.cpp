/*
LANG: C++
PROB: milk2
*/
#define pb push_back
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

bool comparePair(pair<int, int>a, pair<int, int>b) {
	return a.first < b.first;
}

int main() {
	int N;
	vector<pair<int, int> > plan;
	ifstream fin("milk2.in");
	ofstream fout("milk2.out");

	fin>>N;
	for(int i=0; i<N; i++) {
		int start, end;
		fin>>start>>end;
		plan.pb(make_pair(start, end));
	}

	sort(plan.begin(), plan.end(), comparePair);	
	int longestFull = -1, longestEmpty= 0;
	int next = 0;
	int count = 0, start = -1, end = -1;
	int lastEnd = plan[0].first;

	while(true) {
		if(next >= plan.size())	{
			if(count > longestFull)	{
				longestFull = count;
			}
			break;
		}
		if(end == -1) {
			end = plan[next].second;
			start = plan[next].first; 
			if(start - lastEnd > longestEmpty) {
				longestEmpty = start - lastEnd;
			}
		} else if(end >= plan[next].first) {
			if(plan[next].second >= end) {
				end = plan[next].second;
			}
		} else {
			if(count > longestFull)	{
				longestFull = count;
			}
			next--;
			lastEnd = end;
			start = -1, end = -1;
		}

		count = end - start;
		next++;
	}

	fout << longestFull << " " << longestEmpty << endl;
}
