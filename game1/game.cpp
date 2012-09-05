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
bool choice[100][100]; // T:Left - F:Right
int v[100];
int N;

void print() {
  for(int i=0; i<N; i++) {
    for(int j=0; j<N; j++) {
      cout << f[i][j] << " ";
    }
    cout << endl;
  }
  cout << "-----\n";
}

int main() {
  cin>>N;
  for(int i=0; i<N; i++) cin>>v[i];
  for(int i=0; i<N; i++) sum[i][i] = v[i];
  
  for(int l=1; l<N; l++)
    for(int i=0; i+l<N; i++)
      sum[i][i+l] = sum[i][i+l-1] + v[i+l];

  for(int l=0; l<N; l++) {
    for(int i=0; i+l<N; i++) {
      if(l == 0) {
	f[i][i] = v[i];
	choice[i][i] = true;
      } else if(l == 1) {
	f[i][i+1] = max(v[i], v[i+1]);
	choice[i][i+1] = (v[i] >= v[i+1]);
      } else {
	int lv, rv, j = i+l;

	// for lv
	if(choice[i+1][j]) lv = v[i] + f[i+2][j];
	else lv = v[i] + f[i+1][j-1];

	// for rv
	if(choice[i][j-1]) rv = v[j] + f[i+1][j-1];
	else rv = v[j] + f[i][j-2];

	f[i][j] = max(lv, rv);
	choice[i][j] = (lv >= rv);
      }
    }
  }

  cout << f[0][N-1] << " " << sum[0][N-1] - f[0][N-1] << endl;
}
