#include <iostream>
#include <string>
#include <vector>
#include <stack>

using namespace std;

int towers;
int caseNum = 0;
int main() {
	cin>>towers;
	while(towers--) {
		caseNum++;
		int N;
		int K;
		vector<vector<string> > tower;
		cin>>N>>K;

		for(int i=0; i<N; i++) {
			vector<string>temp;
			for(int j=0; j<N; j++) {
				temp.push_back(".");
			}
			tower.push_back(temp);
		}
		
		stack<string> bricks;
		for(int i=0; i<N; i++) {
			string row;
			cin>>row;
			for(int j=0; j<row.length(); j++) {
				if(row.at(j) != '.') {
					bricks.push(row.substr(j, 1));	
				}
			}


			// set k fixed; filling tower[l][k]
			int k = N-i-1, l = N-1;
			while(!bricks.empty()) {	
				string cur = bricks.top();
				bricks.pop();
				tower[l][k] = cur;
				l--;
			}
		}
		
		
	/*	
		cout << "tower is .. \n";	
		for(int i=0; i<N; i++) {
			for(int j=0; j<N; j++) {
				cout << tower[i][j];
			}
			cout << endl;
		}
		cout << "end\n";
*/
		// check!
		bool rgood = false, bgood = false;

		for(int i=0; i<N; i++) {
			for(int j=0; j<N; j++) {
				string cur = tower[i][j];
				if(cur == ".")	continue;
				else if(cur == "R" && rgood)	continue;
				else if(cur == "B" && bgood)	continue;

				string right = "", down="", ld="", rd="";
				// right K
				if(j+K-1 <= N-1) {
					for(int l=j; l<=j+K-1; l++)
						right+=tower[i][l];
				}
				// down K
				if(i+K-1 <= N-1) {
					for(int l=i; l<=i+K-1; l++) {
						down+=tower[l][j];
					}
				}
				// left down K
				if(i+K-1 <=N-1 && j-K+1 >= 0) {
					int x = i, y = j;
					for(int ct=0; ct<K; ct++) {
						ld += tower[x][y];
						x++;
						y--;
					}
				}

				// right down K
				if(i+K-1 <= N-1 && j+K-1 <= N-1) {
					int x = i, y = j;
					for(int ct=0; ct<K; ct++) {
						rd += tower[x][y];
						x++;
						y++;
					}
				}

				string perfect = "";
				for(int ct=0; ct<K; ct++)	perfect+=cur;
				if(perfect == right || perfect == down || perfect == ld || perfect == rd) {
					if(cur == "R")	rgood = true;
					else	bgood = true;
				}
			}
		}
		cout << "Case #" << caseNum << ": ";
		if(rgood && !bgood)	cout << "Red\n";
		else if(rgood && bgood)	cout << "Both\n";
		else if(!rgood && bgood)	cout << "Blue\n";
		else cout << "Neither\n";
	}

}
