#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
#define L ch][0
#define R ch][1
#define mid (l + r) / 2

const int N = 2e5 + 52;

struct LCT;
struct SAM {
	int tr[N][2], link[N], len[N], pre[N], nc, sz, last;
	SAM() { nc = last = 1; }
	void ins(int c) {
		int cur = ++nc, p = last, q, cl;
		cur[len] = p[len] + 1;
		for (; p && !(q = p[tr][c]); p = p[link]) p[tr][c] = cur;
		if (!p)
			cur[link] = 1;
		else if (p[len] + 1 == q[len])
			cur[link] = q;
		else {
			cl = ++nc, cl[len] = p[len] + 1, cl[link] = q[link];
			memcpy(cl[tr], q[tr], sizeof *tr);
			for (; p && p[tr][c] == q; p = p[link]) p[tr][c] = cl;
			q[link] = cur[link] = cl;
		}
		pre[++sz] = last = cur;
	}
} sam;

int n, tr[N];
void upd(int i, int x) {
	for (i = n - i + 1; i <= n; i += i & -i) i[tr] = std::max(i[tr], x);
}
int qry(int i) {
	int r = 0;
	for (i = n - i + 1; i; i &= i - 1) r = std::max(r, i[tr]);
	return r;
}

struct LCT {
	int ch[N][2], p[N], v[N], t[N], st[N], top;
	bool nr(int x) { return x[p][L] == x || x[p][R] == x; }
	bool c(int x) { return x[p][R] == x; }
	void put(int x, int y) { x[v] = x[t] = y; }
	void pd(int x) { x[t] && (put(x[L], x[t]), put(x[R], x[t]), x[t] = 0); }
	void rt(int x) {
		int y = x[p], z = y[p], k = c(x), w = x[ch][!k];
		if (nr(y)) ch[z][c(y)] = x;
		p[p[p[ch[ch[x][!k] = y][k] = w] = y] = x] = z;
	}
	void sp(int x) {
		for (int i = st[top = 1] = x; nr(i); i = i[p]) st[++top] = i[p];
		while (top) pd(st[top--]);
		for (int y; y = x[p], nr(x); rt(x))
			if (nr(y)) rt(c(x) == c(y) ? y : x);
	}
	void ac(int x, int y) {
		int i = 0;
		for (; x; x = (i = x)[p]) {
			sp(x);
			if (x[v]) upd(x[v], x[sam.len]);
			x[R] = i;
		}
		put(i, y);
	}
} lct;

std::vector<int> q[N];
int m, l[N], ans[N];
char s[N];
int main() {
	scanf("%d%d%s", &n, &m, s + 1);
	for (int i = 1; i <= n; i++) sam.ins(s[i] - '0');
	for (int i = 2; i <= sam.nc; i++) i[lct.p] = i[sam.link];
	for (int i = 1, r; i <= m; i++) {
		scanf("%d%d", l + i, &r);
		q[r].push_back(i);
	}
	for (int i = 1; i <= n; i++) {
		lct.ac(sam.pre[i], i);
		for (int j : q[i]) ans[j] = qry(l[j]);
	}
	for (int i = 1; i <= m; i++) printf("%d\n", ans[i]);
}