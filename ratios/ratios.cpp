#include <iostream>

using namespace std;

int det(int _a, int _b, int _c, int _d, int _e, int _f, int _g, int _h, int _i) {
  return _a*_e*_i+_b*_f*_g+_c*_d*_h-_c*_e*_g-_b*_d*_i-_a*_f*_h;
}

bool divide(int up, int down) {
  int ratio = up/down;
  return ratio * down == up;
}

int test() {
  int a,b,c,d,e,f,g,h,i, j, k, l;

  a=1, b=3, c=2;
  d=2, e=7, f=1;
  g=3, h=1, i=2;

  j = 21, k=28, l=35;
  int base = det(a,b,c,d,e,f,g,h,i);
  int up1 = det(j,b,c,k,e,f,l,h,i);
  int up2 = det(a,j,c,d,k,f,g,l,i);
  int up3 = det(a,b,j,d,e,k,g,h,l);

  cout << base << endl;
  cout << up1 << " " << up2 << " " << up3 << endl;
  cout << up1/base << " " << up2/base << " " << up3/base << endl;
}

//  x*(a,b,c) + y*(d,e,f) + z*(g,h,i) = (j,k,l) = t*(m,n,o)
int main() {
  int a,b,c,d,e,f,g,h,i,j,k,l,m,n,o;
  int x,y,z,t;
  int up1, up2, up3;
  
  cin>>m>>n>>o>>a>>d>>g>>b>>e>>h>>c>>f>>i;

  int base = det(a,b,c,d,e,f,g,h,i);

  for(t=1; t<1000; t++) {
    j=t*m, k=t*n, l=t*o;

    up1 = det(j,b,c,k,e,f,l,h,i);
    if(!divide(up1, base))
      continue;

    up2 = det(a,j,c,d,k,f,g,l,i);
    if(!divide(up2, base))
      continue;

    up3 = det(a,b,j,d,e,k,g,h,l);
    if(!divide(up3, base))
      continue;

    break;
  }

  x = up1/base, y=up2/base, z=up3/base;
  cout << x << " " << y << " "<< z << " "<< t << endl;
}
