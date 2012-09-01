/*
PROB: lamps
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <string>
#include <map>

using namespace std;
ifstream fin("lamps.in");
ofstream fout("lamps.out");
enum state{off, on, any};

bool lamps[101];
int req[101];
int loop[16][4] = { {0}, {1}, {2}, {3}, {4},
					{1,2}, {1,3}, {1,4}, {2,3}, {2,4}, {3,4},
					{1,2,3}, {1,2,4}, {1,3,4}, {2,3,4},
					{1,2,3,4}};
int loopsize[16] = {0, 1, 1, 1, 1, 2, 2, 2, 2, 2, 2, 3, 3, 3, 3, 4};
int N, C;
bool virgin=true;
map<string, bool> hash;


void perform(int id) {
	if(id==1) {
		for(int i=1; i<=N; i++)	lamps[i] = 1-lamps[i];	
	}
	if(id==2) {
		for(int i=1; i<=N; i+=2)	lamps[i] = 1-lamps[i];
	}
	if(id==3) {
		for(int i=2; i<=N; i+=2)	lamps[i] = 1-lamps[i];
	}
	if(id==4) {
		for(int i=1; i<=N; i+=3)	lamps[i] = 1-lamps[i];
	}
}

void calc(int seq[4]) {
	for(int i=0; i<4; i++) {
		if(seq[i]==0)	continue;
		perform(seq[i]);
	}
}

string toHash() {
	string temp="";
	for(int i=1; i<=N; i++)	temp+=(lamps[i])? "1":"0";
	return temp;
}

void check() {
	if(hash[toHash()] == 1)	return;

	bool ok=true;
	for(int i=1; ok && i<=N; i++) {
		if(req[i]==any)	continue;
		if(req[i]!=lamps[i])	{ok=false;}
	}

	hash[toHash()] = ok;
	if(ok)	virgin=false;
}

int main() {
	fin>>N>>C;	
	for(int i=1; i<101; i++)	{lamps[i]=on, req[i]=any;}	
	int id;
	while(fin>>id && (id!=-1))	req[id]=on;
	while(fin>>id && (id!=-1))	req[id]=off;
	
	for(int i=0; i<16; i++) {
		if(loopsize[i]>C)	continue;

		calc(loop[i]);
		check();

		for(int i=1; i<101; i++)	lamps[i]=on;
	}
	if(virgin)	
		fout << "IMPOSSIBLE\n";
	else {
		for(map<string, bool>::iterator it=hash.begin(); it!=hash.end(); it++)	
			if(it->second == true)	fout << it->first << endl;
	}
}
