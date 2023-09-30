#include <bits/stdc++.h>

const int N=1e5+5;
const int M=1e5+5;
const int inf=0x3fffffff;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 lll;
/*
给n个数和k限制：数x最多出现y次
每次操作选一个数-1，不能操作输(不能出现负数)
*/

/*
t数据
n,k
a数
xy限制
Pico先手
*/

/*
显然每个数都能操作到限制为0，无论顺序（注意0是有堆叠的）
所以总操作数就能得到结果
每个数的贡献为离最近限制为0的距离
奇先手
*/

void solve(){
	int n, k;
	std::cin>>n>>k;
	std::vector<ll> a(n);
	for (int i=0; i<n; i++){
		std::cin>>a[i];
	}
	std::set<ll> set;
	std::map<ll, ll> cnt;
	set.insert(-1);
	while (k--){
		ll x, y;
		std::cin>>x>>y;
		if (y==0){
			set.insert(x);
		}
		cnt[x]=y;
	}
	ll sum=0;
	for (auto x:a){
		auto it=set.upper_bound(x);
		it=std::prev(it);
		ll tar=(*it)+1;
		sum+=x-tar;
		cnt[tar]--;
		if (cnt[tar]==0){
			set.insert(tar);
		}
	}
	if (sum%2){
		std::cout<<"Pico\n";
	}
	else{
		std::cout<<"FuuFuu\n";
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