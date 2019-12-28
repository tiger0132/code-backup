#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>

typedef long long ll;
const int N = 1e5 + 51, P = 1e9 + 7;

struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = (edge){y, x[head]}, x[head] = cnt;
	e[++cnt] = (edge){x, y[head]}, y[head] = cnt;
}

std::map<ll, int> mp[N];
int n, x, y, ans;
ll a[N];
void dfs(int x, int p) {
	for (auto i : mp[p]) {
		ll v = std::__gcd(i.first, a[x]);
		mp[x][v] += i.second;
		ans = (ans + v * i.second) % P;
	}
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != p) dfs(nx, x);
}
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++)
		scanf("%lld", a + i), mp[i][a[i]]++, ans = (ans + a[i]) % P;
	for (int i = 1; i < n; i++) scanf("%d%d", &x, &y), addedge(x, y);
	dfs(1, 0);
	printf("%d", ans);
}