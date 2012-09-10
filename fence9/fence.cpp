/*
  PROB: fence9
  LANG: C++
 */
#include <iostream>
#include <fstream>
#include <cmath>

using namespace std;
ifstream fin("fence9.in");
ofstream fout("fence9.out");
#define cin fin
#define cout fout

const double eps = 1e-16;

int N, M, P;

bool close(double cur, double target) {
  return abs(cur-target) < eps;
}

double left_x(int y) {
  return 1.0 * N/M*y;
}

double right_x(int y) {
  return 1.0 * (N-P)*y/M+P;
}

int main() {
  cin>>N>>M>>P;

  long cows = 0;
  for(int y=1; y<M; y++) {
    double left_end = left_x(y);
    double right_end = right_x(y);
    long l, r;
	
    l = (long)(left_end+1), r = (long)right_end;
    
    if(close(left_end, l))
      l++;
    if(close(right_end, r))
      r--;


    //    cout << left_end << " -> " << l << " and " << right_end << " -> " << r << endl;
    
    if(r-l+1 > 0)
      cows += r-l+1;
    
  }

  cout << cows << endl;
}
