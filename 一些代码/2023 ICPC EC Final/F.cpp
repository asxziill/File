#include <bits/stdc++.h>

using ll = long long;

/*
首先发现要求的排列满足 ： 在1234.。p的基础上 交换两个相邻的数（交换区域为2，不能相交
发现将排列变成123.. 操作数为逆序对的数量
而然后用DP解决是否交换该数即可
*/

template <typename T>
struct Fenwick {
    int n;
    std::vector<T> a;
    
    Fenwick(int n = 0) {
        init(n);
    }
    
    void init(int n) {
        this->n = n;
        a.assign(n, T());
    }
    
    void add(int x, T v) {
        for (int i = x + 1; i <= n; i += i & -i) {
            a[i - 1] += v;
        }
    }
    
    T sum(int x) {
        auto ans = T();
        for (int i = x; i > 0; i -= i & -i) {
            ans += a[i - 1];
        }
        return ans;
    }
    
    T rangeSum(int l, int r) {
        return sum(r) - sum(l);
    }
    
    int kth(T k) {
        int x = 0;
        for (int i = 1 << std::__lg(n); i; i /= 2) {
            if (x + i <= n && k >= a[x + i - 1]) {
                x += i;
                k -= a[x - 1];
            }
        }
        return x;
    }
};

void solve() {
	int n;
	std::cin >> n;
	std::vector<int> a(n);
	std::vector<int> pos(n);
	for (int i = 0; i < n; i++) {
		std::cin >> a[i];
		a[i]--;
		pos[a[i]] = i;
	}

	ll ans = 0;
	Fenwick<ll> fen(n);
	for (int i = n - 1; i >= 0; i--) {
		ans += fen.sum(a[i]);
		fen.add(a[i], 1);
	}

	std::vector dp(n + 1, std::vector<int>(2, n + 1));
	dp[0][0] = 0, dp[0][1] = 0;
	int mn = 0;
	for (int i = 0; i < n; i++) {
		int v = 0;
		if (i) {
			v = pos[i] < pos[i - 1] ? -1 : 1;
		}

		dp[i + 1][1] = dp[i][0] + v;
		dp[i + 1][0] = std::min(dp[i][0], dp[i][1]);
		mn = std::min({mn, dp[i + 1][0], dp[i + 1][1]});
	}
	ans += mn;
	std::cout << ans << "\n";
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--) {
    	solve();
    }
    return 0;
}