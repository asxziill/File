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
	std::set<ll> set;
	ll mul=1;
	int cnt=0;
	for (int i=0; i<n; i++){
		ll a;
		std::cin>>a;
		if (a==0){
			cnt++;
			continue;
		}
		mul*=a;
		set.insert(a);
	}
	if (cnt>=2){
		std::cout<<0<<"\n";
	}
	else if (cnt==1){
		std::cout<<mul<<"\n";
	}
	else{
		mul/=*set.begin();
		mul*=(*set.begin()+1);
		std::cout<<mul<<"\n";
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