#include <iostream>
#include <vector>

using namespace std;

enum State {
  ZERO,
  A1,
  B1,
  B2,
  B3,
  C1,
  C2,
  C3
};

struct Node {
  vector<int> sq;
  State state;
};

void print(const Node& n) {
  for(int i=0; i<4; i++) cout << n.sq[i];
  cout << endl;
  for(int i=0; i<4; i++) cout << n.sq[7-i];
  cout << endl;
  cout << n.state << endl;
}

Node A(Node n) {
  for(int i=0; i<4; i++) swap(n.sq[i], n.sq[7-i]);
  return n;
}

Node B(Node n) {
  int temp = n.sq[0];
  n.sq[0] = n.sq[3];
  n.sq[3] = n.sq[2];
  n.sq[2] = n.sq[1];
  n.sq[1] = temp;

  temp = n.sq[7];
  n.sq[7] = n.sq[4];
  n.sq[4] = n.sq[5];
  n.sq[5] = n.sq[6];
  n.sq[6] = temp;
  return n;
}

Node C(Node n) {
  int temp = n.sq[1];
  n.sq[1] = n.sq[6];
  n.sq[6] = n.sq[5];
  n.sq[5] = n.sq[2];
  n.sq[2] = temp;
  return n;
}


int main() {
  Node n;
  for(int i=0; i<8; i++) n.sq.push_back(i+1);
  n.state = ZERO;
  print(n);

  print(A(n));
  print(B(n));
  print(C(n));
}
