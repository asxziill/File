#include <bits/stdc++.h>

const int N=1e5+5;
const int M=1e5+5;
const int inf=0x3fffffff;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 lll;

void solve(){
	int n, a, b;
	std::cin>>n>>a>>b;

	a--,  b--;
	std::vector<std::vector<int>> adj(n);
	std::vector<int> deg(n);
	for (int i=0; i<n; i++){
		int u, v;
		std::cin>>u>>v;
		u--, v--;
		deg[u]++, deg[v]++;
		adj[u].push_back(v);
		adj[v].push_back(u);
	}
	if (a==b){
		std::cout<<"NO\n";
		return;
	}
	std::queue<int> q;
	std::vector<int> vis(n);
	for (int i=0; i<n; i++){
		if (deg[i]==1){
			q.push(i);
			vis[i]=1;
		}
	}
	while (!q.empty()){
		int u=q.front();
		q.pop();
		for (int v:adj[u]){
			deg[v]--;
			if (deg[v]==1){
				q.push(v);
				vis[v]=1;
			}
		}
	}
	if (!vis[b]){
		std::cout<<"YES\n";
		return;
	}
	std::vector<int> cvis(n);
	std::vector<int> cir;
	for (int i=0; i<n; i++){
		if (!vis[i]){
			int j=i;
			while (!cvis[j]){
				cvis[j]=1;
				cir.push_back(j);
				for (int v:adj[j]){
					if (!cvis[v] && !vis[v]){
						j=v;
						break;
					}
				}
			}
		}
	}
	int m=cir.size();
	int disb, disa;
	int isa, isb;
	std::function<void(int, int, int)> dfs=[&](int u, int f, int dep){
		if (u==b){
			disb=dep;
			isb=1;
		}
		if (u==a){
			disa=dep;
			isa=1;
		}

		for (int v:adj[u]){
			if (v==f || !vis[v]){
				continue;
			}
			dfs(v, u, dep+1);
		}
	};
	int pa, pb;
	for (int i=0; i<m; i++){
		isa=0, isb=0;
		dfs(cir[i], -1, 0);
		if (isa){
			pa=i;
		}
		if (isb){
			pb=i;
		}
	}
	int d=std::abs(pa-pb);
	int tmp=std::min(d, m-d);
	if (disb<disa+tmp){
		std::cout<<"YES\n";
	}
	else{
		std::cout<<"NO\n";
	}
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
 	int t;
 	std::cin>>t;
 	while (t--){
 		solve();
 	}   
    return 0;
}