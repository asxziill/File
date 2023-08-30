template<class T>
struct ST
{
    int n;
    int lgn;
    bool isST=false;
    std::vector<std::vector<T>> a;
    ST(){}
    ST(const std::vector<T> &v){
        init(v);
    }
    void init(const std::vector<T> &v){
        n=v.size();
        lgn=std::__lg(n);
        a.assign(lgn+1, std::vector<T>(n));
        for (int i=0; i<n; i++){
            a[0][i]=v[i];
        }
        for (int j=0; j<lgn; j++){
            for (int i=0; i+(2<<j)<=n; i++){
                a[j+1][i]=a[j][i] + a[j][i+(1<<j)];
            }
        }
    }

    void setIs(T v){
        if ((v+v)==v){
            isST=true;
        }
        else{
            isST=false;
        }
    }
    void setTrue(){
        isST=true;
    }
    void SetFalse(){
        isST=false;
    }

    T STQ(int l, int r){
        int len=r-l+1;
        int lg=std::__lg(len);
        return a[lg][l]+a[lg][r-(1<<lg)+1];
    }

    T Mul(int l, int r){
        T res;
        int p=l;
        for (int i=lgn; i>=0; i--){
            if (p+(1<<i)-1<=r){
                res=res+a[i][p];
                p=p+(1<<i);
            }
        }
        return res;
    }

    T operator()(int l, int r){
        if (isST){
            return STQ(l, r);
        }
        else{
            return Mul(l, r);
        }
    }
};
