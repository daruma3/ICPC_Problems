#include<bits/stdc++.h>
using namespace std;

typedef long long ll;
const ll INF = 1000000000000000000, MOD = 1000000007;

//互いに素にする
ll PreGarner(vector<ll> &b,vector<ll> &m){
    ll pg = 1;
    for (int i = 0; i < (int)b.size();i++){
        for (int j = 0; j < i;j++){
            ll g = __gcd(m[i], m[j]);
            if((b[i]-b[j])%g!=0)
                return -1;
            m[i] /= g;
            m[j] /= g;
            ll gi = __gcd(m[i], g), gj = g / gi;
            while((g=__gcd(gi,gj))!=1){
                gi *= g;
                gj /= g;
            }
            m[i] *= gi, m[j] *= gj;
            b[i] %= m[i], b[j] %= m[j];
        }
    }
    for (int i = 0; i < (int)b.size();i++)
        pg *= m[i]/*%=MOD */;
    return pg;
}

ll Mod(ll x,ll m){
    ll mod=x%m;
    if(mod<0)
        mod += m;
    return mod;
}

//拡張Euclid
ll ExtendGCD(ll a,ll b,ll &p,ll &q){
    if(b==0){
        p = 1;
        q = 0;
        return a;
    }
    ll d=ExtendGCD(b,a%b,q,p);
    q -= a / b * p;
    return d;
}

//逆元(a,mは互いに素)
ll modinv(ll a,ll m){
    ll x, y;
    ExtendGCD(a, m, x, y);
    return Mod(x, m);
}

//Garnerのアルゴリズム
//coeffs[k]*t[k]+constants[k]=b[k](mod m[k])
//coeffs[k]=m[0]m[1]...m[k-1]
//constants[k]=t[0]+t[1]m[0]+..+t[k-1]m[0]m[1]..m[k-2]

ll Garner(vector <ll> b,vector<ll> m,ll mod){
    //番兵（最後ここの数値でmodをとり出力．制限ない場合はINF推奨）
    m.push_back(mod);
    vector<ll> coeffs((int)m.size(), 1);
    vector<ll> constants((int)m.size(), 0);
    for (int k = 0; k < (int)b.size();k++){
        ll t = Mod((b[k] - constants[k]) * modinv(coeffs[k], m[k]), m[k]);
        for (int i = k + 1;i<(int)m.size();i++){
            (constants[i] += t * coeffs[i]) %= m[i];
            (coeffs[i] *= m[k]) %= m[i];
        }
    }
    return constants.back();
}




//verify yukicoder 中華風(easy) https://yukicoder.me/problems/no/186
int main(){
    vector<ll> b(3), m(3);
    bool exist_non_zero = false;
    for (int i = 0; i < 3;i++){
        cin >> b[i] >> m[i];
        if(b[i])
            exist_non_zero = true;
    }
    ll pg = PreGarner(b, m);
    if(!exist_non_zero)
        cout << pg << endl;
    else if(pg==-1)
        cout << -1 << endl;
    else
        cout << Garner(b, m,INF) << endl;
    return 0;
}