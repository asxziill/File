//����d=gcd(a, b), x,yΪax+by=d���ؽ� 
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

//x%mod����Ԫ��Ҫ��gcd(x, mod)=1
template<class T>
T inv(T x, T mod){
    T inx, y;
    T d=exgcd(x, mod, inx, y);
    assert(d==1);
    return (inx%mod+mod)%mod;
}

//���ax+by=c, �޽ⷵ�ؿ�,���򷵻ؽ����ƶ�����ԣ�0a,1b;Ĭ����x��ԭ�����
template<class T>
std::vector<std::pair<T, T>> DiophantineEquation(T a, T b, T c){
    std::vector<std::pair<T, T>> res;
    T x, y;
    T d=exgcd(a, b, x, y);
    if (c%d!=0){
        return res;
    }
    c/=d;
    a/=d;
    b/=d;
    x=(x*c%b + b)%b;
    y=(c-x*a)/b;
    res.emplace_back(x, b);
    res.emplace_back(y, a);
    return res;
}
