#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e5 + 51;

// clang-format off
#define L(x) ch[x][0]
#define R(x) ch[x][1]
struct LCT {
	int p[N], ch[N][2], r[N], v[N], lc[N], rc[N], s[N], t[N], st[N], top;
	void up(int x) {
		lc[x] = L(x) ? lc[L(x)] : v[x], rc[x] = R(x) ? rc[R(x)] : v[x];
		if (L(x) && R(x)) s[x] = s[L(x)] + s[R(x)] - (rc[L(x)] == v[x]) - (lc[R(x)] == v[x]) + 1;
		else if (L(x)) s[x] = s[L(x)] + (rc[L(x)] != v[x]);
		else if (R(x)) s[x] = s[R(x)] + (lc[R(x)] != v[x]);
		else s[x] = 1;
	}
	bool c(int x) { return R(p[x]) == x; }
	bool nr(int x) { return L(p[x]) == x || R(p[x]) == x; }
	void rv(int x) { r[x] ^= 1, std::swap(L(x), R(x)), std::swap(lc[x], rc[x]); }
	void cl(int x, int y) { t[x] = v[x] = lc[x] = rc[x] = y, s[x] = 1; }
	void pd(int x) { r[x] && (rv(L(x)), rv(R(x)), r[x] = 0), t[x] && (cl(L(x), t[x]), cl(R(x), t[x]), t[x] = 0); }
	void rt(int x) {
		int y = p[x], z = p[y], k = c(x), w = ch[x][!k];
		ch[y][k] = w, p[w] = y, (nr(y) && (ch[z][c(y)] = x)), p[x] = z, ch[x][!k] = y, p[y] = x, up(y), up(x);
	}
	void sp(int x) {
		for (int i = st[top = 1] = x; nr(i); i = p[i]) st[++top] = p[i];
		while (top) pd(st[top--]);
		for (int y = p[x]; nr(x); rt(x), y = p[x]) nr(y) && (rt(c(x) == c(y) ? y : x), 0);
	}
	void ac(int x) { for (int i = 0; x; x = p[i = x]) sp(x), R(x) = i, up(x); }
	void mr(int x) { ac(x), sp(x), rv(x); }
	void spl(int x, int y) { mr(x), ac(y), sp(y); }
	void lnk(int x, int y) { mr(x), p[x] = y; }
} lct;
// clang-format on

int n, m, x, y, z;
char op[2];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", &x), lct.lc[i] = lct.rc[i] = lct.v[i] = x, lct.s[i] = 1;
	for (int i = 1; i < n; i++) scanf("%d%d", &x, &y), lct.lnk(x, y);
	while (m--) {
		scanf("%s%d%d", op, &x, &y);
		lct.spl(x, y);
		if (*op == 'C')
			scanf("%d", &z), lct.cl(y, z);
		else
			printf("%d\n", lct.s[y]);
	}
}