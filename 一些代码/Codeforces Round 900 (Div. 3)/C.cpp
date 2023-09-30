#include <bits/stdc++.h>

const int N=1e5+5;
const int M=1e5+5;
const int inf=0x3fffffff;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 lll;

void solve(){
	ll n, k, x;
	std::cin>>n>>k>>x;
	ll mn=k*(1+k)/2;
	ll mx=k*(n+n-k+1)/2;
	if (mn<=x && x<=mx){
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