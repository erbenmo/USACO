/*
PROB: sort3
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <assert.h>

using namespace std;

ifstream fin("sort3.in");
ofstream fout("sort3.out");

int N;
int length[3] = {0};
int data[1000];
int total=0;

int main() {
	fin>>N;
	for(int i=0; i<N; i++)	fin>>data[i];
	for(int i=0; i<N; i++)	length[data[i]-1]++;

	int _12=0, _13=0;
	for(int i=0; i<length[0]; i++) {
		if(data[i]==2)	_12++;
		if(data[i]==3)	_13++;
	}
	int _21=0, _23=0;
	for(int i=length[0]; i<length[0]+length[1]; i++) {
		if(data[i]==1)	_21++;
		if(data[i]==3)	_23++;
	}
	int _31=0, _32=0;
	for(int i=length[0]+length[1]; i<length[0]+length[1]+length[2]; i++) {
		if(data[i]==1)	_31++;
		if(data[i]==2)	_32++;
	}

	total+=min(_12, _21);
	total+=min(_13, _31);
	total+=min(_23, _32);


	int swap12=0, swap13=0;
	for(int i=0; i<length[0]; i++) {
		if(data[i]==2 && swap12<min(_12, _21))	{swap12++, data[i]=1;}
		if(data[i]==3 && swap13<min(_13, _31))	{swap13++, data[i]=1;}
	}

	int swap21=0, swap23=0;
	for(int i=length[0]; i<length[0]+length[1]; i++) {
		if(data[i]==1 && swap21<min(_12, _21))	{swap21++, data[i]=2;}
		if(data[i]==3 && swap23<min(_23, _32))	{swap23++, data[i]=2;}
	}

	int swap31=0, swap32=0;
	for(int i=length[0]+length[1]; i<length[0]+length[1]+length[2]; i++) {
		if(data[i]==1 && swap31<min(_13, _31))	{swap31++, data[i]=3;}
		if(data[i]==2 && swap32<min(_23, _32))	{swap32++, data[i]=3;}
	}

	int rest = 0;
	for(int i=0; i<N; i++) {
		if(i<length[0] && data[i]!=1)	rest++;
		if(i>=length[0] && i<length[0]+length[1] && data[i]!=2)	rest++;
		if(i>=length[0]+length[1] && i<length[0]+length[1]+length[2] && data[i]!=3)	rest++;
	}
	assert(rest%3==0);
	total+=rest/3*2;
	fout << total << endl;
}
