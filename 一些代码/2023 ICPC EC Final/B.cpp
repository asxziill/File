#include <bits/stdc++.h>

using ll = long long;

//倒着来就好了

std::vector<std::string> t = {"I", "II", "III", "IV", "V", "VI", "VII", "VIII"};
std::vector<int> tp = {7, 2, 6, 1, 3, 5, 0, 4};

void solve() {
	std::string s;
	std::cin >> s;

	std::string ans;
	int n = s.size();
	for (int r = n; r;) {
		for (int j = 0; j < 8; j++) {
			int p = tp[j];
			auto x = t[p];
			int l = r - t[p].size();
			if (l < 0) continue;
			auto y = s.substr(l, t[p].size());
			if (x == y) {
				r = l;
				ans += '0' + p + 1;
				break;
			}
		}
	}
	std::reverse(ans.begin(), ans.end());
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