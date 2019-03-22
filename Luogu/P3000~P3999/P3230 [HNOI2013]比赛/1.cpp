#include <algorithm>
#include <cstdio>
#include <cstring>
#include <unordered_map>

using ll = long long;
const int N = 22, P = 1e9 + 7;

std::unordered_map<ll, ll> mp;
int n, win, draw, sum, a[N];

ll H(int x) {
	static int t[N];
	ll ret = 0;
	memcpy(t, a, sizeof t);
	std::sort(t + x + 1, t + n + 1);
	for (int i = x + 1; i <= n; i++) ret = ret * 97 + t[i];
	return ret;
}
ll dfs(int x, int y) {
	if (x == n) return 1;
	if (a[x] > 3 * (n - y + 1)) return 0;
	if (y > n) {
		ll hv = H(x);
		if (mp.count(hv)) return mp[hv];
		return mp[hv] = dfs(x + 1, x + 2);
	}
	ll ret = 0;
	if (a[x] >= 3 && win) a[x] -= 3, win--, ret += dfs(x, y + 1), a[x] += 3, win++;
	if (a[x] >= 1 && a[y] >= 1 && draw) a[x]--, a[y]--, draw--, ret += dfs(x, y + 1), a[x]++, a[y]++, draw++;
	if (a[y] >= 3 && win) a[y] -= 3, win--, ret += dfs(x, y + 1), a[y] += 3, win++;
	return ret % P;
}

int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", a + i), sum += a[i];
	std::sort(a + 1, a + n + 1);
	win = sum - n * (n - 1);
	draw = (sum - 3 * win) / 2;
	printf("%lld", dfs(1, 2));
}