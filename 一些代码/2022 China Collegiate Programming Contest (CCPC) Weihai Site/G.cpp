#include <bits/stdc++.h>

const int N=1e5+5;
const int M=1e5+5;
const int inf=0x3fffffff;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 lll;

/*
给定值x
求题目式子大小
*/

/*
x,n定值和数据
l,r范围
*/

/*
通过打表式子与gcd发现
gcd可能有循环节的性质
且大小应该在x左右
且如果x为偶数，gcd不为1

先暴力计算gcd再通过KMP得到循环节大小，预处理出来即可
*/

ll x;
std::vector<ll> pre;//循环节内1数量的前缀和
ll sum=0;//循环节中1的数量
ll cirlen;//循环节长度

std::vector<int> KMP(std::vector<ll> s) {
	// for (auto x:s){
	// 	std::cout<<x<<" ";
	// }
	// std::cout<<std::endl;
    int n = s.size();
    std::vector<int> f(n + 1);
    for (int i = 1, j = 0; i < n; i++) {
        while (j && s[i] != s[j]) {
            j = f[j];
        }
        j += (s[i] == s[j]);
        f[i + 1] = j;
    }
    return f;
}

void init(){
	ll len=x*10+5;
	std::vector<ll> gcd(len);
	for (ll k=1; k<=len; k++){
		gcd[k-1]=std::gcd((k*x)^x, x);
	}
	auto nxt=KMP(gcd);
	cirlen=len-nxt.back();
	// std::cout<<cirlen<<std::endl;
	pre.resize(cirlen+2);
	pre[0]=0;
	for (int i=0; i<cirlen; i++){
		sum+=(gcd[i]==1);
		pre[i+1]=pre[i]+(gcd[i]==1);
	}
}

void err(ll a){
	x=a;
	init();
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    //打表发现周期好像是2的倍数
    // for (int i=1; i<=100; i++){
    // 	err(i);
    // }

    ll n;
    std::cin>>x>>n;
    init();
    while (n--){
    	ll l, r;
    	std::cin>>l>>r;
    	if (x%2==0){
    		std::cout<<0<<"\n";
    	}
    	else{
    		l--;
    		ll lcnt=(l/cirlen)*sum;
    		l%=cirlen;
    		lcnt+=pre[l];
    		ll rcnt=(r/cirlen)*sum;
    		r%=cirlen;
    		rcnt+=pre[r];
    		std::cout<<(rcnt-lcnt)<<"\n";
    	}
    }

    return 0;
}
/*
打表打的
const int N=100;
for (ll x=1; x<=N; x++){
    ll sum=0;
    for (ll k=1; k<=N; k++){
        if (std::gcd(((k*x)^x), x)==1){
            sum++;
        }
        // std::cout<<sum<<" \n"[k==N];
        std::cout<<std::gcd(((k*x)^x), x)<<" \n"[k==N];
    }
}
*/