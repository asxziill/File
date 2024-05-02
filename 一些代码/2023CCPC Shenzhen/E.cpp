#include <bits/stdc++.h>

using ll = long long;

/*
注意到区间固定，每次移动一个单位，每个颜色的数量只会+1和-1
关注两个颜色的二进制表示，发现如果一个位置同时有1，则在连续的-1后一定会有一个仍有1，另一个是01111..的情况
然后如果是10的情况则必然更劣的，（只会把1减掉）
所以答案为a | b | (a & b的最高为的1)
这个时候就可以枚举出现次数了复杂度O(n)

也可以发现选最大的两个即可，
因为确定一个数，然后选择另一个数，发现另一个数每一个1越高位越大（或出来的结果的1就会在越高位）
所以两个数取最大答案就是最大的
*/


void solve() {
  int n;
  std::cin >> n;
  std::vector<std::vector<int>> c(n);
  for (int i = 0; i < n; i++) {
    int a;
    std::cin >> a;
    a--;
    c[a].push_back(i);
  }

  std::vector<int> a(n);
  for (int i = 0; i < n; i++) {
    if (!c[i].empty()) {
      a.push_back(c[i].size());
    }
  }
  std::sort(a.begin(), a.end());
  std::reverse(a.begin(), a.end());
  if (a.size() == 1) {
    std::cout << a[0] << "\n";
    return;
  }
  int x = a[0], y = a[1];
  int t = x & y;
  int len = 1;
  while ((len * 2) <= t) {
    len *= 2;
  }
  len -= 1;
  int ans = (x | y | len);
  std::cout << ans << "\n";
}

int main() {
  std::ios::sync_with_stdio(false);
  std::cin.tie(nullptr);
  int t;
  std::cin >> t;
  while (t--) {
    solve();
  }    
  return 0;
}