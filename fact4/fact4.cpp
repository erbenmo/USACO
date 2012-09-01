/*
PROG: fact4
LANG: C++
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <assert.h>

using namespace std;

ofstream fout("fact4.out");
ifstream fin("fact4.in");

int main() {
  int s;
  fin>>s;

  int twos = 0;
  int fives = 0;
  int result = 1;
  
  for(int i=1; i<=s; i++) {
    int cur = i;
    while(cur%2 == 0) {
      cur /= 2;
      twos++;
    }
    while(cur%5 == 0) {
      cur /= 5;
      fives++;
    }

    result = (result * (cur % 10)) % 10;
  }

  assert(twos >= fives);
  for(int i=0; i<twos-fives; i++)
    result = (result * 2) % 10;

  fout << result << endl;
}
