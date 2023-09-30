#include <bits/stdc++.h>

const int N=1e5+5;
const int M=1e5+5;
const int inf=0x3fffffff;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 lll;

/*
给定n个条件，让你找到满足所有条件的区间
该区间包含连续的整数
1kx 存在k个不同的数和为x
2kx 不存在k个不同的数和为x
*/

/*
t数据
n
tkx
*/

/*
首先知道区间l,r则可得出表态和的范围
k(l+l+k-1)/2   k(r+r-k+1)/2
分析（移项）得如果区间长度小于k，则上限则必然非法
条件1 <=x<=  代入x得
l<=(2x+k(1-k))/2k (下取整)
r>=(2x+k(k-1))/2k (上取整)
显然对条件1 l取min, r取max即可满足(小分析一下，发现k<1时r<l，所以无论如何区间显然合法)

条件二 有x<L or x>r 再代入x得
l>(2x+k(1-k))/2k (下取整)
或r<(2x+k(k-1))/2k (上取整)
或区间长度小于k
转换条件，如果l<= 且r>= 则为非法
则我们可以先将l排序，然后遍历一遍同时记下对应的非法区间就可以统计答案
即从大到小在(l_{i} l_{i+1}]区间里非法的r就是后缀min
*/

const ll INF=ll(2e18)+7;

ll getL(ll &x, ll &k){
    return (2*x+k*(1-k))/(2*k);
}

ll getR(ll &x, ll &k){
    return (2*x+k*(k-1)+2*k-1)/(2*k);
}

void solve(){
    ll ans=0;
    int n;
    std::cin>>n;
    std::vector<std::pair<ll, ll>> a;
    ll mnl=INF, mxr=0;
    while (n--){
        ll t, x, k;
        std::cin>>t>>k>>x;
        if (t==1){
            mnl=std::min(mnl, getL(x, k));
            mxr=std::max(mxr, getR(x, k));
        }
        else{
            a.emplace_back(getL(x, k), getR(x, k));
        }
    }
    if (mnl<=0){
        std::cout<<ans<<"\n";
        return;
    }
    std::sort(a.begin(), a.end(), std::greater<std::pair<ll, ll>>());
    if (a.size()==0 || a[0].first<mnl){
        //无限制情况，r是可以无穷大的
        std::cout<<-1<<"\n";
        return;
    }
    //从大到小
    ll tmpr=INF;
    int m=a.size();
    for (int i=0; i<m-1; i++){
        auto [l, r]=a[i];
        auto [nxl, nxr]=a[i+1];
        tmpr=std::min(tmpr, r);
        if (mnl<=nxl) continue;
        if (l<=0) continue;
        if (nxl<0) nxl=0;
        ll cntl=std::min(l-nxl, mnl-nxl);
        ll cntr=std::max(tmpr-mxr, 0ll);
        ans+=cntl*cntr;
    }
    auto [l, r]=a[m-1];
    tmpr=std::min(tmpr, r);
    if (l>0ll){
        ll cntl=std::min(l-0ll, mnl-0ll);
        ll cntr=std::max(tmpr-mxr, 0ll);
        ans+=cntl*cntr;
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