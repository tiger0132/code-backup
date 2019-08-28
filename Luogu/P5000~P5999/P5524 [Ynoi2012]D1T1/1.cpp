#include <algorithm>
#include <cctype>
#include <cmath>
#include <cstdio>

typedef long long ll;
const int N = 8e5 + 58;

struct io_t {
#define $$ (s == t && (t = (s = in) + fread(in, 1, SIZ, stdin), s == t) ? EOF : *s++)
	static const int SIZ = 1 << 25;
	char in[SIZ], *s = in, *t = in;
	int st[15], top;
	inline int read() {
		int x = 0;
		char c = $$;
		while (!isdigit(c)) c = $$;
		while (isdigit(c)) x = x * 10 + c - 48, c = $$;
		return x;
	}
	inline operator int() { return read(); }
} io;

#define L ch][0
#define R ch][1
int ch[N][2], l[N], r[N], mid[N], cnt;
double s[N], c[N];
ll t[N];
inline void up(int x) { x[s] = x[L][s] + x[R][s], x[c] = x[L][c] + x[R][c]; }
inline void put(int x, double p, double q) {
	double u = x[s], v = x[c];
	x[s] = u * q + v * p, x[c] = v * q - u * p;
}
inline void pd(int x) {
	if (!x[t]) return;
	double u = sin(x[t]), v = cos(x[t]);
	put(x[L], u, v), put(x[R], u, v), x[L][t] += x[t], x[R][t] += x[t], x[t] = 0;
}
void build(int x, int ql, int qr, int* a) {
	x[l] = ql, x[r] = qr, x[mid] = (ql + qr) / 2;
	if (ql == qr) return (void)(x[s] = sin(a[ql]), x[c] = cos(a[ql]));
	build(x[L] = ++cnt, ql, x[mid], a), build(x[R] = ++cnt, x[mid] + 1, qr, a), up(x);
}
double qry(int x, int ql, int qr) {
	if (ql <= x[l] && x[r] <= qr) return x[s];
	double ret = 0;
	pd(x);
	if (ql <= x[mid]) ret += qry(x[L], ql, qr);
	if (x[mid] < qr) ret += qry(x[R], ql, qr);
	return ret;
}

double u, v;
void upd(int x, int ql, int qr, int y) {
	if (ql <= x[l] && x[r] <= qr) return x[t] += y, put(x, u, v);
	pd(x);
	if (ql <= x[mid]) upd(x[L], ql, qr, y);
	if (x[mid] < qr) upd(x[R], ql, qr, y);
	up(x);
}

int n, m, op, x, y, z, a[N];
int main() {
	n = io;
	for (int i = 1; i <= n; i++) a[i] = io;
	build(++cnt, 1, n, a);
	for (m = io; m--;) {
		op = io, x = io, y = io;
		if (op == 1)
			z = io, u = sin(z), v = cos(z), upd(1, x, y, z);
		else
			printf("%.1f\n", qry(1, x, y));
	}
}