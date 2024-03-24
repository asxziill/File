#include <bits/stdc++.h>

using ll = long long;

/*
所有不同颜色组成一个完全图
特别的如果d==1 则所有点可以组成完全图
d==2时，则是完全图上将相同颜色的点的连边去掉即可
*/

ll get(ll n) {
	return n * (n - 1) / 2;
}

void solve() {
	ll n, d;
	std::cin >> n >> d;
	ll ans = 0;
	ll sum = 0;

	std::vector<ll> a(n);
	for (int i = 0; i < n; i++) {
		std::cin >> a[i];
		sum += a[i];
	}
	std::sort(a.begin(), a.end());

	if (d == 1) {
		ans = get(sum);
	}
	else if (d == 2) {
		ans = get(sum);
		for (int i = 0; i < n; i++) {
			ans -= get(a[i]);
		}
	}
	else {
		ll last = 0;
		for (int i = 0; i < n; i++) {
			ll v = a[i] - last;
			ans += v * get(n - i);
			last = a[i];
		}
	}
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