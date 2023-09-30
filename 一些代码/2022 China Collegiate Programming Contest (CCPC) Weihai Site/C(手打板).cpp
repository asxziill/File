#include<bits/stdc++.h>
// 手打板

using ll = long long;

struct Point
{
	ll x, y;
	void in(){
		std::cin>>x>>y;
	}
	Point (ll x=0, ll y=0):x(x), y(y){}
	void out(){
		std::cout<<x<<" "<<y<<"\n";
	}
};

Point operator-(Point a, Point b){
	return Point(a.x-b.x, a.y-b.y);
}

ll cross(Point a, Point b){
	return a.x*b.y-a.y*b.x;
}

ll dot(Point a, Point b){
	return a.x*b.x+a.y*b.y;
}

Point ans[5];
const int N=int(1e5)+5;
Point p[N];

bool check(Point a, Point b){
	if (cross(a, b)==0 && dot(a, b)>=0){
		return true;
	}
	return false;
}

void solve(){
	int n;
	std::cin>>n;
	for (int i=0; i<n; i++){
		p[i].in();
	}
	if (n<5){
		std::cout<<"NO\n";
		return;
	}
	int ok=0;
	for (int i=0; i<4; i++){
		ans[i]=p[i];
		if (i>1){
			if (cross(ans[1]-ans[0], p[i]-ans[0])!=0){
				ok=1;
			}
		}
	}
	if (ok){
		ans[4]=p[4];
	}
	for (int i=4; i<n; i++){
		if (ok) break;
		if (cross(ans[1]-ans[0], p[i]-ans[0])!=0){
			ok=1;
			ans[4]=p[i];
		}
	}
	if (!ok){
		std::cout<<"NO\n";
		return;
	}
	std::cout<<"YES\n";
	for (int i=0; i<5; i++){
		std::vector<Point> line;

		for (int j=0; j<5; j++){
			if (i==j) continue;
			line.push_back(ans[j]-ans[i]);
		}

		int ok=1;

		for (int x=0; x<4; x++){
			for (int y=0; y<4; y++){
				if (x==y) continue;
				if (check(line[x], line[y])){
					ok=0;
					break;
				}
			}
			if (!ok) break;
		}

		if (ok){
			ans[i].out();
			for (int j=0; j<5; j++){
				if (i!=j){
					ans[j].out();
				}
			}
			return;
		}
	}
}

int main(){
	std::ios::sync_with_stdio(0);
	std::cin.tie(0);
	int t;
	std::cin>>t;
	while (t--){
		solve();
	}
	return 0;
}