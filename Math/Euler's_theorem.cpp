#include<bits/stdc++.h>
using namespace std;
const int INF=1000000000;
typedef long long ll;

//count the number of mutually prime numbers
ll Euler_phi(ll n){
    ll count=n;
    for (ll i = 2; i <= sqrt(n);i++){
        if(n%i==0){
            count -= count / i;
            while(n%i==0)
                n /= i;
        }
    }
    if(n>1)
        count -= count / n;
    return count;
}

//verify AOJ NTL 1 D http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_D&lang=jp

int main(){
    ll n;
    cin >> n;
    cout<<Euler_phi(n)<<endl;
    return 0;
}