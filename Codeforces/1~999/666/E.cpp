#include <algorithm>
#include <cassert>
#include <cstdio>
#include <cstring>
#include <vector>
#define L ch][0
#define R ch][1
#define mid (l + r) / 2

const int N = 5e5 + 55, LN = 17, M = 2e7 + 72, mmp = 5e5 + 55;

struct pii {
	int x, id;
	bool operator<(const pii &rhs) const {
		return x < rhs.x || (x == rhs.x && id > rhs.id);
	}
};
struct SGT {
	int ch[M][2], nc;
	pii mx[M];
	void up(int x) { x[mx] = std::max(x[L][mx], x[R][mx]); }
	void upd(int &x, int l, int r, int v) {
		if (!x) x = ++nc;
		if (l == r) return x[mx].x++, x[mx].id = l, void();
		if (v <= mid) return upd(x[L], l, mid, v), up(x);
		return upd(x[R], mid + 1, r, v), up(x);
	}
	int mg(int x, int y, int l, int r) {
		if (!x || !y) return x | y;
		int cur = ++nc;
		if (l == r) {
			cur[mx] = {x[mx].x + y[mx].x, x[mx].id};
			return cur;
		}
		cur[L] = mg(x[L], y[L], l, mid);
		cur[R] = mg(x[R], y[R], mid + 1, r);
		return up(cur), cur;
	}
	pii qry(int x, int l, int r, int ql, int qr) {
		if (!x) return {};
		if (ql <= l && r <= qr) return x[mx];
		if (qr <= mid) return qry(x[L], l, mid, ql, qr);
		if (mid < ql) return qry(x[R], mid + 1, r, ql, qr);
		return std::max(qry(x[L], l, mid, ql, qr), qry(x[R], mid + 1, r, ql, qr));
	}
} sgt;

int m;
struct SAM {
	int tr[N][26], link[N], len[N], rt[N], fa[N][LN], nc, last, id;
	std::vector<int> g[N];
	SAM() { nc = last = 1; }
	void ins(int c) {
		int cur = ++nc, p = last, q, cl;
		sgt.upd(cur[rt], 1, m, id);
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
		last = 1, id++;
		for (int i = 0; i < n; i++) ins(s[i] - 97);
	}
	void dfs(int x) {
		for (int nx : x[g]) {
			nx[fa][0] = x;
			for (int i = 1; i < LN; i++) nx[fa][i] = nx[fa][i - 1][fa][i - 1];
			dfs(nx);
			x[rt] = sgt.mg(x[rt], nx[rt], 1, m);
		}
	}
	void build() {
		for (int i = 2; i <= nc; i++) i[link][g].push_back(i);
		dfs(1);
	}
	void exec(char *s, std::vector<int> &v, std::vector<int> &pt) {
		int n = strlen(s), x = 1, l = 0;
		for (int i = 0; i < n; i++) {
			int nx = s[i] - 'a';
			if (x[tr][nx])
				l++, x = x[tr][nx];
			else {
				while (x > 1 && !x[tr][nx]) x = x[link];
				if (x[tr][nx])
					l = x[len] + 1, x = x[tr][nx];
				else
					l = 0;
			}
			v.push_back(l);
			pt.push_back(x);
		}
	}
	int get(int x, int l) {
		for (int i = LN - 1; i >= 0; i--)
			if (x[fa][i][len] >= l) x = x[fa][i];
		return x;
	}
} sam;

std::vector<int> g[N], len, pt;
int q, a, b, c, d;
char s[mmp], t[N];
int main() {
	scanf("%s%d", s, &m);
	for (int i = 1; i <= m; i++) {
		scanf("%s", t);
		sam += t;
	}
	sam.exec(s, len, pt);
	assert(sgt.nc < M);	 // wdnmd
	assert(sam.nc < N);	 // wdnmd
	sam.build();
	scanf("%d", &q);
	for (int i = 1; i <= q; i++) {
		scanf("%d%d%d%d", &a, &b, &c, &d);

		if (d - c + 1 > len[d - 1]) {
			printf("%d 0\n", a);
			continue;
		}
		int p = sam.get(pt[d - 1], d - c + 1);
		pii ans = sgt.qry(p[sam.rt], 1, m, a, b);
		if (!ans.x) ans.id = a;
		printf("%d %d\n", ans.id, ans.x);
	}
}