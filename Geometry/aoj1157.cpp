#include<bits/stdc++.h>
using namespace std;
const double EPS = 1e-9,INF=114514;    // 許容誤差。問題によって変える
typedef complex<double> P;  // Point
#define X real()
#define Y imag()
namespace std{
    bool operator<(const P p1, const P p2){
        return p1.X != p2.X ? p1.X < p2.X : p1.Y < p2.Y;
    }
    P operator+(const P p1, const P p2) { return P(p1.X + p2.X, p1.Y + p2.Y); }
    P operator-(const P p1, const P p2) { return P(p1.X - p2.X, p1.Y - p2.Y); }
    P operator*(const P p, double k) { return P(p.X * k, p.Y * k); }
    P operator/(const P p, double k) { return P(p.X / k, p.Y / k); }
}

double norm(P &p1, P &p2){
    return (p1.X - p2.X) * (p1.X - p2.X) + (p1.Y - p2.Y) * (p1.Y - p2.Y);
}

//Segment/L
struct Segment{
    P p1, p2;
    Segment() {}
    Segment(P p1, P p2) : p1(p1), p2(p2) {}
};
typedef Segment L;

//外積cross(a,b) = |a||b|sinθ=a1b2-a2b1
double cross(const P &a, const P &b){
    return (conj(a) * b).Y;
}
//内積dot(a,b) = |a||b|cosθ=a1b1+a2b2
double dot(const P &a, const P &b){
    return (conj(a) * b).X;
}

P Projection(L l, P p){
    P base = l.p2 - l.p1;                        //始点
    double r = dot(p - l.p1, base) / norm(base); //線分に対する倍率の計算
    return l.p1 + base * r;
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
bool intersectSS(const L &s, const L &t){
    return ccw(s.p1, s.p2, t.p1) * ccw(s.p1, s.p2, t.p2) <= 0 &&
           ccw(t.p1, t.p2, s.p1) * ccw(t.p1, t.p2, s.p2) <= 0;
}
bool intersectSP(const L &s, const P &p){
    return abs(s.p1 - p) + abs(s.p2 - p) - abs(s.p2 - s.p1) < EPS; // triangle inequality
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


int main(){
    int N;
    while(cin>>N and N){
        double ans = INF;
        double sx, sy, ex, ey;
        cin>> sx >> sy >> ex >> ey;
        P sp = P(sx, sy), ep = P(ex, ey);
        L root = L(sp, ep);
        for (int i = 0; i < N;i++){
            double x1,x2,y1,y2,h;
            cin>>x1>>y1>>x2>>y2>>h;
            P pt1=P(x1,y1),pt2=P(x2,y2),pt3=P(x1,y2),pt4=P(x2,y1);
            L h1=L(pt1,pt4),h2=L(pt4,pt2),h3=L(pt2,pt3),h4=L(pt3,pt1);
            if(x1<min(sx,ex) and x2>max(sx,ex) and y1<min(sy,ey) and y2>max(sy,ey))
                ans = 0;
            double d=min({distanceSS(root,h1),distanceSS(root,h2),distanceSS(root,h3),distanceSS(root,h4)});
            if(h<=d){
                ans = min(ans, (h * h + d * d) / (2 * h));
            }else{
                ans = min(ans, d);
            }
        }
        printf("%lf\n", ans);
    }
    return 0;
}
