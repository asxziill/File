#include <bits/stdc++.h>

const int N=1e5+5;
const int M=1e5+5;
const int inf=0x3fffffff;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 lll;

void solve(){
	ll n, k;
	std::cin>>n>>k;
	std::vector<ll> a(n), h(n);
	for (int i=0; i<n; i++){
		std::cin>>a[i];
	}
	for (int i=0; i<n; i++){
		std::cin>>h[i];
	}
	int l=0, r=-1;
	int ans=0;
	ll now=0;
	for (;l<n; ){
		while (r<l){
			r++;
			now+=a[r];
		}
		while (r<n-1 && (h[r]%h[r+1])==0 && now+a[r+1]<=k){
			r++;
			now+=a[r];
		}
		if (now<=k){
			ans=std::max(ans, r-l+1);
		}
		now-=a[l];
		l++;
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