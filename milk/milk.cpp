/*
PROB: milk
LANG: C++
*/
#define pb push_back
#include <iostream>
#include <fstream>

using namespace std;

struct cow{
	int price;
	int amount;
};


int main() {
	cow data[5000];
	int amount, N, cost;
	ifstream fin("milk.in");
	ofstream fout("milk.out");
	fin>>amount>>N;

	for(int i=0; i<N; i++) {
		cow cur;
		fin>>cur.price>>cur.amount;
		data[i] = cur;
	}

	for(int i=0; i<N; i++) {
		for(int j=i+1; j<N; j++) {
			if(data[j].price < data[i].price) {
				int t = data[j].price; data[j].price = data[i].price; data[i].price = t;
				t = data[j].amount; data[j].amount= data[i].amount; data[i].amount= t;
			}
		}
	}


	int idx = 0;
	while(amount != 0) {
		cow cur = data[idx];
		int curAmount = min(amount, cur.amount);
		cost += curAmount * cur.price;
		amount -= curAmount;
		idx++;
	}

	fout << cost << endl;
	return 0;
}
