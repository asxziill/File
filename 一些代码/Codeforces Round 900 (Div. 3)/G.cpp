#include <bits/stdc++.h>

const int N=1e5+5;
const int M=32;
const int inf=0x3fffffff;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 lll;

void solve(){
	int n;
	std::cin>>n;
	std::vector<int> val(n+1);
	for (int i=1; i<=n; i++){
		std::cin>>val[i];
	}
	std::vector<std::vector<int>> t(n+1);
	for (int i=0; i<n-1; i++){
		int u, v;
		std::cin>>u>>v;
		t[u].push_back(v);
		t[v].push_back(u);
	}
	int logn=std::__lg(n);
	std::vector fa(logn+1, std::vector<int>(n+1));
	std::vector cnt(M, std::vector<int>(n+1));
	std::vector<int> dep(n+1);
	auto dfs=[&](auto self, int u)->void{
		for (int i=0; i<logn; i++){
			fa[i+1][u]=fa[i][fa[i][u]];
		}
		for (int i=0; i<M; i++){
			cnt[i][u]+=(val[u]>>i)&1;
		}
		for (int v:t[u]){
			if (v==fa[0][u]){
				continue;
			}
			fa[0][v]=u;
			dep[v]=dep[u]+1;
			for (int i=0; i<M; i++){
				cnt[i][v]+=cnt[i][u];
			}
			self(self, v);
		}
	};
	dep[1]=1;
	dfs(dfs, 1);
	auto LCA=[&](int x, int y){
		if (dep[x]<dep[y]){
			std::swap(x, y);
		}
		for (int i=logn; i>=0; i--){
			if (dep[fa[i][x]]>=dep[y]){
				x=fa[i][x];
			}
		}
		if (x==y) return x;
		for (int i=logn; i>=0; i--){
			if (fa[i][x]!=fa[i][y]){
				x=fa[i][x];
				y=fa[i][y];
			}
		}
		return fa[0][x];
	};
	int q;
	std::cin>>q;
	while (q--){
		int x, y;
		std::cin>>x>>y;
		int lca=LCA(x, y);
		int dis=dep[x]+dep[y]-2*dep[lca]+1;
		//计算从x开始,xy路径上第一个影响值的位置
		auto get=[&](int x, int y, int pos){
			int sum=(cnt[pos][x]-cnt[pos][lca]+cnt[pos][y]-cnt[pos][fa[0][lca]]);
			if (sum==0){
				return dis;
			}
			int res=0;
			for (int i=logn; i>=0; i--){
				if (dep[fa[i][x]]>=dep[lca] && cnt[pos][x]==cnt[pos][fa[i][x]]){
					x=fa[i][x];
					res+=(1<<i);
				}
			}
			if ((val[x]>>pos)&1){
				return res;
			}
			res=dis-1;
			for (int i=logn; i>=0; i--){
				if (dep[fa[i][y]]>=dep[x] && cnt[pos][x]<cnt[pos][fa[i][y]] ){
					res-=(1<<i);
					y=fa[i][y];
				}
			}
			return res;
		};
		std::vector<std::pair<int, int>> pos;
		for (int i=0; i<M; i++){
			pos.push_back({get(x, y, i), 1});
			// if (i<=4){
			// 	std::cout<<"\n"<<get(x, y, i)<<" "<<dis<<" "<<get(y, x, i)<<"ERR\n";

			// }
			pos.push_back({dis-get(y, x, i), -1});
		}
		std::sort(pos.begin(), pos.end());
		int la=0;
		int ans=0;
		int now=M;
		//没有会在开头就减掉
		for (auto [p, v]:pos){
			if (p>la){
				ans=std::max(ans, now);
			}
			la=p;
			now+=v;
		}
		if (la!=dis){
			ans=std::max(ans, now);
		}
		std::cout<<ans<<" \n"[q==0];

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