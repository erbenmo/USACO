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

//const int max_price = 25000;


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

  cout << "need: ";
  for(int i=0; i<num_products; i++)
    cout << need[i] << " ";
  cout << endl << endl;
}

// true ~ >=
bool cmp_bag(int a[5], int b[5]) {
  for(int i=0; i<5; i++) {    
    if(a[i] < b[i])
      return false;
  }

  return true;
}

bool too_big(int a[5]) {
  for(int i=0; i<5; i++) {
    if(a[i] > need[i])
      return true;
  }

  return false;
}

void subtract(int source[5], int d[5], int remain[5]) {
  for(int i=0; i<5; i++) {
    int rem = source[i] - d[i];
    //cout << rem << endl;
    assert(rem >= 0);
    remain[i] = rem;
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

    if(c2index.find(c) == c2index.end())
      c2index[c] = products++;

    index = c2index[c];

    cout << "c: " << c << ", index: " << index << endl;

    assert(index <= 4 && index >= 0);
    assert(ofs_price[num_offer + index] == 0);

    need[index] = k;
    
    ofs_num[num_offer + index][index] = 1;
    ofs_price[num_offer + index] = price;
  }

  print();
  
  // finally start DP
  int hash[7776];
  for(int i=1; i<7776; i++) hash[i] = -1;
  int final_id = encode(need);
  
  for(int i=0; i<num_offer + num_products; i++) {
    for(int bag_id=0; bag_id<7776; bag_id++) {
      int bag[5];
      decode(bag_id, bag);
      if(too_big(bag))
	continue;

      cout << "bag: ";
      for(int i=0; i<num_products; i++) cout << bag[i] << " ";
      cout << " with value: " << hash[bag_id] << endl;
    }
    cout << endl << endl << endl << endl;
    
    for(int bag_id=0; bag_id<7776; bag_id++) {
      int bag[5];
      decode(bag_id, bag);

      if(too_big(bag))
	continue;

      if(cmp_bag(bag, ofs_num[i])) {
	int remain[5];
	int remain_id;

	/*
	for(int x=0; x<5; x++) cout << bag[x] << " ";
	cout << " -  ";
	for(int x=0; x<5; x++) cout << ofs_num[i][x] << " ";
	cout << endl;
	*/
	
	subtract(bag, ofs_num[i], remain);
	remain_id = encode(remain);

	if(hash[remain_id] == -1)
	  continue;
	if(hash[bag_id] == -1)
	  hash[bag_id] = hash[remain_id] + ofs_price[i];
	else
	  hash[bag_id] = min(hash[bag_id],
			   hash[remain_id] + ofs_price[i]);
      }
    }
  }

  cout << hash[final_id] << endl;
}
