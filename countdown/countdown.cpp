#include <iostream>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

int N;

map<string, vector<string> > tree;
vector<vector<string> > score;

int calc(string name, int d) {
	int len = tree[name].size();
	vector<string> vcopy = tree[name];

	if(d==1)	return len;

	int sum=0;
	for(int i=0; i<len; i++)
		sum+=calc(vcopy[i], d+1);
	return sum;
}

void calcMax(int d) {
	for(map<string, vector<string> >::iterator i = tree.begin(); i != tree.end(); i++) {
		int cur = calc((*i).first, d);	
		score[cur].push_back((*i).first);
	}
}

void print(int curcase) {
	cout << "Tree " << curcase << ":\n";
	int num = 0;
	for(int i=1000; i>=0; i--) {
		if(num<3 && score[i].size() > 0) {
			sort(score[i].begin(), score[i].end());
			for(int j=0; j<score[i].size(); j++)
				cout << score[i][j] << " " << j << endl; 
			num--;
		}
	}
}

void clean() {
	tree.clear();
	score.clear();
	for(int i=0; i<1001; i++)	{
		vector<string> temp;
		score.push_back(temp);
	}
}

int main() {
	cin>>N;

	int NN = N;
	cout << N << endl;
	while(N--) {
		cout << "a!\n";
		clean();
		int s, d; cin>>s>>d;
		for(int i=0; i<s; i++) {
			string parent, child;
			int numOfChild;
			cin>>parent>>numOfChild;

			vector<string> children;
			for(int j=0; j<numOfChild; j++) {
				cin>>child; children.push_back(child);
			}
			tree[parent] = children;

			calcMax(d);
			print(NN-N);
		}
		exit(1);
	}
}
