#include <bits/stdc++.h>

const int N=1e5+5;
const int M=1e5+5;
const int inf=0x3fffffff;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 lll;

void solve(){
	int n, k;
	std::cin>>n>>k;
	std::string s;
	std::cin>>s;
	int ans=0;
	for (int l=0, r=0; l<n; l=r){
		if (s[l]=='W'){
			r++;
			continue;
		}
		while (r<n && s[r]=='B'){
			r++;
		}
		int cnt=r-l;
		int d=(cnt+k-1)/k;
		ans+=d;
		r=l+d*k;
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