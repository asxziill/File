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
	int cnt=0;
	for (int i=0; i<n; i++){
		int a;
		std::cin>>a;
		cnt+=(a==k);
	}
	if (cnt){
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