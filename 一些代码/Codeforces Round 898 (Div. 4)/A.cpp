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
	if (s=="abc"){
		std::cout<<"YES\n";
		return;
	}
	for (int i=0; i<3; i++){
		for (int j=i+1; j<3; j++){
			std::swap(s[i], s[j]);
			if (s=="abc"){
				std::cout<<"YES\n";
				return;
			}
			std::swap(s[i], s[j]);

		}
	}
	std::cout<<"NO\n";
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