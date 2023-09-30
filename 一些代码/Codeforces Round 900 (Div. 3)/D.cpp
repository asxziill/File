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
	s=" "+s;
	std::vector<int> l(k), r(k);
	std::vector<int> d(n+5);
	for (int i=0; i<k; i++){
		std::cin>>l[i];
	}
	for (int i=0; i<k; i++){
		std::cin>>r[i];
	}
	int q;
	std::cin>>q;
	while (q--){
		int x;
		std::cin>>x;
		int p=std::lower_bound(r.begin(), r.end(), x)-r.begin();
		int mn=std::min(x, l[p]+r[p]-x);
		int mx=std::max(x, l[p]+r[p]-x);
		d[mn]^=1, d[mx]^=1;
	}
	// std::cout<<d[0]<<" ";
	for (int i=1; i<=n; i++){
		d[i]^=d[i-1];
		// std::cout<<d[i]<<" ";
	}
	// std::cout<<"D"<<std::endl;
	for (int i=0; i<k; i++){
		for (int j=l[i]; j<=r[i]; j++){
			if (d[j] && r[i]+l[i]-j>=j){
				std::swap(s[j], s[r[i]+l[i]-j]);
			}
		}
	}
	for (int i=1; i<=n; i++){
		std::cout<<s[i];
	}
	std::cout<<"\n";
	// std::cout<<s<<"\n";
	// std::cout<<std::endl;
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