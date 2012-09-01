/*
PROB: butter
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <assert.h>

using namespace std;
const int max_d = 200000;

ofstream fout("butter.out");
ifstream fin("butter.in");

#define in fin
#define out fout

// N: cow number, 500
// P: pasture number, 800
// C: path number, 1450
int N,P,C;

struct node {
  node(int id_, int len_) {id=id_, len=len_;}
  int id, len;
};

vector<vector<node> > dist;
int d[800];
int cow[500] = { 0 };

int print() {
  out << "\nprint --------------\n";
  for(int i=0; i<dist.size(); i++) {
    for(int j=0; j<dist[i].size(); j++)
      out << dist[i][j].id << " : " << dist[i][j].len << "    ";
    out << endl;
  }

  out << "--------------\n\n";
}

int init() {
  for(int i=0; i<800; i++) {
    vector<node> temp;
    dist.push_back(temp);
  }
    
  in>>N>>P>>C;

  for(int i=0; i<N; i++) {
    in>>cow[i];
    cow[i]--;
  }

  for(int i=0; i<C; i++) {
    int s, d, l;
    in >> s >> d >> l;
    s--, d--;
    dist[s].push_back(node(d, l));
    dist[d].push_back(node(s, l));
  }
}

int SPFA(int s) {
  for(int i=0; i<800; i++) d[i] = max_d;
  d[s] = 0;

  queue<int> q;
  bool in_q[800] = { false };
  q.push(s);
  in_q[s] = true;

  while(!q.empty()) {
    int cur = q.front();
    in_q[cur] = false;
    q.pop();

    for(int i=0; i<dist[cur].size(); i++) {
      // relax
      if(d[dist[cur][i].id] > d[cur] + dist[cur][i].len) {
	d[dist[cur][i].id] = d[cur] + dist[cur][i].len;

	if(!in_q[dist[cur][i].id]) {
	  in_q[dist[cur][i].id] = true;
	  q.push(dist[cur][i].id);
	}	
      }
    }
  }

  //  for(int i=0; i<P; i++) cout << d[i] << " ";
  //cout << endl;
  
  int ans = 0;
  for(int i=0; i<N; i++) {
    int cid = cow[i];
    ans += d[cid];
  }

  return ans;
}

int main() {
  init();
  
  int min_d = max_d;
  for(int i=0; i<P; i++) {
    int cur_d = SPFA(i);
    //    cout << i << " : " << cur_d << endl;
    min_d = min(cur_d, min_d);
  }

  out << min_d << endl;
}
