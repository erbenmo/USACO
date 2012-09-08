#include <iostream>
#include <queue>

using namespace std;

struct node {
  node(int _x, int _y, int _count, int _dx, int _dy) {
    x=_x, y=_y, count=_count, dx=_dx, dy=_dy;
  }  
  node() { }
  int x, y, count, dx, dy;
};

node board[51][59];
bool visited[51][59];
int dir[8][2] = {{-2, -1}, {-1, -2}, {-2, 1}, {-1, 2}, {1, 2}, {2, 1}, {1, -2}, {2, -1}};

int getBoardInfo() {
  queue<node> q;
  visited[25][29] = true;
  board[25][29] = node(25,29,0,0,0);
  q.push(board[25][29]);

  while(!q.empty()) {
    node cur = q.front();
    q.pop();

    for(int i=0; i<8; i++) {
      int dx=dir[i][0], dy=dir[i][1];

      if((cur.x+dx)>50 || (cur.x+dx)<0) continue;
      if((cur.y+dy)>59 || (cur.y+dy)<0) continue;
      if(visited[cur.x+dx][cur.y+dy]) continue;

      node next(cur.x+dx, cur.y+dy, cur.count+1, dx, dy);
      visited[cur.x+dx][cur.y+dy] = true;
      board[cur.x+dx][cur.y+dy] = next;
      q.push(next);
    }
  }
}
