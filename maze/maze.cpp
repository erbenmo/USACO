/*
LANG: C++
PROB: maze1
*/
#include <iostream>
#include <fstream>
#include <queue>

using namespace std;
ifstream fin("maze1.in");
ofstream fout("maze1.out");

struct node {
	node(){}
	node(bool e, bool w, bool s, bool n) {east = e, west = w, south = s, north = n;}
	bool north;
	bool south;
	bool east;
	bool west;
};

struct nodeInfo {
	nodeInfo(int height, int width, int dist) {w=width, h=height, d=dist;}
	int w;
	int h;
	int d;
};

int W, H;
int SW1=-1, SH1=-1, SW2=-1, SH2=-1;
node maze[100][38];
int input[201][77];
int dist[100][38];

void set(int h, int w) {
	if(SH1==-1 && SW1==-1)		{SH1=h, SW1=w;}
	else if(h!=SH1 || w!=SW1)	{SH2=h, SW2=w;}
}

void findSource() {
	for(int j=0; j<W; j++)	if(maze[0][j].north)	set(0,j); 
	for(int j=0; j<W; j++)	if(maze[H-1][j].south)	set(H-1, j);
	for(int i=0; i<H; i++)	if(maze[i][0].west)		set(i, 0);
	for(int i=0; i<H; i++)	if(maze[i][W-1].east)	set(i, W-1);
}

void bfs(int h, int w) {
	bool visited[100][38] = {0};
	dist[h][w] = 1;
	queue<nodeInfo> wave;
	wave.push(nodeInfo(h, w, 1));

	while(!wave.empty()) {
		int curH = wave.front().h, curW = wave.front().w, curDist = wave.front().d;
		wave.pop();
		if(visited[curH][curW])	continue;

		visited[curH][curW] = true;
		dist[curH][curW] = min(dist[curH][curW], curDist);

		if(curW+1<=W-1 && maze[curH][curW].east)	wave.push(nodeInfo(curH, curW+1, curDist+1));
		if(curW-1>=0 && maze[curH][curW].west)		wave.push(nodeInfo(curH, curW-1, curDist+1));
		if(curH+1<=H-1 && maze[curH][curW].south)	wave.push(nodeInfo(curH+1, curW, curDist+1));
		if(curH-1>=0 && maze[curH][curW].north)		wave.push(nodeInfo(curH-1, curW, curDist+1));
	}
}


int main() {
	fin>>W>>H;
	string temp; getline(fin, temp);
	for(int i=0; i<2*H+1; i++) {
		string cur; getline(fin, cur);
		for(int j=0; j<2*W+1; j++) {
			input[i][j] = cur[j];
		}
	}

	for(int i=0; i<H; i++) {
		for(int j=0; j<W; j++) {
			int h=2*i+1, w=2*j+1;
			bool east = (input[h][w+1] == ' ');
			bool west = (input[h][w-1] == ' ');
			bool south = (input[h+1][w] == ' ');
			bool north = (input[h-1][w] == ' ');
			maze[i][j] = node(east, west, south, north);
		}
	}
	/*	
	for(int i=0; i<2*H+1; i++) {
		for(int j=0; j<2*W+1; j++)
			cout << (char)input[i][j];
		cout << endl;
	}

	cout << "#" << (char)input[0][1] << "#" << endl;
	cout << maze[0][0].north << endl;
	cout << maze[0][1].north << endl;
	*/
	findSource();

	for(int i=0; i<100; i++)	for(int j=0; j<38; j++)	dist[i][j] = 4000;
	//cout << SH1 << SW1 << "	" << SH2 << SW2 << endl;
	bfs(SH1, SW1);
	bfs(SH2, SW2); 

	int curMax = 0;
	for(int i=0; i<H; i++)
		for(int j=0; j<W; j++)
			curMax = max(curMax, dist[i][j]);
	
	fout << curMax << endl;
}
