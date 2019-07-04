#include<bits/stdc++.h>
using namespace std;
const double EPS = 1e-9;    // Allowable Error
typedef complex<double> P;  // Point
#define X real()
#define Y imag()
double norm(P& p1,P& p2){
    return (p1.X-p2.X)*(p1.X-p2.X)+(p1.Y-p2.Y)*(p1.Y-p2.Y);
}
namespace std{
    bool operator < (const P p1, const P p2){
        return p1.X != p2.X ? p1.X <p2.X : p1.Y < p2.Y;
    }
    P operator + (const P p1,const P p2) {return P(p1.X+p2.X,p1.Y+p2.Y);}
    P operator - (const P p1,const P p2) {return P(p1.X-p2.X,p1.Y-p2.Y);}
    P operator * (const P p,double k) {return P(p.X*k,p.Y*k);}
    P operator / (const P p,double k) {return P(p.X/k,p.Y/k);}
}
//Line
struct Segment{
    P p1,p2;
    Segment(){}
    Segment(P p1,P p2):p1(p1),p2(p2){}
};
typedef Segment Line;

//Inner Product dot(a,b) = |a||b|cosÎ¸=a1b1+a2b2
double dot(const P& a, const P& b) {
  return (conj(a)*b).X;
}

P Projection(Line l,P p){
    P base=l.p2-l.p1;//始点
    double r=dot(p-l.p1,base)/norm(base);//線分に対する倍率の計算
    return l.p1+base*r;
}

//Verify
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_A
int main(){
    double x1,x2,y1,y2,x,y;
    cin>>x1>>y1>>x2>>y2;
    Line l=Line(P(x1,y1),P(x2,y2));
    int q;
    cin>>q;
    for(int i=0;i<q;i++){
        cin>>x>>y;
        P p=Projection(l,P(x,y));
        printf("%.10f %.10f\n",p.X,p.Y);
    }

    return 0;
}
