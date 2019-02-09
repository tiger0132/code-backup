#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

typedef long long ll;
const int N = 5e2 + 25, M = 1e5 + 51;
const ll INF = 1e15;
struct edge {
	int to, next;
	ll w;
} e[M << 1];
int head[N], cnt = 1;
void addedge(int x, int y, ll z) {
	e[++cnt] = (edge){y, head[x], z}, head[x] = cnt;
	e[++cnt] = (edge){x, head[y], 0}, head[y] = cnt;
}

int lv[N];
bool bfs(int s, int t) {
	memset(lv, 0, sizeof lv);
	std::queue<int> q;
	lv[s] = 1;
	q.push(s);
	while (!q.empty()) {
		int x = q.front();
		q.pop();
		for (int i = head[x]; i; i = e[i].next) {
			int nx = e[i].to;
			if (!e[i].w || lv[nx]) continue;
			lv[nx] = lv[x] + 1;
			q.push(nx);
		}
	}
	return lv[t];
}
ll dfs(int s, int t, ll f) {
	if (s == t) return f;
	ll r = 0;
	for (int i = head[s]; f && i; i = e[i].next) {
		int nx = e[i].to;
		if (!e[i].w || lv[nx] != lv[s] + 1) continue;
		ll tmp = dfs(nx, t, std::min(f, e[i].w));
		r += tmp, f -= tmp;
		e[i].w -= tmp, e[i ^ 1].w += tmp;
	}
	return r;
}
ll dinic(int s, int t) {
	ll ret = 0;
	while (bfs(s, t)) ret += dfs(s, t, INF);
	return ret;
}

int n, m, a[N], b[N], f[N][N];
ll s;
bool check(ll x) {
	memset(head, 0, sizeof head), cnt = 1;
	for (int i = 1; i <= m; i++) addedge(1, i + 2, x * b[i]);
	for (int i = 1; i <= n; i++) addedge(i + m + 2, 2, a[i]);
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			if (f[i][j]) addedge(i + 2, j + m + 2, INF);
		}
	}
	ll t = dinic(1, 2);
	return t == s;
}

int l, r;
signed main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%d", a + i);
		s += a[i] *= 10000;
	}
	for (int i = 1; i <= m; i++) scanf("%d", b + i);
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) {
			scanf("%d", f[i] + j);
		}
	}
	for (l = 1, r = 1e9; l < r;) {
		int mid = (l + r) >> 1;
		if (check(mid))
			r = mid;
		else
			l = mid + 1;
	}
	printf("%.4f", r / 1e4);
}