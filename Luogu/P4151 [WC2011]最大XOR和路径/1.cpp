#include <algorithm>
#include <cstdio>

typedef long long ll;
const int N = 5e4+45, M = 1e5+51;

struct edge { int to, next; ll w; } e[M<<1];
int head[N], cnt;
void addedge(int x, int y, ll z) {
	e[++cnt] = (edge){y, head[x], z}; head[x] = cnt;
	e[++cnt] = (edge){x, head[y], z}; head[y] = cnt;
}

ll a[N];
void insert(ll x) {
	for (int i = 60; i >= 0; i--) {
		if (1 & ~(x >> (ll)i)) continue;
		if (!a[i]) { a[i] = x; return; }
		x ^= a[i]; 
	}
}

ll xv[N], ans;
bool vis[N];
int n;
void dfs(int x, ll v) {
	xv[x] = v; vis[x] = 1;
	if (x == n) ans = std::max(ans, v);
	for (int i = head[x]; i; i = e[i].next) {
		int nx = e[i].to;
		if (vis[nx]) insert(v ^ e[i].w ^ xv[nx]);
		else dfs(nx, v ^ e[i].w);
	}
}

int m, x, y;
ll z;
int main() {
	for (scanf("%d%d", &n, &m); m--; ) {
		scanf("%d%d%lld", &x, &y, &z);
		addedge(x, y, z);
	}
	dfs(1, 0);
	for (int i = 60; i >= 0; i--) {
		ans = std::max(ans, ans ^ a[i]);
	}
	printf("%lld", ans);
}