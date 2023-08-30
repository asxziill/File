//返回d=gcd(a, b), x,y为ax+by=d的特解 
template<class T>
T exgcd(T a, T b, T &x, T &y){
    if (b==0){
        x=1;
        y=0;
        return a;
    }
    T d=exgcd(b, a%b, y, x);
    y-=a/b*x;
    return d;
}

template<class T>
bool merge(T &m1, T &a1, T m2, T a2){
    T x, y;
    T d=exgcd(m1, m2, x, y);
    if ((a2-a1)%d!=0){
        return false;
    }
    T m=m1/d*m2;
    T td=(a2-a1)/d;
    T res=(x*m1*td+a1)%m;//可能超精度
    if (res<T(0)){
        res+=m;
    }
    m1=m, a1=res;
    return true;
}

//x%m=a
template<class T>
T excrt(const std::vector<T> &a, std::vector<T> &m){
    T res=-1;
    if (a.size()!=m.size() || a.size()==0){
        return res;
    }
    T M=m[0];
    T x=a[0];
    for (int i=1; i<a.size(); i++){
        if (!merge(M, x, m[i], a[i])){
            return res;
        }
    }
    res=x;
    return res;
}
