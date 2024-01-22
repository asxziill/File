#include <bits/stdc++.h>

using ll = long long;

void solve(){
	ll n, k;
	std::cin >> n >> k;
	ll ans = 1;
	std::vector<ll> a(n);
	for (int i = 0; i < n; i++){
		std::cin >> a[i];
		//利用差分的思想，（减下标）变为相同的数
		a[i] -= i;
	}

	//对顶堆维护中位数
	std::multiset<ll> S, B;
	ll s = 0, b = 0;
	ll cnt = 0;

	auto norm = [&](){
		while (S.size() > (cnt + 1)/2){
			ll out = *S.rbegin();
			s -= out;
			S.extract(out);
			b += out;
			B.insert(out);
		}

		while (S.size() < (cnt + 1)/2){
			ll out = *B.begin();
			b -= out;
			B.extract(out);
			s += out;
			S.insert(out);
		}
	};

	auto add = [&](ll x){
		cnt += 1;
		if (S.empty()){
			s += x;
			S.insert(x);
		}
		else{
			ll mid = *S.rbegin();
			if (x <= mid){
				S.insert(x);
				s += x;
			}
			else{
				B.insert(x);
				b += x;
			}
		}

		norm();
	};

	auto del = [&](ll x){
		cnt -= 1;
		if (S.empty()){
			B.extract(x);
			b -= x;
		}
		else{
			ll mid = *S.rbegin();
			if (x <= mid){
				S.extract(x);
				s -= x;
			}
			else{
				B.extract(x);
				b -= x;
			}
		}

		norm();
	};

	auto get = [&]()->ll{
		assert(!S.empty());
		ll mid = *S.rbegin();
		ll res = ll(S.size()) * mid - s;
		res += b - ll(B.size()) * mid;
		return res;
	};

	for (int l = 0, r = 0; l < n; l++){
		while (r < n){
			add(a[r]);

			if (get() <= k){
				r += 1;
			}
			else{
				del(a[r]);
				break;
			}
		}

		if (get() <= k){
			ans = std::max(ans, cnt);
		}
		del(a[l]);
	}
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