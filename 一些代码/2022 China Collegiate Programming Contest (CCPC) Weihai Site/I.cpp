#include <bits/stdc++.h>

const int N=1e5+5;
const int M=1e5+5;
const int inf=0x3fffffff;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 lll;

/*
合成一个龙蛋需要 n 种精华，其中第 i 种精华需要 ai 个单
位。
有 k 种工具龙，第 j 种工具龙总共有 bj 条，且每单位时间
能产出 2^{j−1} 单位的任意一种精华
*/

/*
t数据
n,k
a
b
*/

/*
显然可以二分答案
问题为给定n个数，问现在你能有一定的2次幂来满足该数吗？
首先我们可以让让2次幂尽可能被利用，一定是最优的
然后更大的数要尽可能匹配更大的数

我们可以从大到小去匹配，如果充分利用就填充
如果有剩就填最大的

这种填法是最优的，可以方法如果将其方案改变，只会变的更劣
*/

void solve(){
	ll n, k;
	std::cin>>n>>k;
	std::vector<ll> a(n);
	std::vector<ll> b(k);
	for (int i=0; i<n; i++){
		std::cin>>a[i];
	}
	for (int i=0; i<k; i++){
		std::cin>>b[i];
	}
	lll lo=1, hi=ll(2e18)+5;
	ll ans=0;
	while (lo<hi){
		lll mid=(lo+hi)/2;
		std::priority_queue<lll> q;
		for (int i=0; i<n; i++){
			q.push(a[i]*mid);
		}
		std::vector<ll> cnt=b;
		for (int i=k-1; i>=0; i--){
			while (cnt[i]>0 && !q.empty()){
				lll d=q.top();
				q.pop();
				if (d>=(1ll<<i)){
					lll need=d/(1ll<<i);
					lll now=std::min(lll(cnt[i]), need);
					d-=now*(1ll<<i);
					cnt[i]-=now;
					if (d>0){
						q.push(d);
					}
				}
				else{
					cnt[i]--;
				}
			}
		}
		if (q.empty()){
			ans=mid;
			lo=mid+1;
		}
		else{
			hi=mid;
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