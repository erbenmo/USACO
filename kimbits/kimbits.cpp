/*
PROB: kimbits
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

ofstream fout("kimbits.out");
ifstream fin("kimbits.in");

// hash[A][B]: string of length A, with <= B 1's. How many such string?
// A >= B
unsigned int hash[32][32];

int main() {
  int N, L;
  unsigned int I;
  fin>>N>>L;
  fin>>I;
  
  for(int a=0, b=0; a<32; a++)
    hash[a][b] = 1;
  for(int a=0; a<32; a++)
    for(int b=a; b<32; b++)
      hash[a][b] = 1 << a;
    
  for(int a=1; a<32; a++) {
    for(int b=1; b<a; b++) {
      hash[a][b] = hash[a-1][b] + hash[a-1][b-1];
    }
  }

  vector<bool> ans;
  while(N > 0) {
    unsigned int w_0 = hash[N-1][L];
    unsigned int w_1 = hash[N-1][L-1];

    if(I <= w_0) {
      ans.push_back(0);
    }
    else {
      ans.push_back(1);
      I -= w_0;
      L--;
    }

    N--;
  }

  for(int i=0; i<ans.size(); i++)
    fout << ans[i];
  fout << endl;
}
