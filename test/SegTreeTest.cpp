#include<iostream>
#include<../src/segTree.hpp>
using namespace std;

int main(){
    long long N; cin>>N;
    int q; cin>>q;
    const long long MOD = 1000000007;
    vector<long long> V(N);
    for(int i=0;i<N;++i)cin>>V[i];
    SegTree<long long> ss;
    ss.v = V;
    ss.N = N;
    ss.pre();
    while(q--){
        int l,r; cin>>l>>r;
        long long res = ss.query(l,r-1);
        cout<<res<<endl;
    }
}
