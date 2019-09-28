#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

const int N = 1e5 + 51, M = 2e5 + 52, K = 55;
struct graph {
	struct edge {
		int to, next, w;
	} e[M << 1];
	int head[N], cnt;
	void addedge(int x, int y, int z = 0) {
		e[++cnt] = (edge){y, x[head], z}, x[head] = cnt;
	}
	void clear() { memset(head, 0, sizeof head), cnt = 0; }
} rg, g, h;

struct node {
	int x, d;
	bool operator<(const node& r) const { return d > r.d; }
};
std::priority_queue<node> pq;
int n, dis[N], rdis[N];
void spfa(const graph& g, int s, int* da) {
	memset(da, 0x3f, sizeof dis), s[da] = 0;
	for (pq.push((node){s, 0}); !pq.empty();) {
		node t = pq.top();
		pq.pop();
		int x = t.x, d = t.d;
		if (d != x[da]) continue;
		for (int i = x[g.head], nx; i; i = g.e[i].next)
			if ((nx = g.e[i].to)[da] > x[da] + g.e[i].w)
				nx[da] = x[da] + g.e[i].w, pq.push({nx, nx[da]});
	}
}

int P, v[N], dp[N][K], st[N], top, f, k;
void dfs(int x) {
	x[v] = 1;
	for (int i = x[h.head], nx; i; i = h.e[i].next)
		if ((nx = h.e[i].to)[v] == 1 && nx[dis] + nx[rdis] <= n[dis] + k)
			f = 1;
		else if (!nx[v])
			dfs(nx);
	st[top--] = x, x[v] = -1;
}

int m, x, y, z, ans;
int main() {
	for (scanf("%*d"); ~scanf("%d%d%d%d", &n, &m, &k, &P);) {
		memset(v, 0, sizeof v), memset(st, 0, sizeof st), memset(dp, 0, sizeof dp),
			top = n, ans = 0;
		g.clear(), h.clear(), rg.clear();
		for (int i = 1; i <= m; i++)
			scanf("%d%d%d", &x, &y, &z), g.addedge(x, y, z), rg.addedge(y, x, z);
		spfa(g, 1, dis), spfa(rg, n, rdis);
		// for (int i = 1; i <= n; i++) printf("[%d]", dis[i]);
		// puts("");
		// for (int i = 1; i <= n; i++) printf("[%d]", rdis[i]);
		// puts("");
		for (int i = 1; i <= n; i++)
			for (int j = i[g.head], nx; j; j = g.e[j].next)
				if ((nx = g.e[j].to)[dis] == i[dis] + g.e[j].w) h.addedge(i, nx);
		// , printf("[%d -> %d]\n", i, nx);
		f = 0, dfs(1);
		// for (int i = 1; i <= n; i++) printf("[%d]", st[i]);
		// puts("");
		if (f) {
			puts("-1");
			continue;
		}
		dp[1][0] = 1;
		for (int ck = 0; ck <= k; ck++)
			for (int i = 1; i <= n; i++)
				for (int j = (x = st[i])[g.head], nx; j; j = g.e[j].next) {
					int ofs = g.e[j].w - ((nx = g.e[j].to)[dis] - x[dis]);
					if (ck + ofs <= k)
						dp[nx][ck + ofs] = (dp[nx][ck + ofs] + dp[x][ck]) % P;
				}
		for (int i = 0; i <= k; i++) ans = (ans + dp[n][i]) % P;
		printf("%d\n", ans);
	}
}