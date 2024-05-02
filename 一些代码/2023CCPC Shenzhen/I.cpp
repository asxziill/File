#include <bits/stdc++.h>

using ll = long long;

/*
$$
a^k - b^k\\
a = b + d\\
(b + d) ^ k - b^k = (C_k^0b^k + \cdots C_k^kd^k) - b^k\\
=C_k^1b^{k-1}d + \cdots C_k^kd^k=d(C_k^1b^{k-1}+ \cdots C_k^kd^{k - 1})\\
\le d^k(取第一项)\\
所以d \le n^{\frac{1}{k}}\\
注意到后面的多项式全是正数，随b,d增加而增加\\
所以可以枚举d,然后二分求根
更简单的方法之间讲d = a - b提取出来\\
=(a-b)(a^{k-1}+a^{k-2}b+\cdots+b^{k-1})\\
同上，但是后面的式子可以不用求组合数
$$
*/

constexpr ll inf = 4e18;
constexpr int N = 70;

ll C[N][N];

void init() {
  for (int i = 0; i < N; i++) {
    C[i][0] = 1;
    for (int j = 0; j < i; j++) {
      C[i][j + 1] = C[i - 1][j + 1] + C[i - 1][j];
      if (C[i][j + 1] >= inf) {
        C[i][j + 1] = inf;
      }
    }
  }
} 

ll mul(ll a, ll b) {
  if (a <= inf / b) return a * b;
  else return inf;
}

ll qpow(ll a, ll b) {
  ll res = 1;
  while (b) {
    if (b & 1) {
      res = mul(res, a);
      if (res == inf) break;
    }
    a = mul(a, a);
    b >>= 1;
  }
  return res;
}

void solve() {
  ll n, k;
  std::cin >> n >> k;
  ll lo = 1, hi = n + 1;
  ll lim = -1;
  while (lo < hi) {
      // std::cout << lo << " " << hi << std::endl;
    ll mid = (lo + hi) / 2;
    if (qpow(mid, k) >= n) {
      lim = mid;
      hi = mid;
    } else {
      lo = mid + 1;
    }
  }
  assert(lim != -1);
  // std::cout << lim << std::endl;

  //方法一
  auto get = [&](ll b, ll d) {
    ll res = 0;
    for (int i = 0; i < k; i++) {
      res += mul(mul(qpow(d, i), C[k][i + 1]), qpow(b, k - 1 - i));
      if (res >= inf) {
        res = inf;
        break;
      }
    }
    return res;
  };

  //方法二
  // auto get = [&](ll b, ll d) {
  //   ll res = 0;
  //   for (int i = 0; i < k; i++) {
  //     res += mul(qpow(b + d, i), qpow(b, k - 1 - i));
  //     if (res >= inf) {
  //       res = inf;
  //       break;
  //     }
  //   }
  //   return res;
  // };

  ll ans = 0;
  for (ll d = 1; d <= lim; d++) {
    if (n % d != 0) continue;
    ll val = n / d;
    ll lo = 1, hi = n + 1;
      if (d == 4) {

      }
    while (lo < hi) {
      ll mid = (lo + hi) / 2;

      ll tmp = get(mid, d);
      if (tmp == val) {
        ans += 1;
        break;
      } else if (tmp < val) {
        lo = mid + 1;
      } else {
        hi = mid;
      }
    }
  }
  std::cout << ans << "\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  init();
  int t;
  std::cin >> t;
  while (t--) {
    solve();
  }    
  return 0;
}