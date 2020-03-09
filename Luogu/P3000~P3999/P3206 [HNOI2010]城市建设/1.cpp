#include <algorithm>
#include <cstdio>
#include <cstring>
#include <unordered_map>
#include <utility>
#include <vector>
#define L ch][0
#define R ch][1

typedef long long ll;
const int N = 2e5 + 52;

// clang-format off
namespace LCT {
int n, ch[N][2], p[N], rev[N], mx[N];
ll val[N];
void up(int x) {
	x[mx] = x;
	if (x[L][mx] > n && (x[mx] <= n || x[L][mx][val] > x[mx][val])) x[mx] = x[L][mx];
	if (x[R][mx] > n && (x[mx] <= n || x[R][mx][val] > x[mx][val])) x[mx] = x[R][mx];
}
bool c(int x) { return x[p][R] == x; }
bool nr(int x) { return x[p][L] == x || x[p][R] == x; }
void rv(int x) { std::swap(x[L], x[R]), x[rev] ^= 1; }
void pd(int x) { x[rev] && (rv(x[L]), rv(x[R]), x[rev] = 0); }
void rt(int x) {
	int y = x[p], z = y[p], k = c(x), w = ch[x][!k];
	(nr(y) && (ch[z][c(y)] = x)), p[p[p[ch[ch[x][!k] = y][k] = w] = y] = x] = z, up(y), up(x);
}
void pa(int x) { if (nr(x)) pa(x[p]); pd(x); }
void sp(int x) { pa(x); for (int y = x[p]; nr(x); rt(x), y = x[p]) if (nr(y)) rt(c(x) == c(y) ? y : x); }
void ac(int x) { for (int y = 0; x; x = (y = x)[p]) sp(x), x[R] = y, up(x); }
void mr(int x) { ac(x), sp(x), rv(x); }
void spl(int x, int y) { mr(x), ac(y), sp(y); }
#undef L
#undef R
}
// clang-format on

struct var_rec {
	int *p, v;
} st[N * 5];
int t;
void $(int& x, int y) { st[++t] = (var_rec){&x, x}, x = y; }

struct func_rec {
	void (*p)(int, int, int);
	int x, y;
} st2[N * 5];
int t2;
void $(void (*p)(int, int, int), int x, int y) { st2[++t2] = (func_rec){p, x, y}; }

void cut(int, int, int);
void lnk(int x, int y, int f = 1) {
	if (f) $(cut, x, y);
	LCT::mr(x), x[LCT::p] = y;
}
void cut(int x, int y, int f = 1) {
	if (f) $(lnk, x, y);
	LCT::spl(x, y), x[LCT::p] = y[LCT::ch][0] = 0, LCT::up(y);
}

int _p[N], _sz[N];
int f(int x) { return x[_p] ? f(x[_p]) : x; }
bool mg(int x, int y) {
	if ((x = f(x)) != (y = f(y))) {
		if (x[_sz] > y[_sz]) std::swap(x, y);
		return $(x[_p], y), $(y[_sz], x[_sz] + y[_sz]), 1;
	}
	return 0;
}

#define L (x << 1)
#define R ((x << 1) | 1)
#define mid (l + r) / 2
int n, u[N], v[N], w[N], ql, qr;
ll la;
std::vector<int> tr[N << 2];
void I(int x, int l, int r, int y) {
	if (ql <= l && r <= qr) return x[tr].push_back(y);
	if (ql <= mid) I(L, l, mid, y);
	if (mid < qr) I(R, mid + 1, r, y);
}
void D(int x, int l, int r) {
	int sz = t, sz2 = t2;
	ll ca = la;
	for (int i : x[tr]) {
		(i + n)[LCT::val] = i[w];
		if (f(i[u]) == f(i[v])) {
			LCT::spl(i[u], i[v]);
			int id = i[v][LCT::mx] - n;
			if (id[w] > i[w]) {
				cut(id[u], id + n), cut(id + n, id[v]);
				lnk(i[u], i + n), lnk(i + n, i[v]);
				ca += i[w] - id[w];
			}
		} else {
			lnk(i[u], i + n), lnk(i + n, i[v]);
			ca += i[w], mg(i[u], i[v]);
		}
	}
	if (l == r)
		printf("%lld\n", ca);
	else
		std::swap(ca, la), D(L, l, mid), D(R, mid + 1, r), std::swap(ca, la);
	for (; t > sz; t--) *st[t].p = st[t].v;
	for (; t2 > sz2; t2--) st2[t2].p(st2[t2].x, st2[t2].y, 0);
}

std::unordered_map<int, int> mp;
int m, q, x, y, tm[N], col[N];
signed main() {
	scanf("%d%d%d", &n, &m, &q), LCT::n = n;
	for (int i = 1; i <= n; i++) i[_sz] = 1;
	for (int i = 1; i <= m; i++)
		scanf("%d%d%d", u + i, v + i, w + i), i[tm] = 1, mp[i] = i;
	for (int i = m + 1, id; i <= m + q; i++) {
		scanf("%d%d", &x, &y), id = mp[x];
		if (id[tm] < i - m) ql = id[tm], qr = i - m - 1, I(1, 1, q, id);
		i[u] = id[u], i[v] = id[v], i[w] = y, i[tm] = i - m, mp[x] = i;
	}
	for (int i = 1; i <= m; i++) ql = mp[i][tm], qr = q, I(1, 1, q, mp[i]);
	D(1, 1, q);
}