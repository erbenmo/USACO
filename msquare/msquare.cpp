/*
PROB: msquare
LANG: C++
 */
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <string>
#include <assert.h>
#include <map>

using namespace std;

ifstream fin("msquare.in");
ofstream fout("msquare.out");

map<int, bool> hash;

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
  vector<short> sq;
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
  short temp = n.sq[0];
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
  short temp = n.sq[1];
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

int encode(const vector<short>& v) {
  int result = v[0];
  for(int i=1; i<8; i++) {
    result *= 10;
    result += v[i];
  }
    
  assert(result < 88888888);
  return result;
}


int test() {
  Node init;
  for(int i=0; i<8; i++) init.sq.push_back((short)i+1);
  init.state = ZERO;
  init.trans = "";

  cout << encode(init.sq) << endl;
  //print(B(C(C(B(C(C(C(B(A(init))))))))));

  
  //print(A(B(B(init))));
  //print(B(A(B(init))));
  //print(B(B(A(init))));
  

  //print(A(B(C(B(A(B(C(B(A(init))))))))));
}

int main() {
  Node expect;
  for(int i=0; i<8; i++) {
    short c; fin>>c;
    expect.sq.push_back(c);
  }
  expect.state = ZERO;

  Node init;
  for(int i=0; i<8; i++) init.sq.push_back((short)i+1);
  init.state = ZERO;
  init.trans = "";

  queue<Node> q;
  q.push(init);
  hash[encode(init.sq)] = true;

  while(!q.empty()) {
    Node cur = q.front();
    q.pop();

    if(cmp(cur, expect)) {
      fout << cur.trans.size() << endl;
      fout << cur.trans << endl;
      return 0;
    }

    if(cur.state == ZERO || cur.state >= C1) {
      Node a = A(cur);
      int key = encode(a.sq);
      if(hash[key] == false) {
	hash[key] = true;
	q.push(a);
      }
    }    
    if(cur.state != B3) {
      Node b = B(cur);
      int key = encode(b.sq);
      if(hash[key] == false) {
	hash[key] = true;
	q.push(b);
      }
    }
    if(cur.state != C3) {
      Node c = C(cur);
      int key = encode(c.sq);
      if(hash[key] == false) {
	hash[key] = true;
	q.push(c);
      }      
    }
  }

  return 0;
}


// 1. A,B are associative, if no c presents
