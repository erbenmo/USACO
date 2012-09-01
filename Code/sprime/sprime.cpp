/*
PROB: sprime
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;
int N;

ifstream fin("sprime.in");
ofstream fout("sprime.out");

bool isPrime(int a) {
	int end = sqrt(a);
	for(int i=2; i<=end; i++) {
		if(a%i == 0)	return false;
	}
	return true;
}

void check(int a, int n) {
	if(n==0) {
		if(isPrime(a))	fout << a << endl;
		return;
	}

	for(int i=0; i<=9; i++) {
		if(n==N && (i==0 || i==1))	continue;
		if(isPrime(a*10+i))	check(a*10 + i, n-1);
	}
}

int main() {
	fin>>N;

	check(0, N);
}
