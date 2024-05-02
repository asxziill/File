#include <bits/stdc++.h>

using ll = long long;

//首先度数不能有大于4的，等于4的不能为根
//然后去掉环上的边（变成树，统计答案即可
int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int n;
  std::cin >> n;
  std::vector<std::vector<int>> t(n);
  std::vector<int> deg(n), top(n);
  for (int i = 0; i < n; i++) {
    int u, v;
    std::cin >> u >> v;
    u--, v--;
    t[u].push_back(v);
    t[v].push_back(u);
    deg[u]++;
    deg[v]++;

    top[u]++;
    top[v]++;
  }    

  std::queue<int> q;
  std::vector<int> vis(n);
  for (int i = 0; i < n; i++) {
    if (top[i] == 1) q.push(i);
  }
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    vis[u] = 1;
    for (int v : t[u]) {
      top[v]--;
      if (top[v] == 1) {
        q.push(v);
      }
    }
  }

  std::vector<int> cir;
  for (int i = 0; i < n; i++) {
    if (!vis[i]) {
      int j = i;
      while (true) {
        cir.push_back(j);
        vis[j] = 1;

        int nxt = -1;
        for (int v : t[j]) {
          if (!vis[v]) {
            nxt = v;
            break;
          }
        }

        if (nxt == -1) break;
        j = nxt;
      }
      break;
    }
  }
  int m = cir.size();
  // for (auto x : cir) std::cout << x << " ";

  ll c1 = 0, c2 = 0, big = 0;
  auto add = [&](int x) {
    if (deg[x] < 4) {
      c1++;
    } else if (deg[x] == 4) {
      c2++;
    } else {
      big++;
    }
  };
  auto sub = [&](int x) {
    if (deg[x] < 4) {
      c1--;
    } else if (deg[x] == 4) {
      c2--;
    } else {
      big--;
    }
  };

  for (int i = 0; i < n; i++) {
    add(i);
  }

  ll ans = 0;
  for (int i = 0; i < m; i++) {
    int u = cir[i], v = cir[(i + 1) % m];

    sub(u);
    deg[u]--;
    add(u);
    sub(v);
    deg[v]--;
    add(v);

    assert(c1 + c2 + big == n);
    if (big == 0) {
      // std::cout << c1 << "\n";
      ans += c1;
    }

    sub(u);
    deg[u]++;
    add(u);
    sub(v);
    deg[v]++;
    add(v);
  }
  std::cout << ans << "\n";
  return 0;
}