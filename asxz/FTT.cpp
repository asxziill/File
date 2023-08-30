//注意FTT的浮点数!!!
const double PI = acos(-1);
const double EPS=1e-8;
//简单定义复数
struct C {
    //r实数，i虚数
    double r, i;
    C(double r = 0, double i = 0): r(r), i(i) {}
};
C operator + (const C& a, const C& b) {
    return C(a.r + b.r, a.i + b.i);
}
C operator - (const C& a, const C& b) {
    return C(a.r - b.r, a.i - b.i);
}
C operator * (const C& a, const C& b) {
    return C(a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r);
}

//传入数组，n要是2的倍数, p是是否为逆
void FFT(C x[], int n, int p) {
    for (int i = 0, t = 0; i < n; ++i) {
        if (i > t) std::swap(x[i], x[t]);
        for (int j = n >> 1; (t ^= j) < j; j >>= 1);
    }
    for (int h = 2; h <= n; h <<= 1) {
        C wn(cos(p * 2 * PI / h), sin(p * 2 * PI / h));
        for (int i = 0; i < n; i += h) {
            C w(1, 0), u;
            for (int j = i, k = h >> 1; j < i + k; ++j) {
                u = x[j + k] * w;
                x[j + k] = x[j] - u;
                x[j] = x[j] + u;
                w = w * wn;
            }
        }
    }
    if (p == -1){
        for (int i=0; i<n; i++){
            x[i].r /= n;
        }
    }
}

//数组建议开两倍
//a为结果
//（n 必须超过 a 和 b 的最高指数之和）
void conv(C a[], C b[], int n) {
    FFT(a, n, 1);
    FFT(b, n, 1);
    for (int i=0; i<n; i++){
        a[i] = a[i] * b[i];
    }
    FFT(a, n, -1);
}

int get_n(int _n){
    int n=1;
    while (n<_n) n*=2;
    return n;
}

void err(){
    C f[N<<2], g[N<<2];
    int n, m;
    std::cin>>n>>m;
    for (int i=0; i<=n; i++){
        std::cin>>f[i].r;
    }

    for (int i=0; i<=m; i++){
        std::cin>>g[i].r;
    }

    int out=n+m+1;
    int ln=get_n(out);

    conv(f, g, ln);

    std::cout<<std::fixed<<std::setprecision(0);
    for (int i=0; i<out; i++){
        if (std::abs(f[i].r)<EPS) f[i]=0;
        std::cout<<f[i].r<<" \n"[i==out-1];
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
