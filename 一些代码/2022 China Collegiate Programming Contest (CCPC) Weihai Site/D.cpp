#include <bits/stdc++.h>

const int M=1e5+5;
const int inf=0x3fffffff;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 lll;

/*
状压dp
按题意转移即可
处理位置
pos状态到位置的映射
vis判断x,y的合法性
6个领边的移动（人工处理一下）
from来源
to到达
*/



std::pair<int, int> pos[19];

int vis[10][10]{
	{1, 1, 2},
	{3, 4, 5, 6},
	{7, 8, 9, 10, 11},
	{12, 13, 14, 15},
	{16, 17, 18}
};

std::pair<int, int> from[6]={
	{-1, -1},
	{-1, 0},
	{0, -1},
	{0, 1},
	{1, -1},
	{1, 0},
};

std::pair<int, int> to[6]={
	{1, 0},
	{1, -1},
	{0, 1},
	{0, -1},
	{-1, 0},
	{-1, -1},
};


const int N=1<<19;
ll dp[N];
//19个点的合法移动对应的状态
std::vector<std::pair<int, int>> e[19];
std::map<std::pair<int, int>, int> mp;//坐标映射状态
ll val[19];
ll dpvis[N];

ll dfs(int s){
	if (dpvis[s]){
		return dp[s];
	}
	for (int i=0; i<19; i++){
		if ((s>>i)&1){
			dp[s]=std::max(dp[s], dfs(s^(1<<i)));
			for (auto [u, v]:e[i]){
				if (((s>>u)&1) && ((s>>v)&1)==0){
					int nxt=s^(1<<u);
					nxt^=(1<<i);
					nxt|=(1<<v);
					dp[s]=std::max(dp[s], dfs(nxt)+val[i]);
				}
			}
		}
	}
	dpvis[s]=1;
	return dp[s];
}

void init(){
	// for (int i=0; i<10; i++){
	// 	for (int j=0; j<10; j++){
	// 		std::cout<<vis[i][j]<<" ";
	// 	}
	// 	std::cout<<"\n";
	// }

	int now=0;
	for (int i=0; i<10; i++){
		for (int j=0; j<10; j++){
			if (vis[i][j]){
				pos[now]={i, j};
				mp[{i, j}]=now;
				now++;
			}
		}
	}

	// for (auto [x, y]:pos){
	// 	std::cout<<x<<" "<<y<<"\n";
	// }
	// std::cout<<std::endl;

	for (int i=0; i<19; i++){
		std::cin>>val[i];
		auto [x, y]=pos[i];

		if (x==2){
			for (int j=0; j<6; j++){
				if (mp.count({x+from[j].first, y+from[j].second}) && mp.count({x+to[j].first, y+to[j].second})){
					e[i].emplace_back(mp[{x+from[j].first, y+from[j].second}], mp[{x+to[j].first, y+to[j].second}]);
				}
			}
			continue;
		}

		if (mp.count({x, y+1}) && mp.count({x, y-1})){
			//拥有左右块
			int u=mp[{x, y+1}], v=mp[{x, y-1}];
			e[i].emplace_back(u, v);
			std::swap(u, v);
			e[i].emplace_back(u, v);
		}
		if (mp.count({x+1, y}) && mp.count({x-1, y})){
			//上下跳
			int u=mp[{x+1, y}], v=mp[{x-1, y}];
			e[i].emplace_back(u, v);
			std::swap(u, v);
			e[i].emplace_back(u, v);
		}

		if (x<2){
			//上半为左上右下
			if (mp.count({x-1, y-1}) && mp.count({x+1, y+1})){
				int u=mp[{x-1, y-1}], v=mp[{x+1, y+1}];
				e[i].emplace_back(u, v);
				std::swap(u, v);
				e[i].emplace_back(u, v);
			}
		}
		else{
			//下半为右上左下
			if (mp.count({x+1, y-1}) && mp.count({x-1, y+1})){
				int u=mp[{x+1, y-1}], v=mp[{x-1, y+1}];
				e[i].emplace_back(u, v);
				std::swap(u, v);
				e[i].emplace_back(u, v);
			}
		}
	}

	// for (int i=0; i<19; i++){
	// 	std::cout<<i<<"ERR:\n";
	// 	for (auto [x, y]:e[i]){
	// 		std::cout<<x<<" "<<y<<"\n";
	// 	}
	// 	std::cout<<"END\n";
	// }
	// std::cout<<std::endl;

	// for (int s=0; s<N; s++){
	// 	dfs(s);
	// }
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    init();
    int n;
    std::cin>>n;
    while (n--){
    	int sta=0;
    	char c;
    	for (int i=0; i<19; i++){
    		std::cin>>c;
    		if (c=='#'){
    			sta|=(1<<i);
    		}
    	}
    	// std::cout<<dp[sta]<<"\n";
    	std::cout<<dfs(sta)<<"\n";
    }
    return 0;
}