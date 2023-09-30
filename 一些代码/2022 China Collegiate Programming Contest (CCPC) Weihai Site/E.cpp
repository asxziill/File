#include <bits/stdc++.h>

const int N=1e5+5;
const int M=1e5+5;
const int inf=0x3fffffff;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 lll;

/*
给n个时间和预测公式
求是否会少于给函数定值
*/

/*
n数量，k要小于的值
a
*/

/*
a_i=max(0, 2a_{i-1}-a_{i-2})
a_i=2a_{i-1}-a_{i-2}
a_i-a_{i-1}=a_{i-1}-a_{i-2}
一次函数
则斜率为a_n-a_{n-1}=c
a_{n}+xc<k
xc<k-a_{n}   (c负数)
x>()/c
上取整

*/

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, k;
    std::cin>>n>>k;
    std::vector<int> a(n);
    for (int i=0; i<n; i++){
    	std::cin>>a[i];
    	if (a[i]<k){
    		std::cout<<"Python 3.";
    		std::cout<<(i+1);
    		std::cout<<" will be faster than C++";
    		return 0;
    	}
    }
    int c=a[n-1]-a[n-2];
    if (c>=0){
    	std::cout<<"Python will never be faster than C++";
    }
    else{
    	//直接得到范围再微调
    	int ans=(-1*(k-a[n-1])-c-1)/(-1*c);
    	while (a[n-1]+(ans)*c>=k){
    		ans++;
    	}
    	while (a[n-1]+(ans-1)*c<k){
    		ans--;
    	}
    	ans+=n;

    	std::cout<<"Python 3.";
    	std::cout<<(ans);
    	std::cout<<" will be faster than C++";
    }
    return 0;
}