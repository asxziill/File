#include <bits/stdc++.h>

const int N=1e5+5;
const int M=1e5+5;
const int inf=0x3fffffff;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 lll;

/*
• TI 比赛有 n 只冠军队伍，每个队伍由五个选手组成，每个
选手分别打 1-5 号位中的一个，一个选手永远只打一个位
置，不会打其他位置。有 m 名选手组队，问最多能组多少
队，满足每个队内至少有一名冠军选手。
*/

/*
n冠军数量
m参赛人和位置
*/

/*
平均分组好队 位置min
冠军一个队一个(交互即可)
*/


int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n;
    std::cin>>n;
    std::set<std::string> set;
    for (int i=0; i<n; i++){
    	std::string s;
    	for (int j=0; j<5; j++){
    		std::cin>>s;
    		set.insert(s);
    	}
    }
    int m;
    std::cin>>m;
    int cnt=0;
    std::vector<int> num(5);
    while (m--){
    	std::string s;
    	int pos;
    	std::cin>>s>>pos;
    	pos--;
    	num[pos]++;
    	if (set.count(s)){
    		cnt++;
    	}
    }
    std::cout<<std::min((*std::min_element(num.begin(), num.end())), cnt);
    return 0;
}