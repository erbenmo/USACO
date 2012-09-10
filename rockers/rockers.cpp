/*
  PROB: rockers
  LANG: C++
 */
#include <iostream>
#include <fstream>
using namespace std;

ifstream fin("rockers.in");
ofstream fout("rockers.out");
#define cin fin
#define cout fout

int N, T, M;
int len[21];
int data[21][21][21];


int main() {
  cin>>N>>T>>M;
  for(int i=0; i<N; i++) cin>>len[i+1];

  for(int m=1; m<=M; m++) {
    // init
    for(int t=0; t<=T; t++) data[m][0][t] = 0;
    for(int n=0; n<=N; n++) data[m][n][0] = data[m-1][n][T];

    for(int n=1; n<=N; n++) {
      for(int t=1; t<=T; t++) {
	int pick, skip_bag, skip_song;
	pick = skip_bag = skip_song = -1;
	
	if(t >= len[n])
	  pick = data[m][n-1][t-len[n]]+1;
	skip_bag = data[m-1][n][T];
	skip_song = data[m][n-1][t];

	data[m][n][t] = max(max(pick, skip_bag), skip_song);
      }
    }

    /*
    for(int n=1; n<=N; n++) {
      for(int t=0; t<=T; t++) {
	cout << data[m][n][t] << " ";
      }
      cout << endl;
    }
    cout << endl;
    */
  }

  cout << data[M][N][T] << endl;
}
