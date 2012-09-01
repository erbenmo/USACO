/*
PROB: castle
LANG: C++
*/
#include <iostream>
#include <fstream>

using namespace std;

int N, M, total;
int curComp = 0;					// most recent assigned component number. starting from 1;
bool rooms[2500][2500] = {false};
int roomComp[50][50] = {0};
int compSize[2500] = {0};
/*
	  M 
   *******
N  ******* i
   *******
   *******
      j
*/

ifstream fin("castle.in");
ofstream fout("castle.out");

int id(int i, int j) {
	return j + i * M;
}

void conquer(int i, int j) {

	roomComp[i][j] = curComp;
	compSize[curComp]++;

	if(i>0) 	if(rooms[id(i, j)][id(i-1, j)]==true && roomComp[i-1][j]==0)	conquer(i-1, j);
	if(i<N-1) 	if(rooms[id(i, j)][id(i+1, j)]==true && roomComp[i+1][j]==0)	conquer(i+1, j);	
	if(j>0) 	if(rooms[id(i, j)][id(i, j-1)]==true && roomComp[i][j-1]==0)	conquer(i, j-1);	
	if(j<M-1) 	if(rooms[id(i, j)][id(i, j+1)]==true && roomComp[i][j+1]==0)	conquer(i, j+1);	
}

void find() {
	for(int i=0; i<N; i++) {
		for(int j=0; j<M; j++) {
			if(roomComp[i][j] == 0) {
				roomComp[i][j] = -1;
				curComp++;
				conquer(i, j);
			}
		}
	}
}

int getMax() {
	find();
	int max=-1, maxComp = -1;
	for(int i=1; i<=curComp; i++) {
		if(compSize[i] > max) {
			max = compSize[i], maxComp = i;
		} 
	}

	return max;
}

void clean() {
	for(int i=0; i<2500; i++)	compSize[i] = 0;
	for(int i=0; i<50; i++)	for(int j=0; j<50; j++)	roomComp[i][j] = 0;
	curComp = 0;
}

int main() {
	fin>>M>>N;
	total = M*N;

	for(int i=0; i<N; i++) {
		for(int j=0; j<M; j++) {
			int cur; fin>>cur;

			if(j>0 && (cur&1)==0)			rooms[id(i, j)][id(i, j-1)] = rooms[id(i, j-1)][id(i, j)] = true;
			if(i>0 && (cur>>1 & 1)==0)		rooms[id(i, j)][id(i-1, j)] = rooms[id(i-1, j)][id(i, j)] = true;
			if(j<M-1 && (cur>>2 & 1)==0)	rooms[id(i, j)][id(i, j+1)] = rooms[id(i, j+1)][id(i, j)] = true;
			if(i<N-1 && (cur>>3 & 1)==0)	rooms[id(i, j)][id(i+1, j)] = rooms[id(i+1, j)][id(i, j)] = true;
		}
	}

	int virginMax = getMax();
	int virginRooms = curComp;
	clean();

	int max = virginMax;
	int maxX, maxY;
	bool NorE;
	for(int j=0; j<M; j++) {
		for(int i=N-1; i>0; i--) {
			if(rooms[id(i, j)][id(i-1, j)]==true)	continue;
			rooms[id(i, j)][id(i-1, j)] = rooms[id(i-1, j)][id(i, j)] = true;
			int localmax = getMax();
			if(localmax > max) {
				max = localmax;
				maxX=j+1, maxY=i+1, NorE = true; 
			}
			rooms[id(i, j)][id(i-1, j)] = rooms[id(i-1, j)][id(i, j)] = false;
			clean();
		}

		for(int i=N-1; i>=0; i--) {
			if(j==M-1)	continue;
			if(rooms[id(i, j)][id(i, j+1)]==true)	continue;
			rooms[id(i, j)][id(i, j+1)] = rooms[id(i, j+1)][id(i, j)] = true;
			int localmax = getMax();
			if(localmax > max) {
				max = localmax;
				maxX=j+1, maxY=i+1, NorE = false;
			}
			rooms[id(i, j)][id(i, j+1)] = rooms[id(i, j+1)][id(i, j)] = false;
			clean();
		}
	}

	fout << virginRooms << endl;
	fout << virginMax << endl;
	fout << max << endl;
	fout << maxY << " " << maxX << " ";
	(NorE)? fout << "N": fout << "E";
	fout << endl;
}
