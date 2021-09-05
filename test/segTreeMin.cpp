#include<vector>
#include<iostream>
using namespace std;
#define INF 0xfffffffffffffff
template<typename T> inline T Max(T a, T b){return a>b?a:b;}
template<typename T> inline T Min(T a, T b){return a<b?a:b;}
template<typename T> inline T __Gcd(T a, T b){ return b==0 ? a : __gcd(b,a%b);}
template<typename T> struct SegTree {
    T N;
    vector<T> v;
    vector<T> seg;
    void init(int st, int end, int ind){
        if(st==end){
            seg[ind]=v[st];
            return;
        }
        int mid = (st+end)/2;
        init(st,mid,2*ind+1);
        init(mid+1,end, 2*ind+2);
        seg[ind]=f(seg[2*ind+1],seg[2*ind+2]);
    }
    T f(T a, T b){
        //define function here, here fucntion is sum
        //return a+b;  // uncomment for sum query
        
        //for gcd
        // return __gcd(a,b);
        
        // for maxm
        // return max(a,b);

        return Min(a,b);  //comment out for sum query
    }
    void pre() {
        seg.resize(4*N);
        init(0,N-1,0);
    }
    
    T query(int l,int r){
        return _query(0,l,r,0,N-1);
    }
    
    T _query(int node, int l,int r, int st,int en){
        if(l>en||r<st)return INF; // replace INF with zero for sum query
        if(st>=l&&en<=r)return seg[node];
        int mid = (st+en)/2;
        return f(_query(2*node+1,l,r,st,mid),_query(2*node+2,l,r,mid+1,en));
    }
    
};

int main(){
    long long n,q;
    cin>>n>>q;
    vector<long long> v(n);
    for(auto &x : v) cin>>x;
    SegTree<long long> segt;
    segt.N = n;
    segt.v = v;
    segt.pre();
    while(q--){
        int l,r; cin>>l>>r;
        cout<<segt.query(l,r-1)<<endl;
    }

}



