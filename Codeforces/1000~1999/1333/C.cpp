#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
#define int long long

const int N = 1e5 + 51;

std::map<int, int> mp;
long long ans, s;
int n, x, mx;
signed main() {
	scanf("%lld", &n);
	mp[0] = 0;
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &x), s += x;
		if (mp.count(s)) mx = std::max(mx, mp[s] + 1);
		mp[s] = i;
		ans += i - mx;
	}
	printf("%lld", ans);
}