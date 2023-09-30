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
	ll ans=1;
	for (int i=0; i<n; i++){
		ll a;
		std::cin>>a;
		if (ans==a){
			ans++;
		}
		if (i!=n-1){
		ans++;
			
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