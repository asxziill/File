#include <bits/stdc++.h>

const int N=1e5+5;
const int M=1e5+5;
const int inf=0x3fffffff;
typedef long long ll;
typedef unsigned long long ull;
typedef __int128 lll;


std::vector<ll> acnt(2);
std::vector<int> apos(2);

std::vector<std::vector<int>> getAns(std::vector<int> &a){
	int n=a.size();

	std::vector res(2, std::vector<int>(2, inf));

	for (int i=0; i<n; i++){
		std::vector<int> vis(n);
		int cnt=0;
		for (int j=0; j<n; j++){
			if (vis[j]==0){
				int iszero=0;
				int len=0;
				int p=j;
				while (!vis[p]){
					if (a[p]==0){
						iszero=1;
					}
					len++;
					vis[p]=1;
					p=(a[p]+i)%n;
				}
				//有0贡献长,否则为长+1
				if (len!=1){
					cnt+=(iszero==1)?(len-1):(len+1);
				}
			}
		}

		if (cnt<res[cnt%2][0]){
			res[cnt%2]={cnt, i};
		}
	}

	return res;

}

std::vector<int> outAns(std::vector<int> &a, int apos){
	std::vector<int> ans;
	int n=a.size();
	std::vector<int> vis(n);
	for (int i=0; i<n; i++){
		if (!vis[i]){
			int p=i;
			std::stack<int> sta;
			//环反着来
			int iszero=0;
			while (!vis[p]){
				vis[p]=1;
				if (a[p]==0) iszero=1;
				sta.push(a[p]);
				p=(a[p]+apos)%n;
			}
			if (sta.size()>1){
				if (iszero){
					while (!sta.empty()){
						if (sta.top()){
							ans.push_back(sta.top());
						}
						sta.pop();
					}
				}
				else{
					int d=sta.top();
					while (!sta.empty()){
						ans.push_back(sta.top());
						sta.pop();
					}
					ans.push_back(d);
				}
			}
		}
	}
	std::vector<int> res;
	int zp=0;
	for (int i=0; i<n; i++){
		if (a[i]==0){
			zp=i;
			break;
		}
	}
	for (int x:ans){
		for (int i=1; i<n; i++){
			if (a[(zp+i)%n]==x){
				std::swap(a[zp], a[(zp+i)%n]);
				zp=(zp+i)%n;
				res.push_back(i);
				break;
			}
		}
	}
	return res;
}


int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    int n, m;
    std::cin>>n>>m;
    std::vector<int> a;
    a.push_back(0);
    for (int i=0; i<n; i++){
    	int x;
    	std::cin>>x;
    	a.push_back(x);
    }
    std::vector<std::vector<int>> resa=getAns(a);
    std::vector<int> b;
    b.push_back(0);
    for (int i=0; i<m; i++){
    	int x;
    	std::cin>>x;
    	b.push_back(x);
    }
    std::vector<std::vector<int>> resb=getAns(b);


    std::vector<int> ansa, ansb;
    if (std::max(resa[0][0], resb[0][0])<std::max(resa[1][0], resb[1][0])){
    	if (std::max(resa[0][0], resb[0][0])==inf){
    		std::cout<<-1<<"\n";
    		return 0;
    	}
    	ansa=outAns(a, resa[0][1]);
    	ansb=outAns(b, resb[0][1]);
    }
    else{
    	if (std::max(resa[1][0], resb[1][0])==inf){
    		std::cout<<-1<<"\n";
    		return 0;
    	}
    	ansa=outAns(a, resa[1][1]);
    	ansb=outAns(b, resb[1][1]);

    }

    int ans=std::max(ansa.size(), ansb.size());
    int at=1, bt=1;
    std::cout<<ans<<"\n";
    for (int i=0; i<ans; i++){
    	if (i<ansa.size()){
    		std::cout<<ansa[i];
    	}
    	else{
    		std::cout<<at;
    		at=n+1-at;
    	}
    	std::cout<<" ";
    	if (i<ansb.size()){
    		std::cout<<ansb[i];
    	}
    	else{
    		std::cout<<bt;
    		bt=m+1-bt;
    	}
    	std::cout<<"\n";
    }
    return 0;
}