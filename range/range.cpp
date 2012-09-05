/*
PROB: range
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <assert.h>

using namespace std;
ifstream fin("range.in");
ofstream fout("range.out");

#define cin fin
#define cout fout

bool green[250][250];
int N;

int main() {
  cin>>N;
  char c;
  cin.read(&c, 1);
  for(int i=0; i<N; i++) {
    for(int j=0; j<N; j++) {
      cin.read(&c, 1);
      green[i][j] = (c=='1');
    }
    cin.read(&c, 1);
  }
 
  for(int i=2; i<=N-1; i++) {
    int result = 0;

    for(int y=0; y<=N-i; y++) {
      for(int x=0; x<=N-i; x++) {
	green[y][x] = green[y][x] && green[y+1][x]
	  && green[y][x+1] && green[y+1][x+1];

	if(green[y][x]) result++;
      }      
    }

    if(result != 0)
      cout << i << " " << result << endl;
    else
      return 0;
  }
}
