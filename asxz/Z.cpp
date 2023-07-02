const int P=1e9+7;
ll norm(ll x){
    if (x<0){
        x+=P;
    }
    if (x>=P){
        x-=P;
    }
    return x;
}
template<class T>
T qpow(T a, ll b){
    T res=1;
    for (; b; b/=2, a*=a){
        if (b%2){
            res*=a;
        }
    }
    return res;
}
struct Z{
    ll x;
    Z(ll x=0):x(norm(x%P)){
    }
    ll val()const{
        return x;
    }
    Z operator-()const{
        return Z(norm(P-x));
    }
    Z inv()const{
        assert(x!=0);
        return qpow(*this, P-2);
    }
    Z &operator*=(const Z &rhs) {
        x = x * rhs.x % P;
        return *this;
    }
    Z &operator+=(const Z &rhs) {
        x = norm(x + rhs.x);
        return *this;
    }
    Z &operator-=(const Z &rhs) {
        x = norm(x - rhs.x);
        return *this;
    }
    Z &operator/=(const Z &rhs) {
        return *this *= rhs.inv();
    }
    friend Z operator*(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res *= rhs;
        return res;
    }
    friend Z operator+(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res += rhs;
        return res;
    }
    friend Z operator-(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res -= rhs;
        return res;
    }
    friend Z operator/(const Z &lhs, const Z &rhs) {
        Z res = lhs;
        res /= rhs;
        return res;
    }
    friend std::istream &operator>>(std::istream &is, Z &a) {
        ll v;
        is >> v;
        a = Z(v);
        return is;
    }
    friend std::ostream &operator<<(std::ostream &os, const Z &a) {
        return os << a.val();
    }
};
