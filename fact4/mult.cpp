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

void int_2_vect(int x, vector<int>& ans) {
  if(x == 0) {
    ans.push_back(0);
    return;
  }

  while(x) {
    int cur = x % 10;
    ans.insert(ans.begin(), cur);
    x -= cur;
    x /= 10;
  }

  return;
}

void clean(vector<int>& a) {
  for(int i=a.size()-1; i>=0; i--) {    
    if(a[i] == 0)
      a.pop_back();
    else
      break;
  }
}

void print(const vector<int> & a) {
  for(int i=0; i<a.size(); i++) cout << a[i];
  cout << "\n";
}

void add(vector<vector<int> >& adds, vector<int>& ans) {
  int norm_size = adds.back().size();

  for(int i=0; i<adds.size(); i++) {
    if(adds[i].size() < norm_size) {
      int small_size = adds[i].size();
      for(int t=0; t<norm_size - small_size; t++)
	adds[i].insert(adds[i].begin(), 0);
    }
  }

  int carry = 0;
  for(int i=norm_size-1; i>=0; i--) {
    int cur = 0;
    for(int j=0; j<adds.size(); j++) cur += adds[j][i];
    cur += carry;

    int r = cur % 10;
    int l = cur / 10;

    ans.insert(ans.begin(), r);
    carry = l;
  }

  if(carry != 0)
    ans.insert(ans.begin(), carry);

  return;
}

void mult_helper(const vector<int>& a, int b, int zeros, vector<int>& cur_ans) {
  int carry = 0;
  for(int i=a.size()-1; i>=0; i--) {
    int ai = a[i];
    int cur = ai*b + carry;

    int r = cur % 10;
    int l = cur / 10;

    cur_ans.insert(cur_ans.begin(), r);
    carry = l;
  }
  if(carry != 0)
    cur_ans.insert(cur_ans.begin(), carry);

  assert(cur_ans.size() <= a.size() + 1);

  for(int i=0; i<zeros; i++) cur_ans.push_back(0);
}

void mult(const vector<int>& a, const vector<int>& b, vector<int>& ans) {
  assert(a.size() >= b.size());
  assert(b.size() > 0);
  assert(a.back() != 0);
  assert(b.back() != 0);

  vector<vector<int> > adds;
  for(int i=b.size()-1; i>=0; i--) { // use traditional order
    vector<int> cur_ans;
    
    int zeros = b.size() - 1 - i;
    mult_helper(a, b[i], zeros, cur_ans);

    adds.push_back(cur_ans);
  }

  add(adds, ans);
}

int main() {
  int s;
  fin>>s;
  
  vector<int> cur;
  
  vector<int> ans;
  int_2_vect(1, ans);
  vector<int> ans_dup;

  vector<int> *p1, *p2;
  p1 = &ans, p2 = &ans_dup;
  
  
  for(int i=1; i<=s; i++) {
    //print(*p1);
    //cout << i << endl;
    int_2_vect(i, cur);
    clean(cur);
    //print(cur);
    
    mult(*p1, cur, *p2);
    swap(p1, p2);
    p2->clear();
    clean(*p1);
    cur.clear();

    if(p1->size() >= 20) {
      p1->erase(p1->begin(), p1->begin() + p1->size() - 20);
    }
  }

  //print(*p1);
  fout << p1->back() << endl;
}
