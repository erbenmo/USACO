#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <assert.h>

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
  string trans;
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

  assert(n.state != A1);
  n.state = A1;

  n.trans += "A";
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

  assert(n.state != B3);
  if(n.state == B1)
    n.state = B2;
  else if(n.state == B2)
    n.state = B3;
  else
    n.state = B1;

  n.trans += "B";
  return n;
}

Node C(Node n) {
  int temp = n.sq[1];
  n.sq[1] = n.sq[6];
  n.sq[6] = n.sq[5];
  n.sq[5] = n.sq[2];
  n.sq[2] = temp;

  assert(n.state != C3);
  if(n.state == C1)
    n.state = C2;
  else if(n.state == C2)
    n.state = C3;
  else
    n.state = C1;

  n.trans += "C";
  return n;
}

bool cmp(const Node& n1, const Node& n2) {
  for(int i=0; i<8; i++)
    if(n1.sq[i] != n2.sq[i])
      return false;

  return true;
}

int test() {
  Node init;
  for(int i=0; i<8; i++) init.sq.push_back(i+1);
  init.state = ZERO;
  init.trans = "";

  //print(B(C(C(B(C(C(C(B(A(init))))))))));
  
  print(A(B(B(init))));
  print(B(A(B(init))));
  print(B(B(A(init))));
}

int main() {
  Node expect;
  for(int i=0; i<8; i++) {
    int c; cin>>c;
    expect.sq.push_back(c);
  }
  expect.state = ZERO;

  Node init;
  for(int i=0; i<8; i++) init.sq.push_back(i+1);
  init.state = ZERO;
  init.trans = "";

  queue<Node> q;
  q.push(init);

  while(!q.empty()) {    
    Node cur = q.front();
    q.pop();

    if(cmp(cur, expect)) {
      cout << cur.trans.size() << endl;
      cout << cur.trans << endl;
      return 0;
    }

    if(cur.state != A1) {
      q.push(A(cur));     
    }    
    if(cur.state != B3) {      
      q.push(B(cur));
    }
    if(cur.state != C3) {
      q.push(C(cur));
    }
  }
}
