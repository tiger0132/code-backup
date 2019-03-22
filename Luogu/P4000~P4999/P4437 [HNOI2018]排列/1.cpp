#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

using ll = long long;
const int N = 5e5 + 55;
struct edge {
	int to, next;
} e[N << 1];
int head[N], cnt;
inline void addedge(int x, int y) { e[++cnt] = (edge){y, head[x]}, head[x] = cnt; }

struct node {
	int x, sz;
	ll w;
	inline bool operator<(const node& rhs) const { return sz * rhs.w < rhs.sz * w; }
};

int n, _ = 1, a[N], w[N], sz[N], p[N];
std::priority_queue<node> q;
ll ans;
int f(int x) { return x == p[x] ? p[x] = f(p[x]) : x; }
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= n; i++) {
		scanf("%d", a + i), _ &= a[i];
		addedge(a[i], i);
	}
	if (_) return puts("-1"), 0;
	for (int i = 0; i <= n; i++) p[i] = i, sz[i] = 1;
	for (int i = 1; i <= n; i++) {
		scanf("%d", w + i);
		q.push((node){i, 1, w[i]});
	}
	while (!q.empty()) {
		node x = q.top();
		q.pop();
		int u = f(x.x), v = f(a[u]);
		if (sz[u] != x.sz) continue;
		p[u] = v;
		ans += w[u] * sz[v], w[v] += w[u], sz[v] += sz[u];
		if (v) q.push((node){v, sz[v], w[v]});
	}
	printf("%lld", ans);
}