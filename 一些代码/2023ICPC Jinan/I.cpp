#include <bits/stdc++.h>

using ll = long long;

void solve(){
	int n;
	std::cin >> n;
	std::vector<int> a(n);
	for (int i = 0; i < n; i++){
		std::cin >> a[i];
	}

	auto b = a;
	std::sort(b.begin(), b.end());
	std::vector<std::pair<int, int>> ans;
	int l = 0;
	while (l < n){
		//对每个数选最远的比它小的数，必然能至少两个数排好
		while (l < n && a[l] == b[l]) l++;
		if (l == n) break;

		int ansl = l;
		int ansr = l + 1;
		for (int i = l + 1; i < n; i++){
			if (a[ansl] > a[i]){
				ansr = i;
			}
		}
		ans.emplace_back(ansl + 1, ansr + 1);
		auto c = std::vector(a.begin() + ansl, a.begin() + ansr + 1);
		std::sort(c.begin(), c.end());
		for (int i = ansl; i <= ansr; i++){
			a[i] = c[i - ansl];
		}
	}

	std::cout << ans.size() << "\n";
	for (auto [l, r] : ans){
		std::cout << l << " " << r << "\n";
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