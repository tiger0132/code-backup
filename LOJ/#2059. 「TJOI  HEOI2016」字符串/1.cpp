#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
#define L ch][0
#define R ch][1
#define mid (l + r) / 2

const int N = 2e5 + 52, K = 3e6 + 63, LN = 21;

std::vector<int> g[N];
struct SAM {
	int len[N], link[N], tr[N][26], pre[N], nc, last;
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
		last = cur;
	}
	void operator+=(char *s) {
		int n = strlen(s);
		for (int i = 0; i < n; i++) ins(s[i] - 97), pre[i + 1] = last;
	}
	void build() {
		for (int i = 2; i <= nc; i++) i[link][g].push_back(i);
	}
} sam;

int ch[K][2], sz[K], nc;
int cl(int x) { return (++nc)[L] = x[L], nc[R] = x[R], nc[sz] = x[sz], nc; }
void ins(int x, int l, int r, int i) {
	if (x[sz]++, l == r) return;
	if (i <= mid) return ins(x[L] = cl(x[L]), l, mid, i);
	ins(x[R] = cl(x[R]), mid + 1, r, i);
}
int qry(int x1, int x2, int l, int r, int ql, int qr) {
	if (ql <= l && r <= qr) return x2[sz] - x1[sz];
	if (qr <= mid) return qry(x1[L], x2[L], l, mid, ql, qr);
	if (mid < ql) return qry(x1[R], x2[R], mid + 1, r, ql, qr);
	return qry(x1[L], x2[L], l, mid, ql, qr) + qry(x1[R], x2[R], mid + 1, r, ql, qr);
}
int rt[N];

int dfn[N], rb[N], fa[N][LN], idx;
void dfs(int x) {
	x[dfn] = ++idx;
	for (int nx : x[g]) {
		nx[fa][0] = x;
		for (int i = 1; i < LN; i++) nx[fa][i] = nx[fa][i - 1][fa][i - 1];
		dfs(nx);
	}
	x[rb] = idx;
}
bool check(int a, int b, int c, int d) {
	int x = sam.pre[d];
	for (int i = LN - 1; i >= 0; i--)
		if (x[fa][i][sam.len] >= c) x = x[fa][i];
	return !!qry(rt[a - 1], rt[b], 1, sam.nc, x[dfn], x[rb]);
}

int n, m, a, b, c, d;
char s[N];
int main() {
	scanf("%d%d%s", &n, &m, s);
	std::reverse(s, s + n);
	sam += s;
	sam.build();
	dfs(1);
	for (int i = 1; i <= n; i++) {
		ins(rt[i] = cl(rt[i - 1]), 1, sam.nc, sam.pre[i][dfn]);
	}
	while (m--) {
		scanf("%d%d%d%d", &b, &a, &d, &c);
		a = n - a + 1, b = n - b + 1;
		c = n - c + 1, d = n - d + 1;
		int l = 1, r = std::min(d - c + 1, b - a + 1);
		while (l <= r)
			if (check(a + mid - 1, b, mid, d))
				l = mid + 1;
			else
				r = mid - 1;
		printf("%d\n", r);
	}
}