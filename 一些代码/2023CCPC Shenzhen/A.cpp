#include <bits/stdc++.h>

using ll = long long;

//值域二分
//复杂度O(nlog n)
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  std::cin >> n;
  std::vector<int> b(n);
  std::vector<std::pair<int, int>> ans;

  for (int i = 0; i < n; i++) {
    std::cin >> b[i];
  }    

  std::vector<std::pair<int, int>> v;
  for (int i = 0; i < n; i++) {
    v.emplace_back(b[i], i + 1);
  }
  std::sort(v.begin(), v.end());

  auto solve = [&](auto self, int l, int r)->void {
    if (r - l <= 1) return;
    int mid = (l + r) / 2;
    std::pair<int, int> tmp = {mid, -1};
    auto p = std::lower_bound(v.begin(), v.end(), tmp) - v.begin();
    int cnt = 0;
    for (int i = p; i < n; i++) {
      if (v[i].first >= mid && v[i].first < r) {
        ans.emplace_back(2, v[i].second);
        cnt++;
      }
    }
    if (cnt) {
      for (int i = l + 1; i < mid; i++) {
        ans.emplace_back(1, i);
      }
    }

    self(self, l, mid);
    self(self, mid, r);
    
  };
  solve(solve, 0, n + 1);
  std::cout << ans.size() << "\n";
  for (auto &[a, b] : ans) {
    std::cout << a << " " << b << "\n";
  }


  return 0;
}