#include <bits/stdc++.h>

using ll = long long;

ll get(ll x){
	ll res = 0;
	while (x){
		res = std::max(res, x % 10);
		x /= 10;
	}
	return res;
}

void solve(){
	ll la, ra, lb, rb;
	std::cin >> la >> ra >> lb >> rb;
	ll l = la + lb;
	ll r = ra + rb;
	if (r - l >= 10){
		std::cout << 9 << "\n";
	}
	else{
		ll ans = get(l);
		for (ll i = l + 1; i <= r; i++){
			ans = std::max(ans, get(i));
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