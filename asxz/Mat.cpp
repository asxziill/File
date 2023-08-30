template<class T>
struct Mat
{
    std::vector<std::vector<T>> a;
    int n, m;

    Mat(int n=0){
        init(n, n);
    };
    Mat(int n, int m){
        init(n, m);
    };

    void init(int _n, int _m){
        a.assign(_n, std::vector<T>(_m, T()));
        n=_n, m=_m;
    }

    void set(){
        for (int i=0; i<n; i++){
            a[i][i]=T(1);
        }
    }

    Mat operator+(const Mat &b)const{
        Mat<T> res(n);
        for (int i=0; i<n; i++){
            for (int j=0; j<m; j++){
                res.a[i][j]=a[i][j]+b.a[i][j];
            }
        }
        return res;
    }

    Mat operator-(const Mat &b)const{
        Mat<T> res(n);
        for (int i=0; i<n; i++){
            for (int j=0; j<m; j++){
                res.a[i][j]=a[i][j]-b.a[i][j];
            }
        }
        return res;
    }

    Mat operator*(const Mat &b)const{
        // assert(m==b.n);
        Mat<T> res(n, b.m);
        
        for (int i=0; i<n; i++){
            for (int j=0; j<b.m; j++){
                for (int k=0; k<m; k++){
                    res.a[i][j]+=a[i][k]*b.a[k][j];
                }
            }
        }
        return res;
    }

    void err(){
        for (int i=0; i<n; i++){
            for (int j=0; j<m; j++){
                std::cout<<a[i][j]<<" ";
            }
            std::cout<<"\n";
        }
        std::cout<<"ERR"<<std::endl;
    }

    //对矩阵消元，不满秩不生效,消元后为行阶梯型,主要解线性方程组
    //返回自由变量的数量,和解
    std::pair<int, std::vector<T>> gauss(){
        std::vector<T> x(m-1);
        int r=0, c=0;
        while (r<n && c<m){
            int mxr=r;
            for (int i=r+1; i<n; i++){
                if (std::abs(a[i][c])>std::abs(a[mxr][c])){
                    mxr=i;
                }
            }
            if (mxr!=r){
                for (int j=c; j<m; j++){
                    std::swap(a[r][j], a[mxr][j]);
                }
            }

            if (a[r][c]==T(0)){
                a[r][c]=T(0);
                c++;
                continue;
            }

            for (int i=r+1; i<n; i++){
                if (a[i][c]){
                    T tmp=a[i][c]/a[r][c];
                    for (int j=c; j<m; j++){
                        a[i][j]-=a[r][j]*tmp;
                    }
                }
            }
            r++, c++;
        }

        for (int i=r; i<n; i++){
            if (a[i][m-1]!=T(0)){
                return {-1, x};
            }
        }

        if (r<m-1){
            return {m-1-r, x};
        }

        for (int i=m-2; i>=0; i--){
            T s=a[i][m-1];
            for (int j=i+1; j<m-1; j++){
                s-=a[i][j]*x[j];
            }
            x[i]=s/a[i][i];
        }
        return {0, x};
    }

    //异或下的高斯消元
    int XORgauss(){
        int r=0, c=0;
        while (r<n && c<m){
            int mxr=r;
            for (int i=r+1; i<n; i++){
                if (a[i][c]>a[mxr][c]){
                    mxr=i;
                }
            }
            if (mxr!=r){
                for (int j=c; j<m; j++){
                    std::swap(a[r][j], a[mxr][j]);
                }
            }
            if (a[r][c]==0){
                c++;
                continue;
            }

            for (int i=0; i<n; i++){
                if (i==r) continue;
                if (a[i][c]==1){
                    for (int j=c; j<m; j++){
                        a[i][j]^=a[r][j];
                    }
                }
            }
            r++, c++;
        }

        return r;
    }

    // //对满秩的行阶梯型化成行最简形
    // void E(){
    //     for (int i=0; i<n; i++){
    //         int k=-1;
    //         for (int j=0; j<m; j++){
    //             if (a[i][j]!=T(0)){
    //                 k=j;
    //                 break;
    //             }
    //         }
    //         if (k!=-1){
    //             T tmp=a[i][k];
    //             for (int j=0; j<m; j++){
    //                 a[i][j]/=tmp;    
    //             }
    //         }
    //         else{
    //             break;
    //         }
    //     }

    // }

};

struct LinearXOR
{
    using ull=unsigned long long;
    std::array<ull, 64> p;

    LinearXOR(){
        init();
    }
    void init(){
        p={};
    }

    bool insert(ull x){
        for (int i=63; ~i; i--){
            if (!(x>>i)) continue;
            if (!p[i]){
                p[i]=x;
                return true;
            }
            x^=p[i];
        }
        return false;
    }
};

void EG(){
    // int n, m;
    // std::cin>>n>>m;
    // Mat<double> a(n, m);
    // for (int i=0; i<n; i++){
    //     for (int j=0; j<m; j++){
    //         std::cin>>a.a[i][j];
    //     }
    // }
    // auto [y, x]=a.gauss();
    // a.err();
    // std::cout<<x.size()<<"\n";
    // std::cout<<"Y: "<<y<<"\n";
    // std::cout<<"X: ";
    // for (auto z:x) std::cout<<z<<" ";
    // std::cout<<"\n";
    // std::cout<<"ERR_EG"<<std::endl;
    // a.err();

    /*
    3 5
    2 0 5 6 9
    0 0 1 1 -4
    0 0 2 2 -8

    3 4
    1 3 4 5
    1 4 7 3
    9 3 2 2
    A:0 { -0.973684 5.18421 -2.39474}

    2 3
    1 1 2
    3 3 6

    3 4
    1 0 1 3
    0 1 0 4
    0 0 0 1
    A: -1

    3 4
    1 0 0 1
    0 1 0 2
    0 0 1 3
    A: 0 {1 2 3}

    */
}

void EXORG(){
    Mat<int> a(5, 3);
    std::vector<int> b={2, 3, 5, 6, 7};
    for (int i=0; i<5; i++){
        for (int j=0; j<3; j++){
            a.a[i][j]=(b[i]>>(2-j))&1;
        }
    }
    a.err();
    std::cout<<a.XORgauss()<<std::endl;
    a.err();
}
