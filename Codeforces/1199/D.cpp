#include <algorithm>
#include <cstdio>
#include <cstring>
#include <set>

const int N = 2e5 + 52;
extern struct node _[];
int cnt;
struct node {
	int l, r, mid, lc, rc, t, v;
	void put(int x) {
		if (l == r) v = std::max(v, x);
		t = std::max(t, x);
	}
	void pd() { lc[_].put(t), rc[_].put(t), t = 0; }
	void build(int L, int R) {
		l = L, r = R, mid = (l + r) / 2, t = 0;
		if (L == R) return void(scanf("%d", &v));
		_[lc = ++cnt].build(L, mid);
		_[rc = ++cnt].build(mid + 1, R);
	}
	void upd(int id, int x) {
		pd();
		if (l == r) return void(v = x);
		if (id <= mid) return lc[_].upd(id, x);
		rc[_].upd(id, x);
	}
	void prt() {
		pd();
		if (l == r) return (void)printf("%d ", v);
		lc[_].prt(), rc[_].prt();
	}
} _[N << 2];

int n, a[222222], q, op, x, y;
int main() {
	scanf("%d", &n);
	_[++cnt].build(1, n);
	for (scanf("%d", &q); q--;) {
		scanf("%d%d", &op, &x);
		if (op == 1)
			scanf("%d", &y), _[1].upd(x, y);
		else
			_[1].put(x);
	}
	_[1].prt();
}