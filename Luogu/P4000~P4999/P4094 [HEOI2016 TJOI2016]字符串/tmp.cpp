#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 2e5 + 52, LN = 18;

struct graph {
	struct edge {
		int to, next;
	} e[N];
	int head[N], cnt;
	void operator()(int x, int y) { e[++cnt] = (edge){y, x[head]}, x[head] = cnt; }
};

struct lift {
	int fa[N][LN];
	void dfs(const graph& g, int x) {
		for (int i = x[g.head], nx; i; i = g.e[i].next)
			dfs(g, nx = g.e[i].to), nx[fa][0] = x;
	}
	void build(const graph& g, int n) {
		dfs(g, 1);
		for (int j = 1; j < LN; j++)
			for (int i = 1; i <= n; i++) i[fa][j] = i[fa][j - 1][fa][j - 1];
	}
};

struct SAM {
	int n, len[N], tr[N][27], link[N], nc, last;
	SAM() { nc = last = 1; }
	void ins(int c) {
		int cur = ++nc, p = last, q, cl;
		cur[len] = last[len] + 1;
		for (; p && !(q = p[tr][c]); p = p[link]) p[tr][c] = cur;
		if (!p)
			cur[link] = 1;
		else if (p[len] + 1 == q[len])
			cur[link] = q;
		else {
			cl = ++nc;
			cl[len] = p[len] + 1, cl[link] = q[link];
			memcpy(cl[tr], q[tr], sizeof *tr);
			for (; p && p[tr][c] == q; p = p[link]) p[tr][c] = cl;
			q[link] = cur[link] = cl;
		}
		last = cur;
	}

	int pre[N], suf[N];
	graph g;
	lift lf;
	void build(char* s) {
		n = strlen(s);
		std::reverse(s, s + n);
		pre[0] = 1;
		for (int i = 0; i < n; i++)
			ins(s[i] -= 97), suf[i + 1] = last;	 // 反串的后缀是原串的前缀
		for (int i = 2; i <= nc; i++) g(i[link], i);
		for (int i = last, nn = n; i; i = i[link])
			for (int j = 0; j < i[len] - i[link][len]; j++) pre[nn--] = i;	// 同理
		lf.build(g, nc);
		// DEBUG
		fprintf(stderr, "SAM:\n");
		for (int i = 1; i <= nc; i++)
			for (int j = 0; j < 26; j++)
				if (i[tr][j]) fprintf(stderr, "%d -> %d (%c)\n", i, i[tr][j], j + 97);
		fprintf(stderr, "link tree:\n");
		for (int i = 2; i <= nc; i++) fprintf(stderr, "%d -> %d\n", i[link], i);
		fprintf(stderr, "pre:\n");
		for (int i = 1; i <= n; i++) fprintf(stderr, "%d%c", pre[i], " \n"[i == n]);
		fprintf(stderr, "suf:\n");
		for (int i = 1; i <= n; i++) fprintf(stderr, "%d%c", suf[i], " \n"[i == n]);
		// DEBUG
	}
	int operator()(int l, int r) {
		int x = pre[n - l + 1], ll = r - l + 1;
		if (x[link][len] < ll) return x;
		for (int i = LN - 1; ~i; i--)
			if (x[lf.fa][i][link][len] >= ll) x = x[lf.fa][i];
		return x[link];
	}
} sam;

struct LCT {
#define L ch][0
#define R ch][1
	int p[N], ch[N][2], t[N], v[N], mx[N], st[N], top;
	void up(int x) { x[mx] = std::max({x[L][mx], x[R][mx], x[v]}); }
	bool c(int x) { return x[p][R] == x; }
	bool nr(int x) { return x[p][L] == x || x[p][R] == x; }
	void set(int x, int y) { x && (x[mx] = x[v] = x[t] = y); }
	void pd(int x) { x[t] && (set(x[L], x[t]), set(x[R], x[t]), x[t] = 0); }
	void rt(int x) {
		int y = x[p], z = y[p], k = c(x), w = x[ch][!k];
		(nr(y) && (z[ch][c(y)] = x)), p[p[p[ch[ch[x][!k] = y][k] = w] = y] = x] = z,
																			 up(y), up(x);
	}
	void sp(int x) {
		for (int i = st[top = 1] = x; nr(i); i = i[p]) st[++top] = i[p];
		while (top) pd(st[top--]);
		for (int y = x[p]; nr(x); rt(x), y = x[p]) nr(y) && (rt(c(x) ^ c(y) ? x : y), 0);
	}
	void ac(int x) {
		for (int i = 0; x; x = (i = x)[p]) sp(x), x[R] = i, up(x);
	}
	int qry(int x, int y) {
		if (pd(x), x[R] && x[R][mx] >= y) return qry(x[R], y);
		if (x[v] >= y) return x;
		if (x[L][mx] < y) return 0;
		return qry(x[L], y);
	}
	void dfs(const graph& g, int x) {
		for (int i = x[g.head], nx; i; i = g.e[i].next) dfs(g, nx = g.e[i].to), nx[p] = x;
	}
} lct;

struct QwQ {
	int n, a[N], b[N], pt[N], id[N], ans[N];
	void operator()(int x, int y, int z, int w) {
		n++, a[n] = x, b[n] = y, pt[n] = sam(z, w), n[id] = n;
		fprintf(stderr, "qry [%d %d %d]\n", a[n], b[n], pt[n]);
	}
	void solve() {
		lct.dfs(sam.g, 1);
		sam.len[0] = 1e9;
		std::sort(id + 1, id + n + 1, [this](int x, int y) { return x[b] < y[b]; });
		for (int i = 1, j = 1, p; i <= n; i++) {
			fprintf(stderr, "\n");
			for (; j <= b[i[id]] && j <= sam.n; j++)
				p = sam.suf[j], lct.ac(p), lct.sp(p), lct.set(p, j),
				fprintf(stderr, "set %d -- %d [%d]\n", p, 1, j);
			int l = 1, r = b[i[id]] -
						   a[i[id]];  // 不需要 +1，因为 check(r-l+1) 的时候会出奇怪的问题
#define mid (l + r) / 2
			p = i[id][pt], lct.ac(p), lct.sp(p);
			fprintf(stderr, "qry [%d %d %d]\n", a[i[id]], b[i[id]], pt[i[id]]);
			fprintf(stderr, "[%d, %d]\n", l, r);
			for (; l <= r;) {
				fprintf(stderr, "%d %d: %d, %d\n", mid, b[i[id]] - mid + 1,
						lct.qry(p, b[i[id]] - mid + 1),
						lct.qry(p, b[i[id]] - mid + 1)[sam.len]);
				if (lct.qry(p, b[i[id]] - mid + 1)[sam.len] <= mid)
					r = mid - 1;
				else
					l = mid + 1;
			}
			fprintf(stderr, "[%d, %d]\n", l, r);
			i[id][ans] = l;
		}
		for (int i = 1; i <= n; i++) printf("%d\n", i[ans]);
	}
} solver;

int n, m, a, b, c, d;
char s[N];
graph g;
int main() {
	scanf("%d%d%s", &n, &m, s);
	sam.build(s);
	for (; ~scanf("%d%d%d%d", &a, &b, &c, &d);) solver(n - b + 1, n - a + 1, c, d);
	solver.solve();
}