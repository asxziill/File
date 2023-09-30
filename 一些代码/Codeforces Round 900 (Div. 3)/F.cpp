#include <bits/stdc++.h>

const int N=1e5+5;
const int M=1e5+5;
const int inf=0x3fffffff;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 lll;

std::vector<int> minp, primes;

void sieve(int n) {
    minp.assign(n + 1, 0);
    primes.clear();
    
    for (int i = 2; i <= n; i++) {
        if (minp[i] == 0) {
            minp[i] = i;
            primes.push_back(i);
        }
        
        for (auto p : primes) {
            if (i * p > n) {
                break;
            }
            minp[i * p] = p;
            if (p == minp[i]) {
                break;
            }
        }
    }
}
const int V=int(1e6);

void solve(){
	ll n, q;
	std::cin>>n>>q;
	std::map<ll, ll> np;
	while (n!=1){
		np[minp[n]]++;
		n/=minp[n];
	}
	std::map<ll, ll> pcnt=np;
	while (q--){
		int k;
		std::cin>>k;
		if (k==2){
			pcnt=np;
		}
		else{
			ll x;
			std::cin>>x;
			while (x!=1){
				pcnt[minp[x]]++;
				x/=minp[x];
			}
			ll d=1;
			for (auto [p, c]:pcnt){
				d*=(c+1);
			}
			int ok=1;
			for (ll i=2; i*i<=d; i++){
				if (d%i==0){
					if (!pcnt.count(i)){
						ok=0;
						break;
					}
					int len=0;
					while (d%i==0){
						len++;
						d/=i;
					}
					if (pcnt[i]<len){
						ok=0;
						break;
					}
				}
			}

			if (ok){
				if (d!=1){
					if (!pcnt.count(d) || pcnt[d]<1){
						std::cout<<"NO\n";
						continue;
					}
				}
				std::cout<<"YES\n";
			}
			else{
				std::cout<<"NO\n";
			}
		}
	}

	std::cout<<"\n";
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    sieve(V);
 	int t;
 	std::cin>>t;
 	while (t--){
 		solve();
 	}   
    return 0;
}