#include <algorithm>
#include <cstring>
#include <cstdio>
#define mid (l + r) / 2
#define lson l, mid
#define rson mid + 1, r
#define $ ++cnt

const int N = 1e5 + 51, P = 998244353, d2 = 499122177;
extern struct node _[];
int cnt;
struct node {
	int lc, rc, f, g, sumf, tag;
	void build(int l, int r) {
		sumf = f = g = 0, tag = 1;
		if (l != r) _[lc = $].build(lson), _[rc = $].build(rson);
	}
	void assign(int x) { g = (1ll * g * x + 1 - x + P) % P, tag = 1ll * tag * x % P; }
	void pushdown() { _[lc].assign(tag), _[rc].assign(tag), tag = 1; }
	void pushup() { sumf = (1ll * f + _[lc].sumf + _[rc].sumf) % P; }
	void update(int l, int r, int L, int R) {
		if (r < L || R < l) { // !traverse + pushdown
			f = 1ll * (f + g) * d2 % P, pushup();
			return;
		}
		if (L <= l && r <= R) { // traverse + puttag
			f = (f + 1ll) * d2 % P, assign(d2), pushup();
			return;
		}
		pushdown();
		f = 1ll * f * d2 % P, g = 1ll * g * d2 % P;
		_[lc].update(lson, L, R);
		_[rc].update(rson, L, R);
        pushup();
	}
} _[N << 2];

int n, m, op, L, R, rt, p2 = 1;
int main() {
	scanf("%d%d", &n, &m);
	_[rt = $].build(1, n);
	while (m--) {
		scanf("%d", &op);
		if (op == 1) {
			scanf("%d%d", &L, &R);
			_[rt].update(1, n, L, R);
			p2 = p2 * 2 % P;
		} else {
			printf("%lld\n", 1ll * _[rt].sumf * p2 % P);
		}
	}
}
