#include <algorithm>
#include <cstdio>
#include <cstring>
#define L ch][0
#define R ch][1
#define mid (l + r) / 2

typedef long long ll;
const int N = 4e5 + 54;
// s1: a1 + a2 + a3 + ...
// s2: a1 + 2*a2 + 3*a3 + ...
// s3: a1 + 4*a2 + 9*a3 + ...
struct node {
	ll s1, s2, s3;
} _[N];
node operator+(const node& l, const node& r) {
	return {l.s1 + r.s1, l.s2 + r.s2, l.s3 + r.s3};
}
ll S2(ll x) { return x * (x + 1) / 2; }
ll S3(ll x) { return x * (2 * x + 1) * (x + 1) / 6; }
int ch[N][2], nc;
ll t[N], sz[N];
void up(int x) { x[_] = x[L][_] + x[R][_]; }
void put(int x, int l, int r, int v) {
	x[t] += v;
	x[_].s1 += x[sz] * v;
	x[_].s2 += (S2(r) - S2(l - 1)) * v;
	x[_].s3 += (S3(r) - S3(l - 1)) * v;
}
void pd(int x, int l, int r) {
	if (x[t]) put(x[L], l, mid, x[t]), put(x[R], mid + 1, r, x[t]), x[t] = 0;
}
void build(int x, int l, int r) {
	x[sz] = r - l + 1;
	if (l < r) build(x[L] = ++nc, l, mid), build(x[R] = ++nc, mid + 1, r);
}
void upd(int x, int l, int r, int ql, int qr, int v) {
	if (ql <= l && r <= qr) return put(x, l, r, v);
	pd(x, l, r);
	if (ql <= mid) upd(x[L], l, mid, ql, qr, v), up(x);
	if (mid < qr) upd(x[R], mid + 1, r, ql, qr, v), up(x);
}
node qry(int x, int l, int r, int ql, int qr) {
	if (ql <= l && r <= qr) return x[_];
	pd(x, l, r);
	if (qr <= mid) return qry(x[L], l, mid, ql, qr);
	if (mid < ql) return qry(x[R], mid + 1, r, ql, qr);
	return qry(x[L], l, mid, ql, qr) + qry(x[R], mid + 1, r, ql, qr);
}

ll x, y, z, u, v, tt;
int n, m, l, r;
char op[2];
int main() {
	scanf("%d%d", &n, &m);
	build(nc = 1, 1, n);
	for (; m--;) {
		scanf("%s%d%d", op, &l, &r), r--;
		if (*op == 'C') {
			scanf("%lld", &z);
			upd(1, 1, n, l, r, z);
		} else {
			node t = qry(1, 1, n, l, r);
			x = t.s1, y = t.s2, z = t.s3;
			u = -z + (l + r) * y + (-1ll * l * r - l + r + 1) * x;
			v = (r - l + 2ll) * (r - l + 1) / 2;
			tt = std::__gcd(u, v);
			printf("%lld/%lld\n", u / tt, v / tt);
		}
	}
}