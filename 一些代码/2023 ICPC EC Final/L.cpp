#include <bits/stdc++.h>

using ll = long long;

/*
首先发现10->11->100 我们就可以将这个看成基本操作
如果全1，对每个1有11->100->10
所以就是可以a -> 和b等长的全1串即可
删1 左边1->100 然后变成10
删0 和左边的1结合成11
将全1 变成100000..删0 将a变成10
这里发现如果a或b长度为1则不能操作
*/


void solve() {
	std::string a, b;
	std::cin >> a >> b;
	if (a == b) {
		std::cout << 0 << "\n";
		return;
	}

	if (a.size() == 1 || b.size() == 1) {
		std::cout << -1 << "\n";
		return;
	}

	std::vector<std::pair<int, int>> ans;
	for (int i = 1; i < a.size(); i++) {
		if (a[i] == '0') {
			ans.emplace_back(i, i + 1);
			a[i] = '1';
		}
	}

	int n = a.size();
	for (int i = a.size() - 1; i; i--) {
		ans.emplace_back(i, i + 1);
		n += 1;
		if (n >= 110) {
			ans.emplace_back(i + 1, n);
			n = i + 1;
		}
	}
	if (n > 2) {
		ans.emplace_back(2, n);
	}
	//10
	n = 2;

	while (n < b.size()) {
		ans.emplace_back(1, 2);
		ans.emplace_back(1, 2);
		n++;
	}
	for (int i = 2; i <= n; i++) {
		ans.emplace_back(i - 1, i);
	}

	for (int i = b.size() - 1; i; i--) {
		if (b[i] == '0') {
			ans.emplace_back(i, i + 1);
			ans.emplace_back(i + 1, i + 2);
		}
	}

	std::cout << ans.size() << "\n";
	for (auto &[l, r] : ans) {
		std::cout << l << " " << r << "\n";
	}
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