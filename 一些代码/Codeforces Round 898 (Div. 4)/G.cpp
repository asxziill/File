#include <bits/stdc++.h>

const int N=1e5+5;
const int M=1e5+5;
const int inf=0x3fffffff;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 lll;

void solve(){
	std::string s;
	std::cin>>s;
	int n=s.size();
	ll ans=0;
	std::set<ll> set;
	int ok=0;
	for (int l=0, r=0; l<n; l=r){
		if (s[l]=='B'){
			while (r<n && s[r]=='B'){
				r++;
			}
			if (r-l>1){
				ok=1;
			}
			continue;
		}
		while (r<n && s[r]=='A'){
			r++;
		}
		int cnt=r-l;
		ans+=cnt;
		set.insert(r-l);
	}
	if (s[0]=='A' && s.back()=='A' && (!ok)){
		ans-=*set.begin();
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