#include <iostream>
using namespace std;

const double very_small = 0.000001;
struct v {
  v(double _x, double _y) {x=_x, y=_y;}
  double x, y;
};

double cross(v A, v B) { return A.x*B.y - A.y*B.x; }
bool same_side(v from, v to, v c, v d) { // on-line -> not same side
  return cross(v(to.x-from.x, to.y-from.y), v(c.x-from.x, c.y-from.y))
    *cross(v(to.x-from.x, to.y-from.y), v(d.x-from.x, d.y-from.y)) > 0;
}
bool intersect(v A, v B, v C, v D) {
  return !same_side(C, D, A, B)  && !same_side(A, B, C, D);
}

int main() {
  v A(0, 0);
  v B(1, 0);
  v C(0, 1);
  v Cp(0, 1.0001);
  v Cpp(0, 0.9999);
  v D(1, 1);

  cout << same_side(A, D, C, B) << endl;
  cout << same_side(A, B, C, D) << endl;

  cout << intersect(A, C, B, D) << endl;
  cout << intersect(A, D, C, B) << endl;

  cout << same_side(A, C, C, D) << endl;
  cout << intersect(A, C, C, D) << endl;

  cout << intersect(A, C, Cp, D) << endl;

}
