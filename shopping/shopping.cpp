#include <iostream>
#include <vector>
#include <map>
#include <assert.h>

using namespace std;

struct ele{
  ele(int _id, int _num) {id=_id, num=_num;}
  int id, num;
};

int costs[7776];
vector<vector<ele> >ofs;
vector<int> ofs_price;

int products = 0;
map<int, int> c2index;

int num_products;
int need[5];
int id_price[5];

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
  for(int i=0; i<ofs.size(); i++) {
    for(int j=0; j<ofs[i].size(); j++) {
      cout << ofs[i][j].id << " * " << ofs[i][j].num << " ";
    }
    cout << " with price: " << ofs_price[i] << endl;
  }

  cout << "# products: " << num_products << endl;
  for(int i=0; i<num_products; i++)
    cout << "for " << i << " needs " << need[i] << " price: " << id_price[i] << endl;
}

int main() {
  int num_offer;

  cin>>num_offer;
  for(int i=0; i<num_offer; i++) {
    vector<ele> of;
    int of_size, price;
    
    cin>>of_size;
    for(int j=0; j<of_size; j++) {
      int c, k, index;
      cin>>c>>k;

      if(c2index.find(c) == c2index.end())
	c2index[c] = products++;

      index = c2index[c];
      of.push_back(ele(index, k));      
    }

    ofs.push_back(of);
    
    cin>>price;
    ofs_price.push_back(price); 
  }

  
  cin>>num_products;  
  for(int i=0; i<num_products; i++) {
    int c, num, price, index;
    cin>>c>>num>>price;
    index = c2index[c];

    assert(c2index.find(c) != c2index.end());
    assert(index <= 4 && index >= 0);
    assert(id_price[index] == 0);

    need[index] = num;
    id_price[index] = price;
  }

  
}
