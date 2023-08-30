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
1004535809 3
998244353 3
*/

const int P=998244353;//模数
const int G=3;//原根

ll wn[N << 2], rev[N << 2];
//传入最终数组大小
int NTT_init(int n_) {
    int step = 0; int n = 1;
    for ( ; n < n_; n <<= 1) step++;
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
void NTT(ll a[], int n, int f) {
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




void err(){
    ll f[N<<2], g[N<<2];
    int n, m;
    std::cin>>n>>m;
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
    /*
    FTT测试
    1 2
    1 2
    1 2 1
    A: 1 4 5 2

    5 5
    1 7 4 0 9 4 
    8 8 2 4 5 5 
    A: 8 64 90 50 113 160 105 64 61 65 20 
    */

}
