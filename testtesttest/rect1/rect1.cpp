/*
LANG: C++
PROB: rect1
*/
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <assert.h>

using namespace std;
ifstream fin("rect1.in");
ofstream fout("rect1.out");
struct rect {
	rect() {}
	rect(int _x1, int _x2, int _y1, int _y2, int _color = -1) 
		{x1=_x1, y1=_y1, x2=_x2, y2=_y2, color = _color;}
	int x1, y1, x2, y2;
	int color;
};

int A, B, N;
rect rects[2500];		// Colors = 2500
int colors[2500];
int results[2500] = {0};

void pt(rect cur) {
	printf("%d %d %d %d\n", cur.x1, cur.y1, cur.x2, cur.y2);
}

int calc(int id) {
	vector<rect> curRects;	
	curRects.push_back(rects[id]);
	int curColor = curRects[id].color;

	for(int i=id+1; i<=N; i++) {				// invaders
		int invaderId = colors[i];
		int x1, x2, x3, x4, y1, y2, y3, y4;

		vector<rect> tempRects;
		for(int j=curRects.size()-1; j>=0; j--) {
			x2 = rects[invaderId].x1, y2 = rects[invaderId].y1, x3 = rects[invaderId].x2, y3 = rects[invaderId].y2;
			x1 = curRects[j].x1, y1 = curRects[j].y1, x4 = curRects[j].x2, y4 = curRects[j].y2;

			if(x3 <= x1 || x2 >= x4 || y3 <= y1 || y2 >= y4)	continue;

		//printf("-- %d %d %d %d %d %d %d %d\n", x1, y1, x4, y4, x2, y2, x3, y3);
			x2 = max(x1, x2), x3 = min(x3, x4), y2 = max(y1, y2), y3 = min(y3, y4);	
		//printf("---- %d %d %d %d\n", x2, y2, x3, y3);
			assert(x1<=x2 && x2<=x3 && x3<=x4 && y1<=y2 && y2<=y3 && y3<=y4);

			curRects.erase(curRects.begin() + j);

			if(x1<x2) {
				if(y1<y2)	tempRects.push_back(rect(x1, x2, y1, y2));
				if(y2<y3)	tempRects.push_back(rect(x1, x2, y2, y3));
				if(y3<y4)	tempRects.push_back(rect(x1, x2, y3, y4));
			}
			if(x2<x3) {	
				if(y1<y2)	tempRects.push_back(rect(x2, x3, y1, y2));	
				if(y3<y4)	tempRects.push_back(rect(x2, x3, y3, y4));
			}
			if(x3<x4) {
				if(y1<y2)	tempRects.push_back(rect(x3, x4, y1, y2));
				if(y2<y3)	tempRects.push_back(rect(x3, x4, y2, y3));
				if(y3<y4)	tempRects.push_back(rect(x3, x4, y3, y4));
			}
		}

		for(int j=0; j<tempRects.size(); j++)
			curRects.push_back(tempRects[j]);
	}

	int area = 0;
	for(int i=0; i<curRects.size(); i++) {
		area += abs(curRects[i].x1 - curRects[i].x2) * abs(curRects[i].y1 - curRects[i].y2);
	}

	return area;
}

int main() {
	cin>>A>>B>>N;

	rects[0].x1 = rects[0].y1 = 0;
	rects[0].x2 = A, rects[0].y2 = B;
	rects[0].color = 1;
	colors[0] = 1;

	for(int i=1; i<=N; i++) {
		int x1, y1, x2, y2, color;
		cin>>x1>>y1>>x2>>y2>>color;
		colors[i] = color;
		rects[color].x1=x1, rects[color].x2=x2, rects[color].y1=y1, rects[color].y2=y2, rects[color].color=color;
	}

	for(int i=0; i<=N; i++) {
		int area = calc(colors[i]);
		results[rects[colors[i]].color-1] += area;
	}

	for(int i=0; i<=N; i++) {
		if(results[colors[i]]!=0)
			cout << rects[colors[i]].color << " " << results[colors[i]] << endl;
	}
}




/*		cout << ":"; pt(rects[i]); 
		cout << "^\n";
		for(int j=0; j<curRects.size(); j++)
			pt(curRects[j]);
		cout << "^\n";*/
