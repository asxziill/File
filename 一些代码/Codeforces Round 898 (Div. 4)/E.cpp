#include <bits/stdc++.h>

const int N=1e5+5;
const int M=1e5+5;
const int inf=0x3fffffff;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 lll;

void solve(){
	ll n, x;
	std::cin>>n>>x;
	std::vector<ll> a(n);
	for (int i=0; i<n; i++){
		std::cin>>a[i];
	}
	ll lo=1, hi=ll(2e18);
	ll ans=1;
	while (lo<hi){
		ll mid=(lo+hi)/2;
		lll sum=0;
		for (int i=0; i<n; i++){
			sum+=std::max(lll(mid-a[i]), lll(0));
		}
		if (sum<=x){
			ans=mid;
			lo=mid+1;
		}
		else{
			hi=mid;
		}
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