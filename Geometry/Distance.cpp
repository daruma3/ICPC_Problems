//距離を計算する用のメソッド置き場
#include<bits/stdc++.h>
//#include"geometry.h"
using namespace std;
const double EPS = 1e-9;   // 許容誤差。問題によって変える
typedef complex<double> P; // Point
#define X real()
#define Y imag()
double norm(P &p1, P &p2)
{
    return (p1.X - p2.X) * (p1.X - p2.X) + (p1.Y - p2.Y) * (p1.Y - p2.Y);
}
namespace std
{
bool operator<(const P p1, const P p2)
{
    return p1.X != p2.X ? p1.X < p2.X : p1.Y < p2.Y;
}
P operator+(const P p1, const P p2) { return P(p1.X + p2.X, p1.Y + p2.Y); }
P operator-(const P p1, const P p2) { return P(p1.X - p2.X, p1.Y - p2.Y); }
P operator*(const P p, double k) { return P(p.X * k, p.Y * k); }
P operator/(const P p, double k) { return P(p.X / k, p.Y / k); }
} // namespace std

//Segment/L
struct Segment
{
    P p1, p2;
    Segment() {}
    Segment(P p1, P p2) : p1(p1), p2(p2) {}
};
typedef Segment L;

//外積cross(a,b) = |a||b|sinθ=a1b2+a2b1
double cross(const P &a, const P &b)
{
    return (conj(a) * b).Y;
}
//内積dot(a,b) = |a||b|cosθ=a1b1+a2b2
double dot(const P &a, const P &b)
{
    return (conj(a) * b).X;
}

P Projection(L l, P p)
{
    P base = l.p2 - l.p1;                        //始点
    double r = dot(p - l.p1, base) / norm(base); //線分に対する倍率の計算
    return l.p1 + base * r;
}

P Reflection(L l, P p)
{
    return p + (Projection(l, p) - p) * 2.0;
}
//位置関係判定(線分abを軸にcがどちら側にあるか)
int ccw(P a, P b, P c)
{
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
bool intersectLL(const L &l, const L &m)
{
    return abs(cross(l.p2 - l.p1, m.p2 - m.p1)) > EPS || // non-parallel
           abs(cross(l.p2 - l.p1, m.p1 - l.p1)) < EPS;   // same L
}
bool intersectLS(const L &l, const L &s)
{
    return cross(l.p2 - l.p1, s.p1 - l.p1) * // s.p1 is left of l
               cross(l.p2 - l.p1, s.p2 - l.p1) <
           EPS; // s.p2 is right of l
}
bool intersectLP(const L &l, const P &p)
{
    return abs(cross(l.p2 - p, l.p1 - p)) < EPS;
}
bool intersectSS(const L &s, const L &t)
{
    return ccw(s.p1, s.p2, t.p1) * ccw(s.p1, s.p2, t.p2) <=0 &&
        ccw(t.p1, t.p2, s.p1) * ccw(t.p1, t.p2, s.p2) <= 0;
}
bool intersectSP(const L &s, const P &p)
{
    return abs(s.p1 - p) + abs(s.p2 - p) - abs(s.p2 - s.p1) < EPS; // triangle inequality
}

double distanceLP(const L &l, const P &p){
    return abs(p - Projection(l, p));
}
double distanceLL(const L &l, const L &m){
    return intersectLL(l, m) ? 0 : distanceLP(l, m.p1);
}
double distanceLS(const L &l, const L &s){
    if (intersectLS(l, s))
        return 0;
    return min(distanceLP(l, s.p1), distanceLP(l, s.p2));
}
double distanceSP(const L &s, const P &p){
    const P r = Projection(s, p);
    if (intersectSP(s, r))
        return abs(r - p);
    return min(abs(s.p1 - p), abs(s.p2 - p));
}
double distanceSS(const L &s, const L &t){
    if (intersectSS(s, t))
        return 0;
    return min(min(distanceSP(s, t.p1), distanceSP(s, t.p2)),
               min(distanceSP(t, s.p1), distanceSP(t, s.p2)));
}
P crosspoint(const L &l, const L &m){
    double A = cross(l.p2 - l.p1, m.p2 - m.p1);
    double B = cross(l.p2 - l.p1, l.p2 - m.p1);
    if (abs(A) < EPS && abs(B) < EPS)
        return m.p1; // same line
    if (abs(A) < EPS)
        assert(false); // !!!PRECONDITION NOT SATISFIED!!!
    return m.p1 + B / A * (m.p2 - m.p1);
}

//Verify
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_D&lang=jp
int main(){
    int q;
    cin>>q;
    for (int i = 0; i < q;i++){
        double x0,x1,x2,x3,y0,y1,y2,y3;
        cin>>x0>>y0>>x1>>y1>>x2>>y2>>x3>>y3;
        P p0 = P(x0, y0), p1 = P(x1, y1), p2 = P(x2, y2), p3 = P(x3, y3);
        const L l1 = L(p0, p1), l2 = L(p2, p3);
        printf("%.16f\n", distanceSS(l1, l2));
    }
    return 0;
}
