#include <iostream>
#include <cmath>
using namespace std;

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

const double eps = 0.000001;

int N;
double points[200][2];
double person[2];
bool SEE[200];

void ray(double dir_x, double dir_y) {
  //cout << person[0] << "," << person[1] << " - " << dir_x << "," << dir_y << "  ->  " << endl;
  double Ax, Ay, Bx, By, Cx, Cy, Dx, Dy;
  Ax = person[0], Ay = person[1];
  Bx = dir_x, By = dir_y;

  int min_idx = -1;
  double min_dist = 14000000;
  for(int i=0; i<N; i++) {
    int j = (i+1)%N;

    Cx = points[i][0], Cy = points[i][1];
    Dx = points[j][0], Dy = points[j][1];

    // parallel
    v AB(Bx-Ax, By-Ay), CD(Dx-Cx, Dy-Cy);
    if(abs(cross(AB, CD)) < eps) {
      continue;
    }

    // find dist from A->B
    double dist_1, dist_2;
    if(abs(abs(Dx)-abs(Cx)) <= eps) { // Dx-Cx == 0, Dy-Cy != 0
      //cout << i << " a~ ";
      dist_1 = (Cx-Ax)/(Bx-Ax);
      dist_2 = (Ay-Cy+(By-Ay)*dist_1)/(Dy-Cy);
    }
    else if(abs(abs(Dy)-abs(Cy)) <= eps) { // Dy-Cy == 0, Dx-Cx != 0
      //cout << i << "b~ ";
      dist_1 = (Cy-Ay)/(By-Ay);
      dist_2 = (Ax-Cx+(Bx-Ax)*dist_1)/(Dx-Cx);
    } else {
      //cout << i << "c~ ";
      dist_1 = ((Ay-Cy)*(Dx-Cx)-(Ax-Cx)*(Dy-Cy))/((Dy-Cy)*(Bx-Ax)-(Dx-Cx)*(By-Ay));
      dist_2 = (Ax + (Bx-Ax) * dist_1 - Cx) / (Dx-Cx);
    }

    //printf(" %.10f %.10f\n", dist_1, dist_2);
    if(dist_1 < 0) continue;
    if(dist_2 <= 0 || dist_2 >= 1) continue;
    
    
    if(dist_1 < min_dist) {
      min_dist = dist_1;
      min_idx = i;
    }
  }

  if(min_idx == -1) return;

  //cout << "final: " << min_idx << endl << endl;
  SEE[min_idx] = true;
}

int main() {
  cin>>N;
  cin>>person[0]>>person[1];
  for(int i=0; i<N; i++) cin>>points[i][0]>>points[i][1];

  // check is valid fence
  for(int i=0; i<N; i++) {
    int j = (i+1)%N;

    for(int k=0; k<N; k++) {
      int l = (k+1)%N;

      if(i==k || i==l || j==k)
	continue;

      v I(points[i][0], points[i][1]);
      v J(points[j][0], points[j][1]);
      v K(points[k][0], points[k][1]);
      v L(points[l][0], points[l][1]);

      if(intersect(I, J, K, L)) {
	//cout << i << j << k << l << endl;
	//cout << "collide, " << I.x << I.y << J.x << J.y << K.x << K.y << L.x << L.y << endl;
	cout << "NOFENCE\n";
	return 0;
      }
    }
  }
  
  //cout << "fence valid!\n";

  for(int i=0; i<N; i++) {
    ray(points[i][0], points[i][1]+eps);
    ray(points[i][0], points[i][1]-eps);
  }

  int result_num = 0;
  int results[200][2];
  
  for(int i=0; i<N; i++) {
    if(SEE[i]) {
      int j = (i+1) % N;
      results[result_num][0] = min(i, j);
      results[result_num][1] = max(i, j);
      result_num++;
    }
  }
  
  if(result_num >1) {
    if(results[result_num-1][0] < results[result_num-2][1]) {
      swap(results[result_num-1][0], results[result_num-2][0]);
      swap(results[result_num-1][1], results[result_num-2][1]);
    }
  }

  for(int i=0; i<result_num; i++) {
    int a = results[i][0], b = results[i][1];
    cout << points[a][0] << " " << points[a][1] << " " << points[b][0] << " " << points[b][1] << endl;
  }
  
}
