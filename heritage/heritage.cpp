/*
  PROB: heritage
  LANG: C++
 */
#include <iostream>
#include <fstream>
#include <string>
#include <assert.h>

using namespace std;
ifstream fin("heritage.in");
ofstream fout("heritage.out");
#define cin fin
#define cout fout

struct node {
  node(char _v) {l=r=0, v=_v;}
  node* l;
  node* r;
  char v;
};

int N = 0;
int rank[26];
char src[26];

void post_order(node* cur) {
  if(cur->l)
    post_order(cur->l);

  if(cur->r)
    post_order(cur->r);

  cout << cur->v;
}

node* process(int start, int end) {
  assert(start <= end);

  node* root = new node(src[start]);
  int root_rank = rank[src[start]-'A'];

  int left, right;
  left = right = -1;

  // find left child start-point
  for(int i=start+1; i<=end; i++) {
    if(rank[src[i]-'A'] < root_rank) {
      left = i;
      break;
    }    
  }

  // find right child start-point
  for(int i=start+1; i<=end; i++) {
    if(rank[src[i]-'A'] > root_rank) {
      right = i;
      break;
    }      
  }
  
  if(left != -1) {
    int left_end = (right == -1)? end : right-1;
    root->l = process(left, left_end);
  }
  if(right != -1) {
    root->r = process(right, end);
  }

  return root;
}

int main() {
  string in;
  cin>>in;
  N = in.length();
  
  for(int i=0; i<N; i++) {
    char c = in[i];
    rank[c-'A'] = i+1;
  }

  for(int i=0; i<N; i++) {
    cin>>src[i];
  }


  /*
  for(int i=0; i<26; i++)
    cout << (char)('A'+i) << " : " << rank[i] << endl;

  for(int i=0; i<N; i++)
    cout << src[i];

  cout << endl;
  */
  
  node* root = process(0, N-1);
  post_order(root);
  cout << endl;
}
