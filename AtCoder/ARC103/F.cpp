#include <algorithm>
#include <cstdio>
#include <cstring>
#include <functional>
#include <map>

typedef long long ll;
const int N = 1e5 + 51;
struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y) {
	e[++cnt] = (edge){y, x[head]}, x[head] = cnt;
	e[++cnt] = (edge){x, y[head]}, y[head] = cnt;
}

ll ans;
void dfs(int x, int p, int d) {
	ans += d;
	for (int i = x[head], nx; i; i = e[i].next)
		if ((nx = e[i].to) != p) dfs(nx, x, d + 1);
}

int p[N];
int f(int x) { return x[p] ? x[p] = f(x[p]) : x; }
void l(int x, int y) {
	if ((x = f(x)) != (y = f(y))) x[p] = y;
}

std::map<ll, int> mp;
int n, sz[N];
ll a[N];
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) scanf("%lld", a + i), i[sz] = 1, mp[a[i]] = i;
	std::sort(a + 1, a + n + 1, std::greater<ll>());
	for (int i = 1; i < n; i++) {
		int x = mp[a[i]], nx;
		ll tmp = a[i] - n + 2 * x[sz];
		if (tmp >= a[i] || !mp.count(tmp)) return puts("-1"), 0;
		nx = mp[tmp];
		nx[sz] += x[sz];
		if (f(x) == f(nx)) return puts("-1"), 0;
		addedge(x, nx);
		l(x, nx);
	}
	dfs(mp[a[1]], 0, 0);
	if (ans != a[1]) return puts("-1"), 0;
	for (int i = 1; i <= cnt; i += 2) printf("%d %d\n", e[i + 1].to, e[i].to);
}