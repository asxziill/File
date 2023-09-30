#include <bits/stdc++.h>

const int N=1e5+5;
const int M=10;
const int inf=0x3fffffff;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 lll;

ll get(int x, int y){
	for (int i=1; i<=5; i++){
		if (x==i || x==M-i+1 || y==i || y==M-i+1){
			return i;
		}
	}
	return 0;
}

void solve(){
	std::vector<std::string> s(M);
	ll ans=0;
	for (int i=0; i<M; i++){
		std::cin>>s[i];
		for (int j=0; j<M; j++){
			if (s[i][j]=='X'){
				ans+=get(i+1, j+1);
			}
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