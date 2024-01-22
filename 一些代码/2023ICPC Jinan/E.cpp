#include <bits/stdc++.h>

using ll = long long;

template<class T>
struct MaxFlow {
    struct _Edge {
        int to;
        T cap;
        _Edge(int to, T cap) : to(to), cap(cap) {}
    };
     
    int n;
    std::vector<_Edge> e;
    std::vector<std::vector<int>> g;
    std::vector<int> cur, h;
     
    MaxFlow() {}
    MaxFlow(int n) {
        init(n);
    }
     
    void init(int n) {
        this->n = n;
        e.clear();
        g.assign(n, {});
        cur.resize(n);
        h.resize(n);
    }
     
    bool bfs(int s, int t) {
        h.assign(n, -1);
        std::queue<int> que;
        h[s] = 0;
        que.push(s);
        while (!que.empty()) {
            const int u = que.front();
            que.pop();
            for (int i : g[u]) {
                auto [v, c] = e[i];
                if (c > 0 && h[v] == -1) {
                    h[v] = h[u] + 1;
                    if (v == t) {
                        return true;
                    }
                    que.push(v);
                }
            }
        }
        return false;
    }
     
    T dfs(int u, int t, T f) {
        if (u == t) {
            return f;
        }
        auto r = f;
        for (int &i = cur[u]; i < int(g[u].size()); ++i) {
            const int j = g[u][i];
            auto [v, c] = e[j];
            if (c > 0 && h[v] == h[u] + 1) {
                auto a = dfs(v, t, std::min(r, c));
                e[j].cap -= a;
                e[j ^ 1].cap += a;
                r -= a;
                if (r == 0) {
                    return f;
                }
            }
        }
        return f - r;
    }
    void addEdge(int u, int v, T c) {
        g[u].push_back(e.size());
        e.emplace_back(v, c);
        g[v].push_back(e.size());
        e.emplace_back(u, 0);
    }
    T flow(int s, int t) {
        T ans = 0;
        while (bfs(s, t)) {
            cur.assign(n, 0);
            ans += dfs(s, t, std::numeric_limits<T>::max());
        }
        return ans;
    }
     
    std::vector<bool> minCut() {
        std::vector<bool> c(n);
        for (int i = 0; i < n; i++) {
            c[i] = (h[i] != -1);
        }
        return c;
    }
     
    struct Edge {
        int from;
        int to;
        T cap;
        T flow;
    };
    std::vector<Edge> edges() {
        std::vector<Edge> a;
        for (int i = 0; i < e.size(); i += 2) {
            Edge x;
            x.from = e[i + 1].to;
            x.to = e[i].to;
            x.cap = e[i].cap + e[i + 1].cap;
            x.flow = e[i + 1].cap;
            a.push_back(x);
        }
        return a;
    }
};

void solve(){
	int n, m;
	std::cin >> n >> m;
	MaxFlow<int> g(2 * n + 2);
	int s = 2 * n, t = s + 1;
	for (int i = 0; i < n; i++){
		g.addEdge(s, i, 1);
		g.addEdge(i + n, t, 1);
	}

	while (m--){
		int u, v;
		std::cin >> u >> v;
		u--, v--;
		g.addEdge(u, v + n, 1);
	}

    g.flow(s, t);
    ll scnt = 0, tcnt = 0;

    std::vector<int> vis(2 * n + 2);
    //根据残留网络
    //源s可到达的点
    auto dfss = [&](auto self, int u)->void{
        if (vis[u]) return;
        if (u < n) scnt += 1;
        vis[u] = 1;
        for (auto i : g.g[u]){
            auto [v, c] = g.e[i];
            if (c > 0 && !vis[v]){
                self(self, v);
            }
        }
    };
    dfss(dfss, s);

    vis.assign(2 * n + 2, 0);
    auto dfst = [&](auto self, int u)->void{
        if (vis[u]) return;
        if (u >= n && u < s) tcnt += 1;
        vis[u] = 1;
        for (auto i : g.g[u]){
            auto [v, _] = g.e[i];
            i ^= 1;
            auto [__, c] = g.e[i];
            if (c > 0 && !vis[v]){
                self(self, v);
            }
        }
    };
    dfst(dfst, t);

	ll ans = scnt * tcnt;
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