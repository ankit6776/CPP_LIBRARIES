#include<vector>

// // Template reference: https://github.com/ankit6776/CPP_LIBRARIES/blob/master/src/segTree.hpp
template<typename T> inline T Max(T a, T b){return a>b?a:b;}
template<typename T> inline T Min(T a, T b){return a<b?a:b;}
template<typename T> inline T __Gcd(T a, T b){ return b==0 ? a : __Gcd(b,a%b);}
template<typename T> struct SegTree {
    long long int N;
    vector<T> v;
    vector<T> seg;
    vector<T> lazy;
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
        return max(a, b);  
        
    }
    void pre() {
        seg.resize(4*N);
        lazy.resize(4*N);
        init(0,N-1,0);
    }
    
    void point_update(int p, T x) {
        point_update_query(0,0,N-1,p,x);
    }
    
    T update_function(T x, T y){
        return f(x,y);
    }
    
    void point_update_query(int node, int st, int en, int ind, T x) {
        if(ind<st||ind>en)return;
        if(st==en) {
            seg[node] = update_function(seg[node], x);
            return;
        }
        int mid = (st+en)/2;
        ind<=mid ? point_update_query(2*node+1, st, mid, ind, x) : point_update_query(2*node+2, mid+1, en, ind, x);
        seg[node]=f(seg[2*node+1],seg[2*node+2]);
    }
    
    void update_range_query(int l, int r, T x) {
        update_range(0, 0, N-1, l, r, x);
    }

    void update_range(int node, int st, int en, int l, int r, T x) {
        if(st>en || st>r || l>en)return;
        if(st == en) {
            seg[node] = f(seg[node], x);
            return;
        }
        
        int mid = (st+en)/2;
        if(st>=l&&en<=r) {
            if(seg[node]<=x) { // lazy return condition
                seg[node]=x;
                lazy[node]=x;
                return;
            }
            if(lazy[node]>=x) {
                return;
            }
            seg[2*node+1]=f(seg[2*node+1], lazy[node]);
            seg[2*node+2]=f(seg[2*node+2], lazy[node]);
            lazy[2*node+1]=f(lazy[node], lazy[2*node+1]);
            lazy[2*node+2]=f(lazy[node], lazy[2*node+2]);
            update_range(2*node+1, st, mid, l,r,x);
            update_range(2*node+2, mid+1, en, l, r,x);
            seg[node]=f(seg[2*node+1], seg[2*node+2]);
            return;
        }
        seg[2*node+1]=f(seg[2*node+1], lazy[node]);
        seg[2*node+2]=f(seg[2*node+2], lazy[node]);
        lazy[2*node+1]=f(lazy[node], lazy[2*node+1]);
        lazy[2*node+2]=f(lazy[node], lazy[2*node+2]);
        update_range(2*node+1, st, mid, l, r, x);
        update_range(2*node+2, mid+1, en, l, r, x);
        seg[node]=f(seg[2*node+1], seg[2*node+2]);
    }
    
    T query(int l,int r){
        return _query(0,l,r,0,N-1);
    }
    
    T _query(int node, int l,int r, int st,int en){
        if(l>en||r<st)return 0; // replace INF with zero for sum query
        if(st>=l&&en<=r)return seg[node];
        int mid = (st+en)/2;
        return f(_query(2*node+1,l,r,st,mid),_query(2*node+2,l,r,mid+1,en));
    }

    T lazy_query(T x) {
        return _range_query(0,x, 0, N-1);
    }

    T _range_query(int node, T x, int st, int en) {
        if(st==en && st==x) return seg[node];
        int mid = (st+en)/2;
        seg[2*node+1]=f(seg[2*node+1], lazy[node]);
        seg[2*node+2]=f(seg[2*node+2], lazy[node]);
        lazy[2*node+1]=f(lazy[node], lazy[2*node+1]);
        lazy[2*node+2]=f(lazy[node], lazy[2*node+2]);
        if(mid>=x)return _range_query(2*node+1, x, st, mid);
        else return _range_query(2*node+2, x, mid+1, en);
    }
    
    //TODO(ankit6776): Add query implementation for range query in lazy propagation.
    
};

