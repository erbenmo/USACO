#include <iostream>
#include <vector>
#include <stack>

using namespace std;

vector<vector<int> > links;
stack<int> answer;

void print() {
  for(int i=0; i<7; i++) {
    for(int j=0; j<links[i].size(); j++)
      cout << links[i][j]+1 << " ";
    cout << endl;
  }
}

void insert_link(int s, int e) {
  int idx = 0;
  for(int i=0; i<links[s].size(); i++) {
    if(links[s][i] < e)
      idx = i+1;
    else
      break;
  }

  links[s].insert(links[s].begin() + idx, e);    	
}

void delete_link(int s, int e) {
  for(int i=0; i<links[s].size(); i++) {
    if(links[s][i] == e) {
      links[s].erase(links[s].begin() + i);
    }
  }
}

int main() {
  int num_fence;
  cin>>num_fence;

  for(int i=0; i<500; i++) {
    vector<int> row;
    links.push_back(row);
  }

  for(int i=0; i<num_fence; i++) {
    int s, e;
    cin>>s>>e;
    s--, e--;

    insert_link(s,e);
    insert_link(e,s);
  }

  int cur;
  stack<int> s;
  for(cur=0; cur<links.size(); cur++)
    if(links[cur].size() != 0)
      break;
  s.push(cur);
  
  while(!s.empty()) {
    cur = s.top();
    s.pop();

  process_node:
    if(links[cur].size() == 0) {
      answer.push(cur);
      continue;
    }

    s.push(cur);
    int neighbor = links[cur][0];
    delete_link(cur, neighbor);
    delete_link(neighbor, cur);

    cur = neighbor;
    goto process_node;
  }

  while(!answer.empty()) {
    cout << answer.top() + 1<< " ";
    answer.pop();
  }

  cout << endl;

}
