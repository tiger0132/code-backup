#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>

// clang-format off
#define L ch][0
#define R ch][1
const int N = 1e6 + 61;
int ch[N][2], v[N], pri[N], la[N], ra[N], gss[N], s[N], sz[N], set[N], r[N], nc, rt;
std::queue<int> q;
int alloc(int y) {
	int x; if (q.empty()) x = ++nc; else x = q.front(), q.pop();
	return x[L] = x[R] = 0, x[v] = x[s] = x[gss] = y, x[la] = x[ra] = std::max(0, y),
		   x[set] = 1e6, x[r] = 0, x[sz] = 1, x[pri] = rand(), x;
}
void up(int x) {
	x[sz] = x[L][sz] + x[R][sz] + 1, x[s] = x[L][s] + x[R][s] + x[v];
	x[la] = std::max(x[L][la], x[L][s] + x[v] + x[R][la]);
	x[ra] = std::max(x[L][ra] + x[v] + x[R][s], x[R][ra]);
	x[gss] = std::max({x[L][gss], x[R][gss], x[L][ra] + x[v] + x[R][la]});
}
void put(int x, int y) {
	if (x) x[set] = y, x[v] = y, x[la] = x[ra] = std::max(0, x[s] = x[sz] * y), x[gss] = x[v] < 0 ? x[v] : 0;
}
void rv(int x) { std::swap(x[L], x[R]), std::swap(x[la], x[ra]), x[r] ^= 1; }
void pd(int x) {
	if (x[set] != 1e6) put(x[L], x[v]), put(x[R], x[v]), x[set] = 1e6, x[r] = 0; if (x[r]) rv(x[L]), rv(x[R]), x[r] = 0;
}
void spl(int id, int k, int& x, int& y) {
	if (!id) return void(x = y = 0);
	pd(id);
	if (id[L][sz] < k) return x = id, spl(id[R], k - id[L][sz] - 1, x[R], y), up(x);
	y = id, spl(id[L], k, x, y[L]), up(y);
}
int u(int x, int y) {
	if (!x || !y) return x | y;
	pd(x), pd(y);
	if (x[pri] < y[pri]) return pd(x), x[R] = u(x[R], y), up(x), x;
	return pd(y), y[L] = u(x, y[L]), up(y), y;
}
int build(int l, int r, int* a) {
	if (l > r) return 0;
	int mid = (l + r) / 2, x = alloc(a[mid]);
	return x[L] = build(l, mid - 1, a), x[R] = build(mid + 1, r, a), up(x), x;
}
void rm(int x) {q.push(x); if (x[L]) rm(x[L]); if (x[R]) rm(x[R]); }
// clang-format on

int n, x, y, z, a, b, c, ar[N];
char op[11];
int main() {
	scanf("%d%*d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", ar + i);
	0 [gss] = -1e6;
	rt = build(1, n, ar);
	while (~scanf("%s", op))
		if (op[2] == 'X')
			printf("%d\n", rt[gss]);
		else {
			scanf("%d%d", &x, &y);
			if (op[2] == 'S') {
				memset(ar, 0, sizeof ar);
				for (int i = 1; i <= y; i++) scanf("%d", ar + i);
				b = build(1, y, ar);
				spl(rt, x, a, c);
				rt = u(u(a, b), c);
			} else {
				spl(rt, x - 1, a, b);
				spl(b, y, b, c);
				if (op[2] == 'T') printf("%d\n", b[s]);
				if (op[2] == 'V') rv(b);
				if (op[2] == 'K') scanf("%d", &z), put(b, z);
				if (op[2] == 'L')
					rm(b), rt = u(a, c);
				else
					rt = u(u(a, b), c);
			}
		}
}