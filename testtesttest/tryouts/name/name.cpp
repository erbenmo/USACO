#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

int main() {
	int N;
	while(cin>>N && N != 0) {
		vector<string> count2Name(N+1, "");
		map<string, int> curRecord;	

		for(int i=0; i<N; i++) {

			string cur;
			cin>>cur;
			if(curRecord.find(cur) == curRecord.end()) {
				curRecord[cur] = 1;
				count2Name[1] = cur;
			} else {
				int curCount = curRecord[cur];
				curCount++;
				curRecord[cur] = curCount;
				count2Name[curCount] = cur;  
			}
		}

		for(int i=N; i>=0; i--) {
			if(count2Name[i] != "") {
				cout << count2Name[i] << " " << i << endl;
				break;
			}
		}
	}
return 0;
}
