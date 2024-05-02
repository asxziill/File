#include <bits/stdc++.h>

using ll = long long;

/*
首先后手选择模仿，先手必不可能获胜
然后后手必胜，则对于任意一个点，能到达的叶子节点编号，存在同一深度的节点的子树 能到达所有胜利的叶子
所以，同一深度的节点的获胜关系 一定会组成一个环，否则存在一个节点，每个节点能获胜它，先手走该节点就为平局
再根据模的性质有，同一深度的节点，每个点能到达的叶子点集合满足
集合大小相同，集合内的点的编号为{a, a + x, a + 2x..} (x是当前深度节点的个数)
又因为所有节点并起来一定是m
所以每个点集合可以表示为 叶子节点模x相同的值
如果没有上面的性质，则平局

所以后手获胜的树要有这个性质
则它必然会是一个多叉树，每次分叉，每个节点的度数是相同的
只要判断树是不是这个形式的即可

因为每次合并集合数的变化至少/2所以 最多只有log n层需要检测
检测每次合并时 叶子是否满足上面的形式即可

又因为如果确定了一层的模关系，则可以只可以将每个子树看成一个叶子
(这样对一个子树只用关注能到达的子树编号最小的叶子即可，这样就能用一个数字代表整个集合)
(当然用dfs序也可以快速获得子树能到达的叶子信息)
*/

void solve() {
  int n, m;
  std::cin >> n >> m;
  std::vector<std::vector<int>> t(n);
  for (int i = 0; i < n - 1; i++) {
    int u, v;
    std::cin >> u >> v;
    u--, v--;
    t[u].push_back(v);
    t[v].push_back(u);
  }

  std::vector<int> deg(n);
  std::vector<int> mn(n, n);
  std::vector<std::vector<std::pair<int, int>>> q(n);
  std::vector<int> vis(n);
  int ok = 1;
  auto dfs = [&](auto self, int u, int p)->void {
    int siz = 0;
    for (int v : t[u]) {
      if (v == p) continue;
      deg[v] = deg[u] + 1;
      self(self, v, u);
      mn[u] = std::min(mn[u], mn[v]);
      siz++;
    }
    if (siz == 0) {
      mn[u] = u;
    }
    q[deg[u]].emplace_back(mn[u], u);
    if (siz > 1) {
      vis[deg[u]] = 1;
    }
  };
  dfs(dfs, n - 1, -1);
  for (int i = 0; i < n; i++) {
    if (!vis[i]) continue;
    auto &a = q[i];
    std::sort(a.begin(), a.end());
    int siz = a.size();
    // std::cout << i << " :\n";
    // for (auto x : a) {
    //   std::cout << x.first << " ";
    // }
    // std::cout << "\n";

    std::set<int> set;
    for (int j = 0; j < siz; j++) {
      if (a[j].first != j) {
        std::cout << "Tie\n";
        return;
      }

      std::vector<int> nxt;
      int u = a[j].second;
      for (int v : t[u]) {
        if (deg[v] == deg[u] + 1) {
          nxt.push_back(mn[v]);
        }
      }

      set.insert(nxt.size());
      if (set.size() > 1) {
        std::cout << "Tie\n";
        return;
      }
      std::sort(nxt.begin(), nxt.end());
      // std::cout << j << " J\n";
      // for (auto x : nxt) {
      //   std::cout << x << " ";
      // }
      // std::cout <<"\n";
      for (int k = 0; k < nxt.size(); k++) {
        if (nxt[k] != j + siz * k) {
          std::cout << "Tie\n";
          return;
        }
      }
    }
  }
  std::cout << "Doddle\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t;
  std::cin >> t;
  while (t--) {
    solve();
  }    
  return 0;
}