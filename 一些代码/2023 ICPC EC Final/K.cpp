#include <bits/stdc++.h>

using ll = long long;

/*
我们先假设有一个进位，则我们只需找到尽可能多的数对 >= m - 1
然后再讨论进位的来源，如果本来的数对有>= m的则将他放到最后面即可
如果没有，再查看未匹配的数 最大的数比已经匹配的最小的数大，如果大， 则可以将其替换
如果还没有，最后检查是否能拆掉一个数对满足进位（即存在数>= m即可

匹配数对要由大到小，先将较小的数拿掉，这样会在不影响答案的情况下更容易凑出大于m的
*/


void solve() {
	ll m;
	std::cin >> m;
	std::vector<ll> a(m), b(m);
	for (int i = 0; i < m; i++) {
		std::cin >> a[i];
	}
	for (int i = 0; i < m; i++) {
		std::cin >> b[i];
	}

	//补0
	if (std::accumulate(a.begin(), a.end(), 0ll) > std::accumulate(b.begin(), b.end(), 0ll)) {
		std::swap(a, b);
	}
	a[0] += std::accumulate(b.begin(), b.end(), 0ll) - std::accumulate(a.begin(), a.end(), 0ll);

	std::map<ll, ll> cnt;
	for (int i = 0; i < m; i++) {
		if (b[i]) {
			cnt[i] = b[i];
		}
	}

	bool carry = false;
	bool up = false;

	for (int i = 0; i < m; i++) {
		if (a[i] && cnt.lower_bound(m - i) != cnt.end()) {
			up = true;
			break;
		}
	}

	ll mn = m;
	ll ans = 0;
	for (int i = m - 1; i >= 0; i--) {
		auto it = cnt.lower_bound(m - 1 - i);
		while (it != cnt.end() && a[i]) {
			ll d = std::min(a[i], it->second);
			a[i] -= d;
			it->second -= d;
			ans += d;
			mn = std::min(mn, it->first);
			if (i + it->first >= m) {
				carry = true;
			}
			if (it->second == 0) {
				it = cnt.erase(it);
			}
		} 
	}

	if (carry) {
		;
	}
	else if (!cnt.empty() && cnt.rbegin()->first > mn) {
		;
	}
	else if (up) {
		ans -= 1;
	}
	else {
		ans = 0;
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