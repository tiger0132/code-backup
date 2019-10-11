#include <algorithm>
#include <cstdio>
#include <cstring>

#define L ch][0
#define R ch][1
const int N = 1e5 + 51;
int ch[N][2], sz[N], v[N], pri[N], r[N], rt, nc;
void up(int x) { x[sz] = x[L][sz] + x[R][sz] + 1; }
int alloc(int x) { return (++nc)[sz] = 1, nc[v] = x, nc[pri] = rand(), nc; }
void rv(int x) { std::swap(x[L], x[R]), x[r] ^= 1; }
void pd(int x) { x[r] && (rv(x[L]), rv(x[R]), x[r] = 0); }
void spl(int id, int k, int& x, int& y) {
	if (!id) return void(x = y = 0);
	pd(id);
	if (id[L][sz] < k) return x = id, spl(id[R], k - id[L][sz] - 1, x[R], y), up(x);
	y = id, spl(id[L], k, x, y[L]), up(y);
}
int u(int x, int y) {
	if (!x || !y) return x | y;
	if (x[pri] < y[pri]) return pd(x), x[R] = u(x[R], y), up(x), x;
	return pd(y), y[L] = u(x, y[L]), up(y), y;
}
void prt(int x) {
	pd(x);
	if (x[L]) prt(x[L]);
	printf("%d ", x[v]);
	if (x[R]) prt(x[R]);
}

int n, m, ql, qr, x, y, z;
int main() {
	srand((unsigned long long)new char);
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) rt = u(rt, alloc(i));
	while (m--) {
		scanf("%d%d", &ql, &qr);
		spl(rt, ql - 1, x, y);
		spl(y, qr - ql + 1, y, z);
		rv(y);
		rt = u(u(x, y), z);
	}
	prt(rt);
}