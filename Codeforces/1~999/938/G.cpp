#include <algorithm>
#include <cstdio>
#include <cstring>
#include <map>
#include <utility>
#include <vector>

typedef std::pair<int, int> pii;
const int N = 4e5 + 54, K = 29;

struct _ {
	int *p, v;
} st[N * 6];
int t;
void $(int& x, int y) { st[++t] = (_){&x, x}, x = y; }

int p[K + 5];
void I(int x) {
	for (int i = K, f; ~i; x ^= f * p[i--])
		if ((f = (x >> i) & 1) && !p[i]) return $(p[i], x);
}
int Q(int x) {
	for (int i = K; ~i; i--) x = std::min(x, x ^ p[i]);
	return x;
}

int _p[N], sz[N];
int xv[N], _t;
int f(int x, int& w = _t) {
	while (x[_p]) w ^= x[xv], x = x[_p];
	return x;
}
void M(int x, int y, int z) {
	_t = 0;
	if ((x = f(x)) != (y = f(y))) {
		if (x[sz] > y[sz]) std::swap(x, y);
		$(x[_p], y), $(y[sz], y[sz] + x[sz]), $(x[xv], z ^ _t);
	}
}
inline int Q(int x, int y) { return _t = 0, f(x), f(y), _t; }
inline void A(int a, int b, int c) {
	if (f(a) != f(b))
		M(a, b, c);
	else
		I(Q(a, b) ^ c);
}

#define L (x << 1)
#define R ((x << 1) | 1)
#define md (l + r) / 2
int op[N], u[N], v[N], w[N], qu[N], qv[N];
std::vector<int> tr[N << 2];
int ql, qr;
void I(int x, int l, int r, int y) {
	if (ql <= l && r <= qr) return x[tr].push_back(y);
	if (ql <= md) I(L, l, md, y);
	if (md < qr) I(R, md + 1, r, y);
}
void D(int x, int l, int r) {
	int sz = t;
	for (int i : x[tr]) A(u[i], v[i], w[i]);
	if (l == r)
		printf("%d\n", Q(Q(qu[l], qv[l])));
	else
		D(L, l, md), D(R, md + 1, r);
	for (; t > sz; t--) *st[t].p = st[t].v;
}

int n, m, m0, q, x, y, z, tm_lb[N], tm_rb[N];
int qry_lb[N], qry_rb[N], qc;
std::map<pii, int> mp;
int main() {
	scanf("%d%d", &n, &m0), m += m0;
	for (int i = 1; i <= n; i++) i[sz] = 1;
	for (int i = 1; i <= m0; i++) {
		op[i] = 1, scanf("%d%d%d", u + i, v + i, w + i);
		mp[pii(u[i], v[i])] = i;
	}
	scanf("%d", &m), m += m0;
	for (int i = m0 + 1; i <= m; i++) {
		scanf("%d%d%d", op + i, u + i, v + i);
		if (op[i] == 1) {
			scanf("%d", w + i);
			mp[pii(u[i], v[i])] = i;
		}
		if (op[i] == 3) qc++, qu[qc] = u[i], qv[qc] = v[i];
		i[tm_rb] = qc;
	}
	for (int i = 1; i <= m; i++) i[qry_rb] = qc;
	for (int i = m, c = qc + 1; i >= 1; i--) i[tm_lb] = c -= (op[i] == 3);

	for (int i = 1; i <= m; i++) {
		if (op[i] == 1) i[qry_lb] = i[tm_lb];
		if (op[i] == 2) mp[pii(u[i], v[i])][qry_rb] = i[tm_rb];
	}
	for (int i = 1; i <= m; i++) {
		// printf("[%d, %d]\n", i[tm_lb], i[tm_rb]);
		if (op[i] == 1 && i[qry_lb] <= i[qry_rb])
			ql = i[qry_lb], qr = i[qry_rb], I(1, 1, qc, i);
	}
	D(1, 1, qc);
}