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
	std::vector<std::vector<int>> s(n);
	std::set<int> set;
	for (int i=0; i<n; i++){
		int k;
		std::cin>>k;
		s[i].resize(k);
		for (int j=0; j<k; j++){
			std::cin>>s[i][j];
			set.insert(s[i][j]);
		}
	}
	int mx=*set.rbegin();
	std::vector<int> cnt(mx+1, 0);
	int ans=0;
	for (int i:set){
		for (int j=0; j<n; j++){
			int ok=1;
			for (int x:s[j]){
				if (x==i){
					ok=0;
					break;
				}
			}
			if (ok){
				for (int x:s[j]){
					cnt[x]++;
				}
			}
		}
		int res=0;
		for (int j=1; j<=mx; j++){
			if (cnt[j]){
				res++;
				cnt[j]=0;
			}
		}
		ans=std::max(ans, res);
	}
	std::cout<<ans<<"\n";
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