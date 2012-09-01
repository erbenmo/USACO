#include <iostream>
#include <fstream>

using namespace std;

long long table [200][100];
long long smaller [200][100]; 	// num of binary tree with n nodes and depth smaller than d.
int N, K;
long long calcmin(int n, int k);
long long calc(int n, int k);

long long calcmin(int n, int k) {
//	cout << "calcmin begin! with " << n << "  " << k << endl;
	if(smaller[n][k] != -1)	return smaller[n][k];

	long long total = 0;
	for(int i=1; i<=k; i++) {
		total += calc(n, i);
	}
	
	smaller[n][k] = total;
	printf("min n: %d, k: %d, value: %d\n", n, k, total);
	return smaller[n][k];
}

long long calc(int n, int k) {
	bool debug=(n==11 && k==4);

	if(n==1 && k==1)	return 1;
	if(n > (1<<k)-1)	return 0;	
	if(table[n][k] != -1)	return table[n][k];	


	n--, k--;					// get rid of root...

	long long total = 0;
	long long left = 0, right = 0;
	for(int i=2*k-1; i<=n-1; i+=2) {
		left = calc(i,k);
		right = calcmin(n-i, k);
		if(i!=n-i)	total += 2*left*right;
		else		total += left*right;

		if(debug)	cout << i << "  " << k << "  " << left << "  " << right << "  " << total << endl;
	}

	printf("n: %d, k: %d value: %d\n", n+1, k+1, total);
	table[n+1][k+1] = total;
	return table[n+1][k+1];
}

int main() {
	cin>>N>>K;
	for(int i=0; i<200; i++)
		for(int j=0; j<100; j++)
			table[i][j] = smaller[i][j] = -1;

	calc(N, K);
	cout << table[N][K] % 9901 << endl;
}
