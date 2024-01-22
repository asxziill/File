#include <bits/stdc++.h>

using ll = long long;

int get(char c){
	if (c == '(' || c == ')') return 0;
	else return 1;
}

void solve(){
	std::string s;
	std::cin >> s;
	int n = s.size();
	std::vector<std::set<int>> occur(n + 1); 
	std::vector<int> sta;
	sta.push_back(n);
	//保证同等级下没有多于一个同类型的匹配括号
	for (int i = 0; i < n; i++){
		if (sta.size() > 1 && get(s[sta.back()]) == get(s[i])){
			sta.pop_back();
			int x = get(s[i]);
			int y = sta.back();
			if (occur[y].count(x)){
				std::cout << "No\n";
				return;
			}
			occur[y].insert(x);
		}
		else{
			sta.push_back(i);
		}
	}
	std::cout << "Yes\n";
}

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int t;
    std::cin >> t;
    while (t--){
    	solve();
    }
    return 0;
}