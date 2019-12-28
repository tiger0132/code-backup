#include <algorithm>
#include <cstdio>
#include <cstring>

#define L ch][0
#define R ch][1
#define mid (l + r) / 2
typedef long long ll;
const int N = 4e5 + 54, P = 1e9 + 7;
struct mat {
	ll a, b, c, d;
	void A() { a = b = d = 1, c = 0; }
	void B() { a = c = d = 1, b = 0; }
} t[N], rt[N];
mat operator*(const mat& x, const mat& y) {
	return {(x.a * y.a + x.c * y.b) % P, (x.b * y.a + x.d * y.b) % P,
			(x.a * y.c + x.c * y.d) % P, (x.b * y.c + x.d * y.d) % P};
}
int ch[N][2], r[N], nc;
void up(int x) { x[t] = x[L][t] * x[R][t], x[rt] = x[L][rt] * x[R][rt]; }
void rv(int x) { x[r] ^= 1, std::swap(x[t], x[rt]); }
void pd(int x) { x[r] && (rv(x[L]), rv(x[R]), x[r] = 0); }
void build(int x, int l, int r, char* s) {
	if (l == r) {
		if (s[l] == 'A') return x[t].A(), x[rt].B();
		return x[t].B(), x[rt].A();
	}
	build(x[L] = ++nc, l, mid, s), build(x[R] = ++nc, mid + 1, r, s), up(x);
}
mat qry(int x, int l, int r, int ql, int qr) {
	if (ql <= l && r <= qr) return x[t];
	if (pd(x), qr <= mid) return qry(x[L], l, mid, ql, qr);
	if (mid < ql) return qry(x[R], mid + 1, r, ql, qr);
	return qry(x[L], l, mid, ql, qr) * qry(x[R], mid + 1, r, ql, qr);
}
void upd(int x, int l, int r, int ql, int qr) {
	if (ql <= l && r <= qr) return rv(x);
	if (pd(x), ql <= mid) upd(x[L], l, mid, ql, qr);
	if (mid < qr) upd(x[R], mid + 1, r, ql, qr);
	up(x);
}

int n, m, op, x, y, a, b;
char s[N];
int main() {
	scanf("%d%d%s", &n, &m, s + 1);
	for (build(nc = 1, 1, n, s); m--;) {
		scanf("%d%d%d", &op, &x, &y);
		if (op == 1)
			upd(1, 1, n, x, y);
		else {
			scanf("%d%d", &a, &b);
			mat t = qry(1, 1, n, x, y);
			printf("%lld %lld\n", (t.a * a + t.b * b) % P, (t.c * a + t.d * b) % P);
		}
	}
}