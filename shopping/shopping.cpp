#include <iostream>
#include <vector>
#include <map>
#include <assert.h>

using namespace std;

int num_offer, num_products;
int need[5];

int ofs_num[99+5][5];
int ofs_price[99+5];

int products = 0;
map<int, int> c2index;


int step[5] = {6*6*6*6, 6*6*6, 6*6, 6, 1}; // base 6

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

void print() {
  for(int i=0; i<num_offer + num_products; i++) {
    for(int j=0; j<num_products; j++) {
      cout << ofs_num[i][j] << " ";
    }
    cout << " with price: " << ofs_price[i] << endl;
  }
}

int main() {
  cin>>num_offer;
  for(int i=0; i<num_offer; i++) {
    int of_size, price;
    
    cin>>of_size;
    for(int j=0; j<of_size; j++) {
      int c, k, index;
      cin>>c>>k;

      if(c2index.find(c) == c2index.end())
	c2index[c] = products++;

      index = c2index[c];
      assert(index < 5);
      ofs_num[i][index] = k;
    }

    cin>>price;
    ofs_price[i] = price; 
  }

  
  cin>>num_products;
  for(int i=0; i<num_products; i++) {
    int c, k, price, index;
    
    cin>>c>>k>>price;
    index = c2index[c];

    assert(c2index.find(c) != c2index.end());
    assert(index <= 4 && index >= 0);
    assert(ofs_price[num_offer + index] == 0);

    need[index] = k;
    
    ofs_num[num_offer + index][index] = 1;
    ofs_price[num_offer + index] = price;
  }

  print();
  
  /*
  // finally start DP
  int hash[7776];
  
  for(int i=0; i<ofs.size(); i++) {
    for(int s0=0; s0<=needs[0]; s0++)
      for(int s1=0; s1<=needs[1]; s1++)
	for(int s2=0; s2<=needs[2]; s2++)
	  for(int s3=0; s3<=needs[3]; s3++)
	    for(int s4=0; s4<=needs[4]; s4++) {
	      int bag[5];
	      bag[0]=s0, bag[1]=s1, bag[2]=s2, bag[3]=s3, bag[4]=s4;	      
	      int bag_id = encode(bag);

	      
	    }
  }

  int final_bag_id = encode(need);
  cout << hash[final_bag_id];*/
}
