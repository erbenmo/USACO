/*
PROB: camelot
LANG: C++
*/
#include <iostream>
#include <fstream>
#include <queue>
#include <assert.h>

using namespace std;

ifstream fin("camelot.in");
ofstream fout("camelot.out");
#define cin fin
#define cout fout

int R, C;
int dist[780][780];
int dir[8][2] = {{-2, -1}, {-1, -2}, {-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {1, -2}, {2, -1}};

int num_k = 0;
int knights[780][2];
int king[2];
int surround[25][2] = {{-2, -2}, {-2, -1}, {-2, 0}, {-2, 1}, {-2, 2},
		      {-1, -2}, {-1, -1}, {-1, 0}, {-1, 1}, {-1, 2},
		      {0, -2}, {0, -1}, {0, 0}, {0, 1}, {0, 2},
		      {1, -2}, {1, -1}, {1, 0}, {1, 1}, {1, 2},
		      {2, -2}, {2, -1}, {2, 0}, {2, 1}, {2, 2}};
int surround_dist[25] = {2, 2, 2, 2, 2,
			2, 1, 1, 1, 2,
			2, 1, 0, 1, 2,
			2, 1, 1, 1, 2,
			2, 2, 2, 2, 2};
			

int encode(int r, int c) {
  assert(r>=0 && r<=R-1);
  assert(c>=0 && c<=C-1);
  return r*C+c;
}

struct node {
  node(int _r, int _c, int _count) {r=_r, c=_c, count=_count;}
  int r, c, count;
};

void bfs(int r, int c) {
  int from_id = encode(r, c);
  bool visited[30][26];
  for(int i=0; i<30; i++)
    for(int j=0; j<26; j++)
      visited[i][j] = false;
  
  queue<node> q;
  q.push(node(r, c, 0));
  visited[r][c] = true;
  dist[from_id][from_id] = 0;

  while(!q.empty()) {
    node cur = q.front();
    q.pop();

    for(int i=0; i<8; i++) {
      int dr=dir[i][0], dc=dir[i][1];

      if(visited[cur.r+dr][cur.c+dc]) continue;
      if(cur.r + dr < 0 || cur.r + dr > R-1 || cur.c + dc < 0 || cur.c + dc > C-1)
	continue;
      
      node next(cur.r+dr, cur.c+dc, cur.count+1);
      q.push(next);
      visited[next.r][next.c] = true;
      int to_id = encode(next.r, next.c);
      dist[from_id][to_id] = next.count;
    }
  }
}

int main() {
  for(int i=0; i<780; i++)
    for(int j=0; j<780; j++)
      dist[i][j] = 700000;
  
  cin>>R>>C;
  char cchar;
  int rint;
  
  cin>>cchar>>rint;
  king[0] = --rint, king[1] = cchar - 'A';

  while(cin>>cchar>>rint) {
    knights[num_k][0] = --rint;
    knights[num_k][1] = cchar-'A';
    num_k++;
  }

  for(int r=0; r<R; r++)
    for(int c=0; c<C; c++)
      bfs(r, c);

  /*
  int source = encode(0, 0);
  for(int r=0; r<R; r++) {
    for(int c=0; c<C; c++) {
      cout << dist[source][encode(r, c)] << " ";
    }
    cout << endl;
    }*/

  
  if(num_k == 0) {
      cout << 0 << endl;
    return 0;
  }

  int rst = 700000;
  for(int dr=0; dr<R; dr++) {
    for(int dc=0; dc<C; dc++) {  // for all destination
      int final = encode(dr, dc);
      int cur_dist[780];
      int knight_dists = 0;

      for(int i=0; i<num_k; i++) {
	int from = encode(knights[i][0], knights[i][1]);
	cur_dist[i] = dist[from][final];
	knight_dists += cur_dist[i];
      }
      
      // no picker
      int king_origin = encode(king[0], king[1]);
      rst = min(rst, knight_dists + max(abs(king[0]-dr), abs(king[1]-dc)));

      // with picker
      for(int i=0; i<num_k; i++) {  // for all knight-candidate
	for(int j=0; j<25; j++) {  // for all king surrounding  
	  int cand_origin = encode(knights[i][0], knights[i][1]);
	  int king_r = king[0]+surround[j][0];
	  int king_c = king[1]+surround[j][1];
	  if(king_r < 0 || king_r > R-1 || king_c < 0 || king_c > C-1)
	    continue;
	  int king_id = encode(king_r, king_c);

	  int king_dist = surround_dist[j];
	  int cand_dist = dist[cand_origin][king_id] + dist[king_id][final];
	  int cur_rst = knight_dists - dist[cand_origin][final] + king_dist + cand_dist;


	  //if(cur_rst <= rst)
	  //cout << "Destination: " << (char)('A'+dc) << dr+1 << "  with Knight " << i+1 << "  save king @ " << (char)('A'+king_c) << king_r+1 << "--- Total Dist: " << cur_rst << endl;
	  
	  rst = min(rst, cur_rst);
	}
      }
    }
  }

  cout << rst << endl;
}
