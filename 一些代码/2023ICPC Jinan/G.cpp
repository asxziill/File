#include <bits/stdc++.h>

using ll = long long;

using i64 = long long;
template<class T>
constexpr T power(T a, i64 b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}
 
constexpr i64 mul(i64 a, i64 b, i64 p) {
    i64 res = a * b - i64(1.L * a * b / p) * p;
    res %= p;
    if (res < 0) {
        res += p;
    }
    return res;
}
template<i64 P>
struct MLong {
    i64 x;
    constexpr MLong() : x{} {}
    constexpr MLong(i64 x) : x{norm(x % getMod())} {}
    
    static i64 Mod;
    constexpr static i64 getMod() {
        if (P > 0) {
            return P;
        } else {
            return Mod;
        }
    }
    constexpr static void setMod(i64 Mod_) {
        Mod = Mod_;
    }
    constexpr i64 norm(i64 x) const {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }
    constexpr i64 val() const {
        return x;
    }
    explicit constexpr operator i64() const {
        return x;
    }
    constexpr MLong operator-() const {
        MLong res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr MLong inv() const {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }
    constexpr MLong &operator*=(MLong rhs) & {
        x = mul(x, rhs.x, getMod());
        return *this;
    }
    constexpr MLong &operator+=(MLong rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr MLong &operator-=(MLong rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr MLong &operator/=(MLong rhs) & {
        return *this *= rhs.inv();
    }
    friend constexpr MLong operator*(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr MLong operator+(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr MLong operator-(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr MLong operator/(MLong lhs, MLong rhs) {
        MLong res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr std::istream &operator>>(std::istream &is, MLong &a) {
        i64 v;
        is >> v;
        a = MLong(v);
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const MLong &a) {
        return os << a.val();
    }
    friend constexpr bool operator==(MLong lhs, MLong rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(MLong lhs, MLong rhs) {
        return lhs.val() != rhs.val();
    }
};
 
template<>
i64 MLong<0LL>::Mod = i64(1E18) + 9;
 
template<int P>
struct MInt {
    int x;
    constexpr MInt() : x{} {}
    constexpr MInt(i64 x) : x{norm(x % getMod())} {}
    
    static int Mod;
    constexpr static int getMod() {
        if (P > 0) {
            return P;
        } else {
            return Mod;
        }
    }
    constexpr static void setMod(int Mod_) {
        Mod = Mod_;
    }
    constexpr int norm(int x) const {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }
    constexpr int val() const {
        return x;
    }
    explicit constexpr operator int() const {
        return x;
    }
    constexpr MInt operator-() const {
        MInt res;
        res.x = norm(getMod() - x);
        return res;
    }
    constexpr MInt inv() const {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }
    constexpr MInt &operator*=(MInt rhs) & {
        x = 1LL * x * rhs.x % getMod();
        return *this;
    }
    constexpr MInt &operator+=(MInt rhs) & {
        x = norm(x + rhs.x);
        return *this;
    }
    constexpr MInt &operator-=(MInt rhs) & {
        x = norm(x - rhs.x);
        return *this;
    }
    constexpr MInt &operator/=(MInt rhs) & {
        return *this *= rhs.inv();
    }
    friend constexpr MInt operator*(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res *= rhs;
        return res;
    }
    friend constexpr MInt operator+(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res += rhs;
        return res;
    }
    friend constexpr MInt operator-(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res -= rhs;
        return res;
    }
    friend constexpr MInt operator/(MInt lhs, MInt rhs) {
        MInt res = lhs;
        res /= rhs;
        return res;
    }
    friend constexpr std::istream &operator>>(std::istream &is, MInt &a) {
        i64 v;
        is >> v;
        a = MInt(v);
        return is;
    }
    friend constexpr std::ostream &operator<<(std::ostream &os, const MInt &a) {
        return os << a.val();
    }
    friend constexpr bool operator==(MInt lhs, MInt rhs) {
        return lhs.val() == rhs.val();
    }
    friend constexpr bool operator!=(MInt lhs, MInt rhs) {
        return lhs.val() != rhs.val();
    }
};
 
template<>
int MInt<0>::Mod = 998244353;
 
template<int V, int P>
constexpr MInt<P> CInv = MInt<P>(V).inv();

constexpr int P = int(1e9) + 7;
using Z = MInt<P>;
using D = MInt<2>;

template<class T>
struct DSU {
    std::vector<int> f, siz;
    std::vector<T> dis;
    DSU() {}
    DSU(int n) {
        init(n);
    }
    
    void init(int n) {
        n+=10;
        f.resize(n);
        std::iota(f.begin(), f.end(), 0);
        siz.assign(n, 1);
        dis.assign(n, T());
    }
    
    int find(int x) {
        if (x != f[x]) {
            int fa = f[x];
            f[x] = find(f[x]);
            dis[x] = dis[x] + dis[fa];
        }
        return f[x];
    }
    
    bool same(int x, int y) {
        return find(x) == find(y);
    }

    bool DisSame(int x, int y){
        return (find(x) == find(y)) && (dis[x]==dis[y]);
    }
    
    int merge(int x, int y, T d=T()) {
        int fx = find(x);
        int fy = find(y);
        if (fx == fy) {
            T set_d = dis[x] - dis[y];
            if (set_d == d){
                return 0;
            }
            else{
                return -1;
            }
        }
        else{
            f[fx] = fy;
            dis[fx] = d + dis[y] - dis[x];
            siz[fy] += siz[fx];
            return 1;
        }
    }
    
    int size(int x) {
        return siz[find(x)];
    }

    T getdis(int x){
        find(x);
        return dis[x];
    }
};

void solve(){
	int n, m;
	std::cin >> n >> m;
	std::vector<std::string> s(n);
	DSU<D> dsu(n);

	for (int i = 0; i < n; i++){
		std::cin >> s[i];
	}

	for (int i = 0; i <= m - 1 - i; i++){
		if (i == m - 1 - i){
			int cnt = 0;
			for (int j = 0; j < n; j++){
				if (s[j][i] == '1') cnt++;
			}
			if (cnt >= 2){
				std::cout << 0 << "\n";
				return;
			}
		}
		else{
			std::vector<int> a;
			std::vector<int> pos;
			std::array<int, 3> cnt{};
			for (int j = 0; j < n; j++){
				if (s[j][i] == '1' && s[j][m - i - 1] == '1'){
					a.push_back(2);
					pos.push_back(j);
					cnt[2] += 1;
				}
				else if (s[j][i] == '1' && s[j][m - i - 1] == '0'){
					a.push_back(1);
					pos.push_back(j);
					cnt[1] += 1;
				}
				else if (s[j][i] == '0' && s[j][m - i - 1] == '1'){
					a.push_back(0);
					pos.push_back(j);
					cnt[0] += 1;
				}
			}
			if (cnt[2] >= 2 || (cnt[2] >= 1 && (cnt[1] + cnt[0]) >= 1)){
				std::cout << 0 << "\n";
				return;
			}
			if ((cnt[0] + cnt[1]) > 2 || a.size() > 2){
				std::cout << 0 << "\n";
				return;
			}

			if (a.size() == 2){
				if (dsu.merge(pos[0], pos[1], D(a[0] == a[1])) == -1){
					std::cout << 0 << "\n";
					return;
				}
			}
		}
	}

	int cnt = 0;
	for (int i = 0; i < n; i++){
		if (dsu.find(i) == i){
			cnt += 1;
		}
	}
	Z ans = power(Z(2), cnt);
	std::cout << ans << "\n";
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;

    while (t--){
    	solve();
    }
    return 0;
}