#include <iostream>
#include <queue>

using namespace std;

struct node {
  node(int _x, int _y, int _count, int _dx, int _dy) {
    x=_x, y=_y, count=_count, dx=_dx, dy=_dy;
  }

  node();
  
  int x, y;
  int dx, dy;
  int count;
};

node board[15][15];
int dir[4] = { -2, -1, 1, 2 };

int to(int in) { return in+7; }
bool inRange(int in) { return in>=0 && in<15;}

int main() {
  for(int i=0; i<15; i++)
    for(int j=0; j<15; j++)
      board[i][j].count = -1;
  
  queue<node> q;
  q.push(node(0, 0, 0, 0, 0));

  while(!q.empty()) {
    node cur = q.front();
    q.pop();

    for(int i=0; i<4; i++) {
      for(int j=0; j<4; j++) {
	int dx = dir[i], dy = dir[j];

	node next(cur.x+dx, cur.y+dy, cur.count+1, dx, dy);

	if(!inRange[next.x] || !inRange[next.y]) continue;
	if(board[to(next.x)][to(next.y)].count != -1) continue;
	q.push(next);
	board[to(next.x)][to(next.y)] = next;
      }
    }
  }
}
