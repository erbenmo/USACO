/*
PROB: spin
LANG: C++
*/

#include <iostream>
#include <fstream>
#include <vector>
#include <assert.h>

using namespace std;
ifstream fin("spin.in");
ofstream fout("spin.out");

#define cin fin
#define cout fout

int count_print = 0;

struct wedge {
  wedge(int _s, int _e) {s = _s, e = _e;}
  int s, e;
};

int global[360][5];
int speed[5];
vector<vector<wedge> > wheels;

void print() {
  cout << count_print++ << endl;
  for(int i=0; i<360; i++) {
    cout << i << ": ";
    for(int j=0; j<5; j++) {
      cout << global[i][j] << " ";
    }
    cout << endl;
  }

  cout << endl << endl;
}

void rot(int &s, int dx) {
  assert(s<360);
  assert(s>=0);
  s = (s+dx) % 360;
}

int main() {
  int t;
  
  for(int i=0; i<5; i++) {
    vector<wedge> wheel;
    wheels.push_back(wheel);
  }


  for(int i=0; i<5; i++) {
    cin>>speed[i];
    int wedge_num;
    cin>>wedge_num;

    for(int j=0; j<wedge_num; j++) {
      int s, l;
      cin>>s>>l;
      int e = s;
      rot(e, l);
      wheels[i].push_back(wedge(s,e));

      int k = s;
      while(true) {
	global[k][i]++;
	if(k == e) break;
	rot(k, 1);
      }
    }
  }

  for(t=0; t<360; t++) {
    // rotate
    if(t==0)
      goto check;    
    for(int i=0; i<5; i++) {
      int dfi = speed[i]*1;
      for(int j=0; j<wheels[i].size(); j++) {
	int& s = wheels[i][j].s;
	int& e = wheels[i][j].e;
	// remove old mark
	int k=s;
	while(true) {
	  global[k][i]--;
	  if(k == e) break;
	  rot(k, 1);
	}

	rot(s, dfi);
	rot(e, dfi);

	// add new mark
	k = s;
	while(true) {
	  global[k][i]++;
	  if(k == e) break;
	  rot(k, 1);
	}
      }
    }

  check:
    for(int i=0; i<360; i++) {
      bool ok = true;
      for(int j=0; j<5; j++) {
	if(global[i][j] <= 0) {
	  ok = false;
	  break;
	}
      }

      if(ok) {
	cout << t << endl;
	return 1;
      }
    }
  }

  cout << "none\n";
  return 1;
}
