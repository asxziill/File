#include <bits/stdc++.h>

const int N=1e5+5;
const int M=1e5+5;
const int inf=0x3fffffff;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 lll;

void solve(){
	int n;
	std::cin>>n;
	std::vector<ll> val(n);
	std::vector<ll> f(n);
	std::vector<ll> ans(n);
	std::vector<std::vector<int>> t(n);
	for (int i=0; i<n; i++){
		std::cin>>val[i];
	}
	for (int i=1; i<n; i++){
		int u, v;
		std::cin>>u>>v;
		u--, v--;
		t[u].push_back(v);
		t[v].push_back(u);
	}
	std::vector<int> siz(n);
	auto dfs1=[&](auto self, int u, int fa)->void{
		siz[u]=1;
		for (int v:t[u]){
			if (v==fa) continue;
			self(self, v, u);
			siz[u]+=siz[v];
			f[u]+=f[v]+(val[u]^val[v])*siz[v];
		}
	};
	dfs1(dfs1, 0, -1);
	auto dfs2=[&](auto self, int u, int fa)->void{
		for (int v:t[u]){
			if (v==fa) continue;
			ll tmp=ans[u]-(f[v]+(val[u]^val[v])*siz[v]);
			ans[v]=f[v]+tmp+(val[u]^val[v])*(n-siz[v]);
			self(self, v, u);
		}
	};
	ans[0]=f[0];
	dfs2(dfs2, 0, -1);
	for (int i=0; i<n; i++){
		std::cout<<ans[i]<<" \n"[i==n-1];
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