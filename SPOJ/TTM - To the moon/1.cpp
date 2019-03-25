#include <algorithm>
#include <cstdio>
#include <cstring>
#define int long long
#define lson l, mid
#define rson mid + 1, r

using ll = long long;
const int N = 1e5 + 51;

int newNode(int, int, int), n;
extern struct node _[];
struct node {
	int lc, rc;
	ll v;
	void build(int l, int r, int *arr) {
		if (l == r) return void(v = arr[l]);
		int mid = (l + r) >> 1;
		_[lc = newNode(0, 0, 0)].build(l, mid, arr);
		_[rc = newNode(0, 0, 0)].build(mid + 1, r, arr);
		v = _[lc].v + _[rc].v;
	}
	int update(int x, int y, int l = 0, int r = n) {
		if (l == r) return newNode(0, 0, v + y);
		int mid = (l + r) >> 1;
		if (x <= mid) return newNode(_[lc].update(x, y, l, mid), rc, v + y);
		return newNode(lc, _[rc].update(x, y, mid + 1, r), v + y);
	}
	ll query(int L, int R, int l = 0, int r = n) {
		if (L <= l && r <= R) return v;
		int mid = (l + r) >> 1;
		ll ret = 0;
		if (L <= mid) ret += _[lc].query(L, R, l, mid);
		if (mid < R) ret += _[rc].query(L, R, mid + 1, r);
		return ret;
	}
} _[N * 130];
int newNode(int lc, int rc, int v) {
	static int ptr = 1;
	_[ptr].lc = lc, _[ptr].rc = rc, _[ptr].v = v;
	return ptr++;
}

int rt1[N], rt2[N];
ll query(int tp, int i) { return i * _[rt1[tp]].query(1, i) - _[rt2[tp]].query(1, i); }

int m, x, y, z, tp, a[N], b[N], c[N];
char op[2];
signed main() {
	scanf("%lld%lld", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", a + i);
		b[i] = a[i] - a[i - 1];
		c[i] = b[i] * (i - 1);
	}
	_[rt1[0] = newNode(0, 0, 0)].build(0, n, b);
	_[rt2[0] = newNode(0, 0, 0)].build(0, n, c);
	while (m--) {
		scanf("%s%lld", op, &x);
		if (*op == 'C') {
			scanf("%lld%lld", &y, &z);
			tp++;
			rt1[tp] = _[rt1[tp - 1]].update(x, z);
			rt1[tp] = _[rt1[tp]].update(y + 1, -z);
			rt2[tp] = _[rt2[tp - 1]].update(x, z * (x - 1));
			rt2[tp] = _[rt2[tp]].update(y + 1, -z * y);
		} else if (*op == 'Q') {
			scanf("%lld", &y);
			printf("%lld\n", query(tp, y) - query(tp, x - 1));
		} else if (*op == 'H') {
			scanf("%lld%lld", &y, &z);
			printf("%lld\n", query(z, y) - query(z, x - 1));
		} else {
			tp = x;
		}
	}
}