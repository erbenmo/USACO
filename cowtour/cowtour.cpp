/*
LANG: C++
PROB: cowtour
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <cmath>
#include <assert.h>
#include <iomanip>

using namespace std;
#define LARGEDIST 1e20

ifstream fin("cowtour.in");
FILE* fout = fopen("cowtour.out", "w");

struct point {
	int x;
	int y;
};

int N;

point pos[150];
double dist[150][150];
bool islink[150][150];

bool visited[150] = {0};
vector<vector<int> > components;
double diameters[150];


void print() {
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++)
			(dist[i][j] >= LARGEDIST)? cout << -1 << "	" : cout << dist[i][j] << "	";
		cout << endl;
	}
}

double getDist(int i, int j) {
	int xdist = pos[i].x - pos[j].x, ydist = pos[i].y - pos[j].y;
	return sqrt(xdist*xdist + ydist*ydist); 
}

void fill(int cur, int id) {
	visited[cur] = true;
	components[id].push_back(cur);
	
	for(int j=0; j<N; j++) {
		if(islink[cur][j] && !visited[j])	
			fill(j, id);
	}
}

void find_component() {
	int componentId = 0;
	
	for(int i=0; i<N; i++) {
		if(visited[i])	continue;
		
		vector<int> temp; components.push_back(temp);
		fill(i, componentId);
		componentId++;
	}
}

void floyd(int id) {
	int size = components[id].size();
		
	for(int k=0; k<size; k++)
		for(int i=0; i<size; i++)
			for(int j=i+1; j<size; j++) {
				int ri=components[id][i], rj = components[id][j], rk = components[id][k];
				assert(dist[ri][rj] == dist[rj][ri]);
				dist[ri][rj] = dist[rj][ri] = min(dist[ri][rj], dist[ri][rk] + dist[rk][rj]);
			}
}

void calcDiameter(int id) {
	int size = components[id].size();
	double diameter = 0;
	for(int i=0; i<size; i++)
		for(int j=i+1; j<size; j++) {
			int ri = components[id][i], rj = components[id][j];
			diameter = max(diameter, dist[ri][rj]);
		}

	diameters[id] = diameter;
}

double maxDist(int id, int target) {
	int size = components[id].size();
	double curMax = 0;
	for(int i=0; i<size; i++) {
		int ri = components[id][i];
		if(ri == target)	continue;	
		assert(dist[ri][target] < LARGEDIST);
		curMax = max(curMax, dist[ri][target]);
	}
	
	return curMax;
}

int main() {
	fin>>N;
	for(int i=0; i<N; i++) {
		fin>>pos[i].x>>pos[i].y;
	}
	for(int i=0; i<N; i++) {
		string cur; fin>>cur;
		for(int j=0; j<N; j++)
			islink[i][j] = (cur[j] == '1');
	}

	find_component();	

	for(int i=0; i<N; i++)
		for(int j=0; j<N; j++) {
			dist[i][j] = (islink[i][j])?	getDist(i, j) : (LARGEDIST);
		}

	for(int i=0; i<components.size(); i++) {
		floyd(i);
		calcDiameter(i);
	}


	double curMin = LARGEDIST;
	for(int i=0; i<components.size(); i++)
		for(int j=i+1; j<components.size(); j++)
			for(int k=0; k<components[i].size(); k++)
				for(int l=0; l<components[j].size(); l++) {
					int rk = components[i][k], rl = components[j][l];
					double oldWinner = max(diameters[i], diameters[j]); 

					assert(dist[rk][rl] == LARGEDIST); // check floyd

					double iMax = maxDist(i, rk), jMax = maxDist(j, rl);
					double newWinner = iMax + jMax + getDist(rk, rl);
					
					curMin = min(curMin, max(oldWinner, newWinner));
				}
	fprintf(fout, "%.6lf\n", curMin);
	return 0;
}

