// luogu-judger-enable-o2
#include <algorithm>
#include <cstdio>
#include <cstring>

typedef unsigned long long u;
const int N = 1e5 + 51;
#define int u

// clang-format off
#define L ch][0
#define R ch][1
struct _{u x,y;};
int p[N], ch[N][2], op[N], r[N], st[N], top; _ sf[N], sb[N]; u v[N];
_ $(_ y, _ *a, int x) { return {(y.x | x[a].x) ^ x[a].y, (y.y | x[a].x) ^ x[a].y}; }
_ $(_ val, int x) {
    if (x[op] == 1) return {val.x & x[v], val.y & x[v]};
    if (x[op] == 2) return {val.x | x[v], val.y | x[v]};
    return {val.x ^ x[v], val.y ^ x[v]};
}
void up(int x) {
    static _ forw, bakw;
    forw = $($($({0, -1ull}, sf, x[L]), x), sf, x[R]);
    bakw = $($($({0, -1ull}, sb, x[R]), x), sb, x[L]);
    x[sf] = {~(forw.x ^ forw.y), ~forw.y}, x[sb] = {~(bakw.x ^ bakw.y), ~bakw.y};
}
bool c(int x) { return x[p][R] == x; }
bool nr(int x) { return x[p][L] == x || x[p][R] == x; }
void rv(int x) { std::swap(x[L], x[R]), std::swap(x[sf], x[sb]), x[r] ^= 1; }
void pd(int x) { x[r] && (rv(x[L]), rv(x[R]), x[r] = 0); }
void rt(int x) {
    int y = x[p], z = y[p], k = c(x), w = x[ch][!k];
    (nr(y) && (z[ch][c(y)] = x)), p[p[p[ch[ch[x][!k] = y][k] = w] = y] = x] = z, up(y), up(x);
}
void sp(int x) {
    for (int i = st[top = 1] = x; nr(i); i = i[p]) st[++top] = i[p];
    while (top) pd(st[top--]);
    for (int y = x[p]; nr(x); rt(x), y = x[p]) nr(y) && (rt(c(x) ^ c(y) ? x : y), 0);
}
void ac(int x) { for (int i = 0; x; x = (i = x)[p]) sp(x), x[R] = i, up(x); }
void mr(int x) { ac(x), sp(x), rv(x); }
void spl(int x, int y) { mr(x), ac(y), sp(y); }
void lnk(int x, int y) { mr(x), x[p] = y, up(y); }
// clang-format on

int k;
u calc(u _or, u _xor, u m) {
	u t0 = _or ^ _xor, t1 = -1ull ^ _xor, ans = 0;
	for (u i = 1ull << 63; i; i >>= 1) {
		if (!(t0 & i) && (t1 & i) && m >= i) ans += i, m -= i;
		if (t0 & i) ans += i;
	}
	return ans;
}

int n, m, _op, x, y, z;
signed main() {
	scanf("%llu%llu%llu", &n, &m, &k);
	for (int i = 1; i <= n; i++) scanf("%llu%llu", i + op, i + v), up(i);
	for (int i = 1; i < n; i++) scanf("%llu%llu", &x, &y), lnk(x, y);
	while (m--) {
		scanf("%llu%llu%llu%llu", &_op, &x, &y, &z);
		if (_op == 1)
			spl(x, y), printf("%llu\n", calc(y[sf].x, y[sf].y, z));
		else
			mr(x), x[op] = y, x[v] = z, up(x);
	}
}