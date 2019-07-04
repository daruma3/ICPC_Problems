//Intersection Determination
#include<bits/stdc++.h>
using namespace std;
const double EPS = 1e-9;    // 許容誤差。問題によって変える
typedef complex<double> P;  // Point
#define X real()
#define Y imag()
double norm(P &p1, P &p2){
    return (p1.X - p2.X) * (p1.X - p2.X) + (p1.Y - p2.Y) * (p1.Y - p2.Y);
}
namespace std{
    bool operator<(const P p1, const P p2){
        return p1.X != p2.X ? p1.X < p2.X : p1.Y < p2.Y;
    }
    P operator+(const P p1, const P p2) { return P(p1.X + p2.X, p1.Y + p2.Y); }
    P operator-(const P p1, const P p2) { return P(p1.X - p2.X, p1.Y - p2.Y); }
    P operator*(const P p, double k) { return P(p.X * k, p.Y * k); }
    P operator/(const P p, double k) { return P(p.X / k, p.Y / k); }
} 

//Segment/Line
struct Segment{
    P p1, p2;
    Segment() {}
    Segment(P p1, P p2) : p1(p1), p2(p2) {}
};
typedef Segment Line;

//外積cross(a,b) = |a||b|sinθ=a1b2+a2b1
double cross(const P &a, const P &b){
    return (conj(a) * b).Y;
}
//内積dot(a,b) = |a||b|cosθ=a1b1+a2b2
double dot(const P &a, const P &b){
    return (conj(a) * b).X;
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
    else
        return 0; //他
}

//Intersection Determination
bool intersectLL(const Line &l, const Line &m){
    return abs(cross(l.p2 - l.p1, m.p2 - m.p1)) > EPS || // non-parallel
        abs(cross(l.p2 - l.p1, m.p1 - l.p1))  < EPS;       // same line
                                                      
}
bool intersectLS(const Line &l, const Line &s){
    return cross(l.p2 - l.p1, s.p1 - l.p1) * // s.p1 is left of l
               cross(l.p2 - l.p1, s.p2 - l.p1) <EPS; // s.p2 is right of l
}
bool intersectLP(const Line &l, const P &p){
    return abs(cross(l.p2 - p, l.p1 - p)) < EPS;
}
bool intersectSS(const Line &s, const Line &t){
    return ccw(s.p1, s.p2, t.p1) * ccw(s.p1, s.p2, t.p2) <= 0 &&
           ccw(t.p1, t.p2, s.p1) * ccw(t.p1, t.p2, s.p2) <= 0;
}
bool intersectSP(const Line &s, const P &p){
    return abs(s.p1 - p) + abs(s.p2 - p) - abs(s.p2 - s.p1) < EPS; // triangle inequality
}

//Verify
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_A&lang=jp
int main(){
    int q;
    cin>>q;
    for (int i = 0; i < q;i++){
        double x0,x1,x2,x3,y0,y1,y2,y3;
        cin>>x0>>y0>>x1>>y1>>x2>>y2>>x3>>y3;
        P p0 = P(x0, y0), p1 = P(x1, y1), p2 = P(x2, y2), p3 = P(x3, y3);
        const Line l1 = Line(p0, p1), l2 = Line(p2, p3);
        if (intersectSS(l1, l2) )
            cout << "1" << endl;
        else
            cout << "0" << endl;
    }
    return 0;
}
