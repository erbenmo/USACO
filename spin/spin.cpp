#include <iostream>
#include <vector>

using namespace std;


struct wedge {
  wedge(int _s, int _e) {s = _s, e = _e;}
  int s, e;
};

int global[360][5];
int speed[5];
vector<vector<wedge> > wheels;

void print() {
  for(int i=0; i<360; i++) {
    cout << i << ": ";
    for(int j=0; j<5; j++) {
      cout << global[i][j] << " ";
    }
    cout << endl;
  }
}

void rot(int &s, int dx) {
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
      int s, e;
      cin>>s>>e;
      wheels[i].push_back(wedge(s,e));
      for(int k=s; k<=e; rot(k, 1)) {
	global[k][i]++;
      }
    }
  }

  print();

  for(t=0; t<360; t++) {
    // rotate
    if(t==0)
      goto check;    
    for(int i=0; i<5; i++) {
      int dfi = speed[i]*1;
      for(int j=0; j<wheels[i].size(); j++) {
	int s=wheels[i][j].s, e=wheels[i][j].e;
	// remove old mark
	for(int k=s; k<=e; rot(k, 1)) {
	  global[k][i]--;
	}

	rot(s, dfi);
	rot(e, dfi);

	// add new mark
	for(int k=s; k<=e; rot(k, 1)) {
	  global[k][i]++;
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
