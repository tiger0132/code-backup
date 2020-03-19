#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long L;
const int N = 6e5 + 56, INF = 1e9;

struct rec {
	int mx1, mx2, mn1, mn2;
	void operator+=(const rec& rhs) {
		rhs.mx1 > mx1 ? mx2 = mx1, mx1 = rhs.mx1 : rhs.mx1 > mx2 && (mx2 = rhs.mx1);
		rhs.mx2 > mx1 ? mx2 = mx1, mx1 = rhs.mx2 : rhs.mx2 > mx2 && (mx2 = rhs.mx2);
		rhs.mn1 < mn1 ? mn2 = mn1, mn1 = rhs.mn1 : rhs.mn1 < mn2 && (mn2 = rhs.mn1);
		rhs.mn2 < mn1 ? mn2 = mn1, mn1 = rhs.mn2 : rhs.mn2 < mn2 && (mn2 = rhs.mn2);
	}
};
struct graph {
	struct edge {
		int to, next;
	} e[N];
	int head[N], cnt;
	void operator()(int x, int y) { e[++cnt] = (edge){y, x[head]}, x[head] = cnt; }
};
struct SAM {
	int len[N], link[N], tr[N][26], cnt[N], nc, last;
	rec v[N];
	SAM() { nc = last = 1; }
	void ins(int c, int w) {
		int cur = ++nc, p = last, q, cl;
		cur[len] = last[len] + 1;
		for (; p && !(q = p[tr][c]); p = p[link]) p[tr][c] = cur;
		if (!p)
			cur[link] = 1;
		else if (p[len] + 1 == q[len])
			cur[link] = q;
		else {
			cl = ++nc;
			cl[v] = {-INF, -INF, INF, INF};
			cl[len] = p[len] + 1, cl[link] = q[link];
			memcpy(cl[tr], q[tr], sizeof *tr);
			for (; p && p[tr][c] == q; p = p[link]) p[tr][c] = cl;
			q[link] = cur[link] = cl;
		}
		cur[cnt] = 1, cur[v] = {w, -INF, w, INF}, last = cur;
	}

	graph g;
	L ans1[N], ans2[N];
	void dfs(int x) {
		for (int i = x[g.head], nx; i; i = g.e[i].next) {
			dfs(nx = g.e[i].to), x[v] += nx[v];
			x[len][ans1] += 1ll * x[cnt] * nx[cnt];
			x[cnt] += nx[cnt];
		}
		if (x[cnt] >= 2)
			x[len][ans2] = std::max(x[len][ans2], std::max(1ll * x[v].mx1 * x[v].mx2,
														   1ll * x[v].mn1 * x[v].mn2));
	}
	void solve(int n) {
		for (int i = 2; i <= nc; i++) g(i[link], i);
		memset(ans2, 0xc0, sizeof ans2);
		1 [v] = {-INF, -INF, INF, INF};
		dfs(1);
		for (int i = n - 1; ~i; i--)
			i[ans1] += (i + 1)[ans1], i[ans2] = std::max(i[ans2], (i + 1)[ans2]);
		for (int i = 0; i < n; i++) printf("%lld %lld\n", i[ans1], !!i[ans1] * i[ans2]);
	}
} sam;

int n, a[N];
char s[N];
int main() {
	scanf("%d%s", &n, s);
	for (int i = 0; i < n; i++) scanf("%d", a + i);
	for (int i = n - 1; ~i; i--) sam.ins(s[i] - 97, a[i]);
	sam.solve(n);
}