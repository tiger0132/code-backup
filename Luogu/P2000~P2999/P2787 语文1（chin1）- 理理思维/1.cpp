// mmp，毒瘤出题人

#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>

const int N = 2e5 + 52;

#define L ch][0
#define R ch][1
#define Lc x[L], l, mid, ql, qr
#define Rc x[R], mid + 1, r, ql, qr
#define Rt 1, 1, n
int ch[N][2], s[N][26], sz[N], t[N][26], nc = 1;
void up(int i, int x) { x[s][i] = x[L][s][i] + x[R][s][i]; }
void put(int i, int x, int v) { x[t][i] = v, x[s][i] = x[sz] * v; }
void pd(int i, int x) {
	if (~x[t][i]) put(i, x[L], x[t][i]), put(i, x[R], x[t][i]), x[t][i] = -1;
}
void build(int x, int l, int r, char *str) {
	memset(x[t], -1, sizeof(x[t])), x[sz] = r - l + 1;
	if (l == r) return void(x[s][toupper(str[l]) - 'A'] = 1);
	int mid = (l + r) / 2;
	build(x[L] = ++nc, l, mid, str), build(x[R] = ++nc, mid + 1, r, str);
	for (int i = 0; i < 26; i++) up(i, x);
}
void set(int i, int x, int l, int r, int ql, int qr, int y) {
	if (ql <= l && r <= qr) return put(i, x, y);
	pd(i, x);
	int mid = (l + r) / 2;
	if (ql <= mid) set(i, Lc, y);
	if (mid < qr) set(i, Rc, y);
	up(i, x);
}
int qry(int i, int x, int l, int r, int ql, int qr) {
	if (ql <= l && r <= qr) return x[s][i];
	pd(i, x);
	int mid = (l + r) / 2;
	if (qr <= mid) return qry(i, Lc);
	if (mid < ql) return qry(i, Rc);
	return qry(i, Lc) + qry(i, Rc);
}
void qry(int x, int l, int r, int ql, int qr, int *ans) {
	if (ql <= l && r <= qr) {
		for (int i = 0; i < 26; i++) ans[i] += x[s][i], put(i, x, 0);
		return;
	}
	for (int i = 0; i < 26; i++) pd(i, x);
	int mid = (l + r) / 2;
	if (ql <= mid) qry(Lc, ans);
	if (mid < qr) qry(Rc, ans);
	for (int i = 0; i < 26; i++) up(i, x);
}

int n, m, op, x, y, c[26];
char str[N], z[2];
int main() {
	scanf("%d%d%s", &n, &m, str + 1);
	build(Rt, str);
	while (m--) {
		scanf("%d%d%d", &op, &x, &y);
		if (op == 3) {
			memset(c, 0, sizeof c), qry(Rt, x, y, c);
			for (int i = 0, p = x; i < 26; p += c[i++])
				if (c[i]) set(i, Rt, p, p + c[i] - 1, 1);
		} else {
			scanf("%s", z), *z = toupper(*z);
			if (op == 1) printf("%d\n", qry(*z - 'A', Rt, x, y));
			if (op == 2) {
				for (int i = 0; i < 26; i++) set(i, Rt, x, y, 0);
				set(*z - 'A', Rt, x, y, 1);
			}
		}
	}
}