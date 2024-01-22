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
using Z = MInt<998244353>;

constexpr int B = 330;

void solve(){
	int n, k;
	std::cin >> n >> k;
	std::vector<std::vector<int>> t(n);
	for (int i = 0; i < n - 1; i++){
		int u, v;
		std::cin >> u >> v;
		u--, v--;
		t[u].push_back(v);
		t[v].push_back(u);
	}

	std::vector<int> siz(n);
    // k <= B
	if (k <= B){
		auto dfs = [&](auto self, int u, int p)->std::vector<Z>{
			siz[u] = 1;

            //还剩连通块的大小
            std::vector<Z> dp(k + 2);
            dp[0] = 1;
			for (int v : t[u]){
				if (v == p) continue;
				auto dpv = self(self, v, u);

                std::vector<Z> f(k + 2);
				for (int i = std::min(k, siz[u] + siz[v]); i >= 0; i--){
                    //i - j >= siz[u]
                    for (int j = std::max(0, i - siz[u]); j <= std::min(i, siz[v]); j++){
                        f[i] += dp[i - j] * dpv[j];
                    }
                }

                std::swap(f, dp);
                siz[u] += siz[v];
			}

            for (int i = k; i >= 0; i--){
                dp[i + 1] = dp[i];
            }
            dp[0] = dp[k] + dp[k + 1];

            return dp;
		};

        auto res = dfs(dfs, 0, -1);
        std::cout << res[0] << "\n";
	}
    else{
        //移除几个k块，剩下的就是模(k + 1)的大小
        std::vector<std::bitset<B + 1>> vis(n);//对应是否可以组成
        auto dfs = [&](auto self, int u, int p)->std::vector<Z>{
            std::vector dp(1, std::vector<Z>(2));//根节点是否被切
            //类似分层图，通过根节点是否被切来维护合法状态
            //0为根节点未切，此时剩下的连通块的大小应该 <= k
            //否则切出去后，连通块大小应该一直保持k
            //分层是区分连通块大小是 0 还是k
            dp[0][0] = 1;

            for (int v : t[u]){
                if (v == p) continue;

                auto dpv = self(self, v, u);
                std::vector f(std::min(B, (siz[u] + siz[v]) / k) + 1, std::vector<Z>(2));
                for (int i = std::min(B, (siz[u] + siz[v]) / k); i >= 0; i--){
                    //i - j <= siz[u] / k
                    for (int j = std::max(0, i - (siz[u] / k)); j <= std::min(siz[v] / k, i); j++){
                        for (int stau : {0, 1}){
                            // assert(siz[u] - (i - j) * k >= 0);
                            int lessu = siz[u] - (i - j) * k;
                            lessu %= (k + 1);
                            // assert(siz[v] - j * k >= 0);
                            int lessv = siz[v] - j * k;
                            lessv %= (k + 1);
                            //如果为1则剩下的块必定为k
                            if (stau == 1 && lessu != k){
                                continue;
                            }

                            //把根节点切出去的连回来，一起算， 合法情况只有连通块大小满足条件
                            if (lessu + lessv > k) continue; //剩下的连通块太大，无法切除,不合法
                            //如果相加等于k, 即可以与根节点连通，并且根就看成已经被占用
                            f[i][lessv + lessu == k] += dp[i - j][stau] * dpv[j];
                        }

                    }
                }

                std::swap(dp, f);
                siz[u] += siz[v];
            }

            std::vector<Z> f(std::min(B, (siz[u] / k)) + 3);
            for (int i = std::min(B, (siz[u] / k)); i >= 0; i--){
                for (int j : {0, 1}){
                    int less = siz[u] - i * k;
                    less %= (k + 1);

                    f[i] += dp[i][j];
                    if (less + 1 == k){
                        f[i + 1] += dp[i][j];
                    }
                }
            }

            siz[u] += 1;
            return f;
        };

        auto res = dfs(dfs, 0, -1);
        Z ans = 0;
        for (int i = 0; i < res.size(); i++){
            if ((n - i * k) >= 0 && (n - i * k) % (k + 1) == 0){
                ans += res[i];
            }
        }
        std::cout << ans << "\n";
    }
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