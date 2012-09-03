#include <iostream>
#include <vector>
#include <assert.h>

using namespace std;

// base 6
int step[5] = {6*6*6*6, 6*6*6, 6*6, 6, 1};

int encode(int data[5]) {
  for(int i=0; i<5; i++)
    assert(data[i]<=5 && data[i]>=0);

  int res = 0;
  for(int i=0; i<5; i++)
    res += data[i] * step[i];
  
  return res;  
}

void decode(int res, int data[5]) {
  assert(res <= 7776 && res >= 0);
  for(int i=0; i<5; i++) {
    data[i] = res / step[i];
    res -= data[i]*step[i];
  }
}

int main() {
  /*
  for(int s1=0; s1<=5; s1++)
    for(int s2=0; s2<=5; s2++)
      for(int s3=0; s3<=5; s3++)
	for(int s4=0; s4<=5; s4++)
	  for(int s5=0; s5<=5; s5++) {
	    int data[5];
	    data[0] = s1;
	    data[1] = s2;
	    data[2] = s3;
	    data[3] = s4;
	    data[4] = s5;

	    for(int i=0; i<5; i++) cout << data[i];
	    cout << " : ";
	    cout << encode(data);
	    cout << endl;
	  }
  */

  /*
  for(int res=0; res<7776; res++) {
    int data[5];
    decode(res, data);
    int rev = encode(data);

    cout << res << " : " << rev << endl;
    }*/
}
