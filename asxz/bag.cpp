//01背包 
//总空间V
//对物品质量，v,价值w有
void DP(std::pair<int, int> obj){
    auto [v, w]=obj;
    for (int x=V; x>=v; x--){
        //由dp[x]和dp[x-v]转移来
        dp[x]=f(dp[x], dp[x-v], w);
    }
}

//完全背包
//总空间V
//对物品质量，v,价值w有
void DP(std::pair<int, int> obj){
    auto [v, w]=obj;
    for (int x=v; x<=V; x--){
        //由dp[x]和dp[x-v]转移来且dp[x-v]是已处理过该物品
        dp[x]=f(dp[x], dp[x-v], w);
    }
} 

//多重背包 
//总空间V
//对物品质量，v,价值w, 数量cnt有
void DP(std::tuple<int, int, int> obj){
    auto [v, w, cnt]=obj;
    int k=1;
    while (k<cnt){
        int x=v*k;
        //对每块做01背包
        for (int vi=V; vi>=x; vi--){
            dp[vi]=f(dp[vi], dp[vi-x], w);
        }
        cnt-=k;
        k*=2;
    }
    int x=v*cnt;
    for (int vi=V; vi>=x; vi--){
        dp[vi]=f(dp[vi], dp[vi-x], w);
    }
}

//分组背包
//总空间V
//对组内每个物品质量，v,价值w
void DP(std::vector<std::pair<int, int>> obj){
    //视该组为一个整体
    for (int vi=V; vi>=0; vi--){
        //一个空间vi只由选组内一个物品转移来
        for (auto [v, w]:obj){
            if (vi>=v){
                dp[vi]=f(dp[vi], dp[vi-v], w);
            }
        }
    }
} 
