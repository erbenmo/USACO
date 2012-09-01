/*
PROB: pprime
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;

int low, high, a;
ifstream fin("pprime.in");
ofstream fout("pprime.out");

bool isPrime(int a) {
	int end = sqrt(a);	
	for(int i=2; i<=end; i++)	
		if(a%i == 0)	return false;
	return true;
}

void test() {
	if(a<low || a>high)	return;
	if(isPrime(a))	fout << a << endl;
}

int main() {
	fin>>low>>high;

	for(int i=1; i<=9; i+=2) {
		a = i*1;
		test();
	}

	a = 11;
	test();

	for(int i=1; i<=9; i+=2) {
		for(int j=0; j<=9; j++) {
			a = i*100 + j*10 + i;
			test();
		}
	}

	for(int i=1; i<=9; i+=2) {
		for(int j=0; j<=9; j++) {
			for(int k=0; k<=9; k++) {
				a = i*10000 + j*1000 + k*100 + j*10 + i;
				test();
			}
		}
	}


	for(int i=1; i<=9; i+=2) {
		for(int j=0; j<=9; j++) {
			for(int k=0; k<=9; k++) {
				for(int l=0; l<=9; l++) {
					a = i*1000000 + j*100000 + k*10000 + l*1000 + k*100 + j*10 + i;
					test();
				}
			}
		}
	}
}
