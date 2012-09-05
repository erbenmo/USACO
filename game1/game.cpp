/*
  PROB: game1
  LANG: C++
*/
#include <iostream>
#include <fstream>

using namespace std;
ifstream fin("game1.in");
ofstream fout("game1.out");
#define cin fin
#define cout fout

int f[100][100];
int sum[100][100];
int v[100];
int N;

int main() {
  cin>>N;
  for(int i=0; i<N; i++) cin>>v[i];
  for(int i=0; i<N; i++) sum[i][i] = v[i];
  
  for(int l=1; l<N; l++)
    for(int i=0; i+l<N; i++)
      sum[i][i+l] = sum[i][i+l-1] + v[i+l];

  for(int l=0; l<N; l++) {
    for(int i=0; i+l<N; i++) {
      if(l == 0)
	f[i][i] = v[i];
      int lv, rv, j = i+l;
      lv = v[i] + sum[i+1][j]-f[i+1][j];
      rv = v[j] + sum[i][j-1]-f[i][j-1];
      f[i][j] = max(lv, rv);
    }
  }

  cout << f[0][N-1] << " " << sum[0][N-1] - f[0][N-1] << endl;
}
