#define pb push_back
#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

int N;
vector<vector<char> > data;
vector<vector<char> > sample;

int main() {
	string temp;
	ifstream("transform.in");
	ofstream("transform.out");
	cin>>N;

	for(int i=0; i<N; i++) {
		vector<char> row;
		cin>>temp;
		for(int i=0; i<N; i++) row.pb(temp.at(i));	
		data.pb(row);
	}

	
	for(int i=0; i<N; i++) {
		vector<char> row;
		cin>>temp;
		for(int i=0; i<N; i++) row.pb(temp.at(i));	
		sample.pb(row);
	}
	
	if(equal())	fout << 6 << endl;	


}
