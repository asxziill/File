#include <bits/stdc++.h>

const int N=1e5+5;
const int M=1e5+5;
const int inf=0x3fffffff;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 lll;

ll qpow(ll a, ll b, ll p){
    ll res= (p!=1);
    while (b){
        if (b&1){
            res=res*a%p;
        }
        a=a*a%p;
        b>>=1;
    }
    return res;
}

ll get_inv(ll x, ll p){
    return qpow(x, p-2, p);
}

/*
FTT测试
1 2
1 2
1 2 1
1 4 5 2
*/

/*
1004535809 3
998244353 3
*/

const int P=998244353;//模数
const int G=3;//原根

std::vector<ll> wn, rev;
//传入最终数组大小
int NTT_init(int n_) {
    int step = 0; int n = 1;
    for ( ; n < n_; n <<= 1) step++;
    if (wn.size()<n+1){
        wn.resize(n+1);
    }
    if (rev.size()<n+1){
        rev.resize(n+1);
    }
    for (int i=1; i<n; i++){
        rev[i] = (rev[i >> 1] >> 1) | ( (i & 1) << (step - 1) );
    }
    int g = qpow(G, (P - 1) / n, P);
    wn[0] = 1;
    for (int i = 1; i <= n; ++i){
        wn[i] = wn[i - 1] * g % P;
    }
    return n;
}

//数组可换vector 建议开两倍 要引用
//f为是否为逆
void NTT(std::vector<ll> &a, int n, int f) {
    if (a.size()<n){
        a.resize(n);
    }
    for (int i=0; i<n; i++){
        if (i < rev[i]){
            std::swap(a[i], a[rev[i]]);
        }
    }
    for (int k = 1; k < n; k <<= 1) {
        for (int i = 0; i < n; i += (k << 1)) {
            int t = n / (k << 1);
            for (int j=0; j<k; j++){
                ll w = f == 1 ? wn[t * j] : wn[n - t * j];
                ll x = a[i + j];
                ll y = a[i + j + k] * w % P;
                a[i + j] = (x + y) % P;
                a[i + j + k] = (x - y + P) % P;
            }
        }
    }
    if (f == -1) {
        ll ninv = get_inv(n, P);
        for (int i=0; i<n; i++){
            a[i] = a[i] * ninv % P;
        }
    }
}





int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin>>n>>m;
    std::vector<ll> f(n+1), g(m+1);
    for (int i=0; i<=n; i++){
        std::cin>>f[i];
        f[i]%=P;
    }
    for (int i=0; i<=m; i++){
        std::cin>>g[i];
        g[i]%=P;
    }
    int out=n+m+1;
    int ln=NTT_init(out);
    NTT(f, ln, 1);
    NTT(g, ln, 1);
    for (int i=0; i<ln; i++){
        f[i]=f[i]*g[i]%P;
    }
    NTT(f, ln, -1);
    for (int i=0; i<out; i++){
        std::cout<<f[i]<<" \n"[i==out-1];
    }
    return 0;
}
