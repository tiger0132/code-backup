#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

typedef std::pair<int, int> pii;
const int N = 1e5 + 51, LN = 18;

std::vector<int> g[N];
struct {
	int occ[N << 1], dep[N], idx;
	pii st[N << 1][LN];
	void dfs2(int x, int p = 0, int d = 0) {
		st[x[occ] = ++idx][0] = {d, x}, x[dep] = d;
		for (int nx : x[g])
			if (nx != p) dfs2(nx, x, d + 1), st[++idx][0] = {d, x};
	}
	void init() {
		dfs2(1);
		for (int j = 1; (1 << j) <= idx; j++)
			for (int i = 1; i + (1 << j) - 1 <= idx; i++)
				st[i][j] = std::min(st[i][j - 1], st[i + (1 << (j - 1))][j - 1]);
	}
	int lca(int x, int y) {
		int l = x[occ], r = y[occ];
		if (l > r) std::swap(l, r);
		int k = 31 - __builtin_clz(r - l + 1);
		return std::min(st[l][k], st[r - (1 << k) + 1][k]).second;
	}
	inline int operator()(int x, int y) { return x[dep] + y[dep] - 2 * lca(x, y)[dep]; }
} dist;

struct {
	std::priority_queue<int> pq, rm;
	int top() {
		while (!pq.empty() && !rm.empty() && pq.top() == rm.top()) pq.pop(), rm.pop();
		return pq.size() ? pq.top() : -1e9;
	}
	void pop() {
		while (!pq.empty() && !rm.empty() && pq.top() == rm.top()) pq.pop(), rm.pop();
		pq.pop();
	}
	inline void erase(int x) { rm.push(x); }
	inline void push(int x) { pq.push(x); }
	inline int size() { return pq.size() - rm.size(); }
	inline int stop2() {
		int r = top(), x = top();
		pop(), r += top(), push(x);
		return r;
	}
} dis[N], ch[N], ans;

int mx[N], sz[N], p[N], rt;
bool vis[N];
void dfs2(int x, int p, int sum) {
	x[sz] = 1, x[mx] = 0;
	for (int nx : x[g])
		if (!nx[vis] && nx != p) {
			dfs2(nx, x, sum), x[sz] += nx[sz];
			x[mx] = std::max(x[mx], nx[sz]);
		}
	x[mx] = std::max(x[mx], sum - x[sz]);
	if (!rt || x[mx] < rt[mx]) rt = x;
}
void dfs(int x, int p, int d, int t) {
	dis[t].push(d);
	for (int nx : x[g])
		if (!nx[vis] && nx != p) dfs(nx, x, d + 1, t);
}
void divi(int x, int sum) {
	x[vis] = true;
	for (int nx : x[g])
		if (!nx[vis]) {
			int ns = nx[sz] < x[sz] ? nx[sz] : sum - x[sz];
			rt = 0, dfs2(nx, x, ns);
			dfs(nx, x, 1, rt);
			ch[x].push(dis[rt].top());
			rt[p] = x, divi(rt, ns);
		}
	ch[x].push(0);
	if (ch[x].size() > 1)
		ans.push(ch[x].stop2());
	else if (ch[x].size())
		ans.push(ch[x].top());
}
void add(int x) {
	if (ch[x].size() > 1) ans.erase(ch[x].stop2());
	ch[x].push(0);
	if (ch[x].size() > 1) ans.push(ch[x].stop2());
	for (int cur = x, f; f = cur[p]; cur = f) {
		if (ch[f].size() > 1) ans.erase(ch[f].stop2());
		if (dis[cur].size()) ch[f].erase(dis[cur].top());
		dis[cur].push(dist(x, f));
		ch[f].push(dis[cur].top());
		if (ch[f].size() > 1) ans.push(ch[f].stop2());
	}
}
void del(int x) {
	if (ch[x].size() > 1) ans.erase(ch[x].stop2());
	ch[x].erase(0);
	if (ch[x].size() > 1) ans.push(ch[x].stop2());
	for (int cur = x, f; f = cur[p]; cur = f) {
		if (ch[f].size() > 1) ans.erase(ch[f].stop2());
		ch[f].erase(dis[cur].top());
		dis[cur].erase(dist(x, f));
		if (dis[cur].size()) ch[f].push(dis[cur].top());
		if (ch[f].size() > 1) ans.push(ch[f].stop2());
	}
}

int n, m, x, y, col[N];
char op[2];
int main() {
	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		scanf("%d%d", &x, &y);
		x[g].push_back(y);
		y[g].push_back(x);
	}
	dist.init();
	dfs2(1, 0, n);
	divi(rt, n);
	for (int i = 1; i <= n; i++) i[col] = 1;
	for (scanf("%d", &m); m--;) {
		scanf("%s", op);
		if (*op == 'G')
			printf("%d\n", ans.size() ? ans.top() : -1);
		else {
			scanf("%d", &x);
			x[col] ? del(x) : add(x);
			x[col] ^= 1;
		}
	}
}