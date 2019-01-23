#include <algorithm>
#include <cstdio>
#include <set>
#define S std::set<int, cmp>
#define $ iterator

typedef long long ll;
const int N = 1e5 + 51, M = 17;
struct edge {
	int to, next;
	ll w;
} e[N << 1];
int head[N], cnt;
void addedge(int x, int y, ll z) {
	e[++cnt] = (edge){y, head[x], z};
	head[x] = cnt;
	e[++cnt] = (edge){x, head[y], z};
	head[y] = cnt;
}

int par[N][M + 1], dep[N], dfn[N], idx;
ll dis[N];
void dfs(int x) {
	dfn[x] = ++idx;
	for (int i = head[x]; i; i = e[i].next) {
		int nx = e[i].to;
		if (nx == par[x][0]) continue;
		par[nx][0] = x;
		dep[nx] = dep[x] + 1;
		dis[nx] = dis[x] + e[i].w;
		dfs(nx);
	}
}

int n;
void init() {
	for (int i = 1; i <= M; i++) {
		for (int j = 1; j <= n; j++) {
			par[j][i] = par[par[j][i - 1]][i - 1];
		}
	}
}

int lca(int x, int y) {
	if (dep[x] < dep[y]) std::swap(x, y);
	int sub = dep[x] - dep[y];
	for (int i = 0; i <= M; i++) {
		if (sub >> i & 1) x = par[x][i];
	}
	if (x == y) return x;
	for (int i = M; i >= 0; i--) {
		if (par[x][i] != par[y][i]) {
			x = par[x][i];
			y = par[y][i];
		}
	}
	return par[x][0];
}

inline ll dist(int x, int y) { return dis[x] + dis[y] - 2 * dis[lca(x, y)]; }

struct cmp {
	bool operator()(int x, int y) const { return dfn[x] < dfn[y]; }
};

S st = S(cmp());
int m, x, y, z;
bool vis[N];
ll ans;

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i < n; i++) {
		scanf("%d%d%d", &x, &y, &z);
		addedge(x, y, z);
	}
	dfs(1);
	init();
	while (m--) {
		scanf("%d", &x);
		if (vis[x]) {
			S::$ it = st.find(x);
			if (st.size() < 3) {
				ans = 0;
				goto end;
			}
			int pre, nxt;
			if (it == st.begin())
				pre = *--st.end();
			else
				pre = *(--it), ++it;

			if (it == --st.end())
				nxt = *st.begin();
			else
				nxt = *(++it), --it;

			ans -= dist(pre, x) + dist(x, nxt) - dist(pre, nxt);
		end:
			st.erase(it);
		} else {
			S::$ it = st.insert(x).first;
			if (st.size() == 1) goto end2;
			int pre, nxt;
			if (it == st.begin())
				pre = *--st.end();
			else
				pre = *(--it), ++it;

			if (it == --st.end())
				nxt = *st.begin();
			else
				nxt = *(++it), --it;

			ans += dist(pre, x) + dist(x, nxt) - dist(pre, nxt);
		end2:;
		}
		vis[x] ^= 1;
		printf("%lld\n", ans);
	}
}