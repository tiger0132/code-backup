#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
#include <queue>
#include <stack>
#include <vector>
#define int ll

void fuck(bool exp) {
	while (!exp) exp = 0;
}

typedef long long ll;
const int N = 3e4 + 43, M = 2e6 + 62, K = 2e3 + 32;
struct {
	struct edge {
		int to, next, w;
	} e[M << 1];
	int head[N], cnt = 1;
	void operator()(int x, int y, int z) {
		fuck(cnt <= 3e6);
		e[++cnt] = {y, x[head], 0}, x[head] = cnt;
		e[++cnt] = {x, y[head], z}, y[head] = cnt;
	}
	int lv[N];
	bool bfs(int s, int t) {
		memset(lv, 0, sizeof lv), s[lv] = 1;
		std::queue<int> q;
		for (q.push(s); !q.empty(); q.pop())
			for (int x = q.front(), i = x[head], nx; i; i = e[i].next)
				if (!(nx = e[i].to)[lv] && e[i ^ 1].w) q.push(nx), nx[lv] = x[lv] + 1;
		return t[lv];
	}
	int dfs(int s, int t, int f) {
		if (s == t || !f) return f;
		int r = 0;
		for (int i = s[head], nx, w; f && i; i = e[i].next)
			if ((nx = e[i].to)[lv] == s[lv] + 1 && e[i ^ 1].w)
				w = dfs(nx, t, std::min(f, e[i ^ 1].w)), e[i].w += w, e[i ^ 1].w -= w,
				r += w, f -= w;
		return (f && (s[lv] = 0)), r;
	}
	ll dinic(int s, int t) {
		ll r = 0;
		while (bfs(s, t)) r += dfs(s, t, 1e9);
		return r;
	}
} f;

struct {
	struct edge {
		int to, next;
	} e[M << 1];
	int head[N], cnt = 1;
	void operator()(int x, int y) {
		fuck(cnt <= 3e6);
		e[++cnt] = {y, x[head]}, x[head] = cnt;
		e[++cnt] = {x, y[head]}, y[head] = cnt;
	}
} g;

std::stack<int> st;
bool v[N], R[N];
bool dfs(int x, int p) {
	if (x[v]) {
		for (int y = 0; y != x; st.pop()) (y = st.top())[R] = true;
		return true;
	}
	st.push(x), x[v] = true;
	for (int i = x[g.head]; i; i = g.e[i].next)
		if (i != (p ^ 1) && dfs(g.e[i].to, i)) return true;
	return st.pop(), false;
}

std::map<int, int> mp;
int id(int x) {
	if (!mp.count(x)) return mp[x] = (int)mp.size() + 1;
	return mp[x];
}

int n, k, x, y, z, c[N], l[K], ans[K][2], cntR;
std::vector<int> a[K], worker[N], idx[K];
int S, S0, T, edge[N], material[N], nc;

// bool vis[K][K];
int aaaa[K];
signed main() {
	// freopen("1.in", "r", stdin);
	scanf("%lld%lld", &n, &k);
	S = 1, S0 = 2, T = 3, nc = 3;
	for (int i = 1; i <= n; edge[i] = ++nc, g(i++, x))
		for (scanf("%lld%lld", &x, &y), l[i] = x; y--;) {
			scanf("%lld", &z), z = id(z);
			// vis[i][z] = 1;
			a[i].push_back(z);
		}
	for (int i = 1; i <= k; i++)
		scanf("%lld", &x), x = id(x), /*aaaa[i] = x, */ worker[x].push_back(i), c[x]++;
	for (int i = 1; i <= (int)mp.size(); i++) material[i] = ++nc;
	fuck(nc <= 2e4);
	dfs(1, 0);
	for (int i = 1; i <= n; i++)
		if (!i[R]) {
			f(S, edge[i], 1);
			for (int j : a[i]) f(edge[i], material[j], 1), idx[i].push_back(f.cnt - 1);
		} else {
			cntR++;
			f(S0, edge[i], 1);
			for (int j : a[i]) f(edge[i], material[j], 1), idx[i].push_back(f.cnt - 1);
		}
	for (int i = 1; i <= (int)mp.size(); i++) f(material[i], T, c[i]);
	f(S, S0, cntR - 1);
	if (f.dinic(S, T) < n - 1) return puts("-1"), 0;
	for (int i = 1; i <= n; i++)
		for (int jj = 0; jj < a[i].size(); jj++) {
			x = idx[i][jj];
			int j = a[i][jj];
			if (f.e[x].w) {
				z = worker[j].back(), worker[j].pop_back();
				z[ans][0] = i, z[ans][1] = l[i];
			}
		}
	// bool f1 = 1;
	// int count = 0;
	for (int i = 1; i <= k; i++) {
		printf("%lld %lld\n", ans[i][0], ans[i][1]);
		// if (ans[i][0]) f1 &= vis[ans[i][0]][aaaa[i]], count++;
	}
	// while (!f1 || count != n - 1)
	// 	;
}