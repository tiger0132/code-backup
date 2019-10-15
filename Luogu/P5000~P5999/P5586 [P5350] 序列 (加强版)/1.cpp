#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>

// clang-format off
#define L ch][0
#define R ch][1
#define _(a) id[a] = x[a]
const int N = 4e6 + 64, M = 3e5 + 53, P = 1e9 + 7;
void add(int& x, int y) { (x += y) >= P && (x -= P); }
int add2(int x, int y) { return (x += y) >= P ? x - P : x; }
int ch[N][2], v[N], ad[N], set[N], sz[N], s[N], nc;
bool r[N];
void up(int x) { x[sz] = x[L][sz] + x[R][sz] + 1, x[s] = add2(add2(x[L][s], x[R][s]), x[v]); }
void rv(int x) { std::swap(x[L], x[R]), x[r] ^= 1; }
int alloc(int x) {
	int id = ++nc; return id[s] = id[v] = x, id[sz] = 1, id[set] = -1, id;
}
int cl(int x) {
	int id = ++nc; return _(L), _(R), _(v), _(s), _(ad), _(set), _(r), _(sz), id;
}
void pr(int x) { if (x) x[r] ^= 1, std::swap(x[L], x[R]); }
void pa(int x, int y) { if (x) add(x[ad], y), add(x[v], y), x[s] = (x[s] + 1ll * x[sz] * y) % P; }
void ps(int x, int y) { if (x) x[v] = y, x[s] = 1ll * x[sz] * y % P, x[set] = y, x[ad] = 0; }
void pd(int x) {  // set -> add -> rev
	if (!x[r] && !x[ad] && x[set] == -1) return;
	if (x[L]) x[L] = cl(x[L]);
	if (x[R]) x[R] = cl(x[R]);
	if (x[set] != -1) ps(x[L], x[set]), ps(x[R], x[set]), x[set] = -1;
	if (x[ad]) pa(x[L], x[ad]), pa(x[R], x[ad]), x[ad] = 0;
	if (x[r]) pr(x[L]), pr(x[R]), x[r] = 0;
}
void spl(int id, int k, int& x, int& y) {
	if (!id) return void(x = y = 0);
	pd(id);
	if (id[L][sz] < k) return x = cl(id), spl(x[R], k - x[L][sz] - 1, x[R], y), up(x);
	y = cl(id), spl(y[L], k, x, y[L]), up(y);
}
int u(int x, int y) {
	if (!x || !y) return x | y;
	if (rand() % (x[sz] + y[sz]) < x[sz]) return pd(x), x = cl(x), x[R] = u(x[R], y), up(x), x;
	return pd(y), y = cl(y), y[L] = u(x, y[L]), up(y), y;
}
int build(int l, int r, int* ar) {
	if (l > r) return 0;
	int mid = (l + r) / 2, x = alloc(ar[mid]);
	x[L] = build(l, mid - 1, ar), x[R] = build(mid + 1, r, ar);
	return up(x), x;
}
void prt(int x) {
	pd(x);
	if (x[L]) prt(x[L]);
	printf("%d ", x[v]);
	if (x[R]) prt(x[R]);
}
// clang-format on

int n, op, x, y, z, w, a, b, c, d, e, la, rt, ar[M];
void dfs(int x) {
	pd(x);
	if (x[L]) dfs(x[L]);
	ar[++n] = x[v];
	if (x[R]) dfs(x[R]);
}
signed main() {
	srand(20081105);
	scanf("%d%*d", &n);
	for (int i = 1; i <= n; i++) scanf("%d", ar + i);
	rt = build(1, n, ar);
	for (; ~scanf("%d%d%d", &op, &x, &y);) {
		x ^= la, y ^= la;
		if (op < 4 || op == 6) {
			spl(rt, y, b, c);
			spl(b, x - 1, a, b);
			if (op == 1)
				printf("%d\n", la = b[s]);
			else if (op == 6)
				pr(b);
			else
				scanf("%d", &z), z ^= la, (op == 2 ? ps : pa)(b, z);
			rt = u(u(a, b), c);
		} else {
			scanf("%d%d", &z, &w), z ^= la, w ^= la;
			bool swped = false;
			if (x > z) std::swap(x, z), std::swap(y, w), swped = true;
			spl(rt, w, d, e);
			spl(d, z - 1, c, d);
			spl(c, y, b, c);
			spl(b, x - 1, a, b);
			if (op == 4)
				if (swped)
					b = cl(d);
				else
					d = cl(b);
			else
				std::swap(b, d);
			rt = u(u(u(u(a, b), c), d), e);
		}
		if (nc > 3.6e6) n = 0, dfs(rt), nc = 0, rt = build(1, n, ar);
	}
	prt(rt);
}