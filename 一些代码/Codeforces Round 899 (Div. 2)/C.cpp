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
	std::vector<ll> a(n+1);
	ll ans=0;
	int pos=n+1;
	for (int i=1; i<=n; i++){
		std::cin>>a[i];
		if (i>=pos){
			ans=std::max(ans, ans+a[i]);
		}
		else if (i%2 && a[i]>=0){
			pos=i;
			ans+=a[i];
		}
	}
	ll res=0;
	ll sum=0;
	for (int i=pos-1; i>0; i--){
		if (i%2){
			res=std::max(res, sum+a[i]);
		}
		else{
			res=std::max(res, sum);
		}
		if (a[i]>=0){
			sum+=a[i];
		}

	}
	ans+=res;
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