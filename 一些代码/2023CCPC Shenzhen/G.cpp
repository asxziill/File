#include <bits/stdc++.h>

using ll = long long;
using ull = unsigned long long;
std::mt19937_64 rng(std::chrono::steady_clock::now().time_since_epoch().count());
const int N = 2;
const ull X[N] = {rng() % 100000 + 131, 13331};

//经典的哈希+二分 模糊匹配
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n, q, m, k;
  std::cin >> n >> q >> m >> k;

  std::vector<std::array<ull, N>> p(m + 1, {1, 1});
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < N; j++) {
      p[i + 1][j] = p[i][j] * X[j];
    }
  }

  std::string s;
  std::vector h(n, std::vector<std::array<ull, N>>(m + 1, {0, 0}));

  for (int i = 0; i < n; i++) {
    std::cin >> s;
    for (int j = 0; j < m; j++) {
      for (int x = 0; x < N; x++) {
        h[i][j + 1][x] = h[i][j][x] * X[x] + (s[j] - 'a');
      }
    }
  }

  auto get = [&](int l, int r, std::vector<std::array<ull, N>> &h) {
    std::array<ull, N> res;
    for (int i = 0; i < N; i++) {
      res[i] = h[r][i] - h[l][i] * p[r - l][i];
    }
    return res;
  };

  // std::cout << get(1, 2, h[0])[0] << "\n";
  while (q--) {
    std::cin >> s;
    std::vector<std::array<ull, N>> th(m + 1);
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < N; j++) {
        th[i + 1][j] = th[i][j] * X[j] + (s[i] - 'a');
      }
    }

    int ans = 0;
    for (int i = 0; i < n; i++) {
      int l = 0;
      for (int j = 0; j <= k; j++) {
        if (l >= m) break;
        int lo = l, hi = m + 1;  
        int anr = l;
        while (lo < hi) {
          int mid = (lo + hi) / 2;

          if (get(l, mid, th) == get(l, mid, h[i])) {
            anr = mid;
            lo = mid + 1;
          } else {
            hi = mid;
          }
        }
        if (j < k) {
          l = anr + 1;
        } else {
          l = anr;
        }
      }
      if (l >= m) ans += 1;
    }
    std::cout << ans << "\n";
  }
  return 0;
}