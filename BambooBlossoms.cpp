//ICPC 2016 Japan Online First-Round Contest Problem C "Bamboo Blossoms"
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=1610&lang=jp
#include<bits/stdc++.h>
using namespace std;
const int zahlen=7400000;
int main(){
    int m,n;
    cin>>m>>n;
    while(m){
        int count=0;
        bool bench[zahlen];
        for(int i=0;i<zahlen;i++) bench[i]=true;
        for(int i=m;count<n;i++){
            if(bench[i]){        //Judge i is a multiple or not
                for(int j=i;j<zahlen;j+=i) bench[j]=false;
                count++;
            }
        }
        for(int i=m;;i++){
            if(bench[i]){
                cout<<i<<endl;
                break;
            }
        }
        cin>>m>>n;
    }
    return 0;
}
