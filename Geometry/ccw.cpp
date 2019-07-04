#include<bits/stdc++.h>
using namespace std;
const double EPS = 1e-9;    // 許容誤差。問題によって変える
typedef complex<double> P;  // Point
#define X real()
#define Y imag()
namespace std{
    bool operator < (const P a, const P b){
        return a.X != b.X ? a.X <b.X : a.Y < b.Y;
    }
    P operator+(const P p1, const P p2) { return P(p1.X + p2.X, p1.Y + p2.Y); }
    P operator-(const P p1, const P p2) { return P(p1.X - p2.X, p1.Y - p2.Y); }
    P operator*(const P p, double k) { return P(p.X * k, p.Y * k); }
    P operator/(const P p, double k) { return P(p.X / k, p.Y / k); }
}
//外積cross(a,b) = |a||b|sinθ=a1b2+a2b1
double cross(const P& a, const P& b) {
  return (conj(a)*b).Y;
}
//内積dot(a,b) = |a||b|cosθ=a1b1+a2b2
double dot(const P& a, const P& b) {
  return (conj(a)*b).X;
}

//位置関係判定(線分abを軸にcがどちら側にあるか)
int ccw(P a, P b, P c){
    b -= a;
    c -= a; //aからの向きを考える
    if (cross(b, c) > EPS)
        return +1; //clockwise
    else if (cross(b, c) < -EPS)
        return -1; //counter clockwise
    else if (dot(b, c) < -EPS)
        return +2; //c-a-b
    else if (norm(b) < norm(c))
        return -2; //a-b-c
    else return 0;    //他
}

//Verify
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_C&lang=jp#
int main(){
    double x0,y0,x1,y1;
    cin>>x0>>y0>>x1>>y1;
    P p0 = P(x0, y0), p1 = P(x1, y1);
    int q;
    cin >> q;
    for (int i = 0; i < q;i++){
        double x2,y2;
        cin>>x2>>y2;
        int pos=ccw(p0,p1,P(x2,y2));
        if(pos==-1) cout << "CLOCKWISE" << endl;
        else if(pos==1) cout << "COUNTER_CLOCKWISE" << endl;
        else if(pos==2) cout << "ONLINE_BACK" << endl;
        else if(pos==-2) cout << "ONLINE_FRONT" << endl;
        else  cout << "ON_SEGMENT" << endl;
    }
    return 0;
}
