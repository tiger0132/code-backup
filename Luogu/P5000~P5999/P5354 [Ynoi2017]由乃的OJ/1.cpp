#include <algorithm>
#include <cctype>
#include <cstdio>

typedef unsigned long long u;
const int N = 1e5 + 51;

// clang-format off
char B[1 << 15], *S = B, *T = B;
inline char getcharx() { return S == T && (T = (S = B) + fread(B, 1, 1 << 15, stdin), S == T) ? 0 : *S++; }
template <typename T> inline void get(T& val) {
	static char ch;
	val = 0;
	while (!isdigit(ch = getcharx()));
	do val = val * 10 + ch - 48; while (isdigit(ch = getcharx()));
}
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
	_ forw = $($($({0, -1ull}, sf, x[L]), x), sf, x[R]);
	_ bakw = $($($({0, -1ull}, sb, x[R]), x), sb, x[L]);
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
	for (int i = st[top = 1] = x; i; i = i[p]) st[++top] = i[p];
	while (top) pd(st[top--]);
	for (int y = x[p]; nr(x); rt(x), y = x[p]) nr(y) && (rt(c(x) ^ c(y) ? x : y), 0);
}
void ac(int x) { for (int i = 0; x; x = (i = x)[p]) sp(x), x[R] = i, up(x); }
void mr(int x) { ac(x), sp(x), rv(x); }
void spl(int x, int y) { mr(x), ac(y), sp(y); }
void lnk(int x, int y) { mr(x), x[p] = y, up(y); }
// clang-format on

u k;
u calc(u _or, u _xor, u m) {
	u t0 = _or ^ _xor, t1 = -1ull ^ _xor, ans = 0;
	for (u i = k; i; i >>= 1) {
		if (!(t0 & i) && (t1 & i) && m >= i) ans += i, m -= i;
		if (t0 & i) ans += i;
	}
	return ans;
}

int n, m, _op, x, y;
u z;
signed main() {
	get(n), get(m), get(k);
	k = 1ull << (k - 1);
	for (int i = 1; i <= n; i++) get(i[op]), get(i[v]), up(i);
	for (int i = 1; i < n; i++) get(x), get(y), lnk(x, y);
	while (m--) {
		get(_op), get(x), get(y), get(z);
		if (_op == 1)
			spl(x, y), printf("%llu\n", calc(y[sf].x, y[sf].y, z));
		else
			mr(x), x[op] = y, x[v] = z, up(x);
	}
}