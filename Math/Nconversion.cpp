#include<bits/stdc++.h>
using namespace std;

void Nconversion(double x,double n){
    
    stack<int> nconv;
    if(x>=1){
        int tmpx = (int)x, tmpn = (int)n;
        for(;tmpx>0;tmpx/=tmpn){
            nconv.push(tmpx % tmpn);
        }
    }else{
        double p=n;
        for(int i=0;i<10 and x>0;i++){
            int tmp = (int)(x * p);
            nconv.push(tmp);
            x-=(double)tmp*p;
            p *= n;
        }
    }
    while(!nconv.empty()){
        cout<<nconv.top();
        nconv.pop();
    }
    cout << endl;
}

int main(){
    double x,n;
    cin>>x>>n;
    Nconversion(x,n);
    return 0;
}