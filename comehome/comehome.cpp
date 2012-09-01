/*
LANG: C++
PROB: comehome
*/
#include <iostream>
#include <fstream>
#include <cstdio>
#include <ctype.h>
#include <assert.h>
#include <queue>
#include <vector>
#define LARGEDIST 1<<18 

using namespace std;
ifstream fin("comehome.in");
ofstream fout("comehome.out");
struct node {
	node(int _id, int _dist) {id=_id, dist=_dist;}
	int id;
	int dist;
};
class CompareNode {
public:
	bool operator()(node& n1, node& n2)
	{
		return n1.dist > n2.dist;
	}
};

int dist[52][52];
int finalDist[52] = {0};
bool islink[52][52];
bool visited[52] = {false};
bool livesCow[52];

int c2i(int c) {
	if(islower(c))		return c-'a';
	else if(isupper(c))	return c-'A'+26;
}

void dijkstra(int s) {
	priority_queue<node, vector<node>, CompareNode> wave;
	wave.push(node(s, 0));
	
	while(!wave.empty()) {
		node cur = wave.top(); wave.pop();
		if(visited[cur.id])	continue;
		visited[cur.id] = true;
		finalDist[cur.id] = cur.dist;

		for(int i=0; i<51; i++) {
			if(visited[i])	continue;
			if(i==cur.id)	continue;
			if(islink[i][cur.id] == false)	continue;
			
			wave.push(node(i, dist[cur.id][i] + finalDist[cur.id]));
		}
	}
}

int main() {
	for(int i=0; i<52; i++)
		for(int j=0; j<52; j++)
			dist[i][j] = LARGEDIST;

	int N; fin>>N;
	for(int i=0; i<N; i++) {
		char s, t;
		int curDist;
		fin>>s>>t>>curDist;

		if(isupper(s))	livesCow[c2i(s)] = true;
		if(isupper(t))	livesCow[c2i(t)] = true;
		
		int is = c2i(s), it = c2i(t);
		islink[is][it] = islink[it][is] = true;
		if(curDist < dist[is][it])	dist[is][it] = dist[it][is] = curDist;
	}

	dijkstra(51);

	int curMin = LARGEDIST, idx = 0;
	for(int i=0; i<51; i++) {
		if(!livesCow[i])	continue;
		if(finalDist[i] < curMin) {
			curMin = finalDist[i];
			idx = i;
		}
	}

	char cur = (idx <= 25)? ('a'+idx) : ('A'+idx-26);
	fout << cur << " " << curMin << endl;
}
