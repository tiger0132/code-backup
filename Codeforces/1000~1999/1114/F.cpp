#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long ll;
const int N = 2e6 + 62, K = 62, P = 1e9 + 7,
		  pri[] = {2,	3,	 5,	  7,   11,	13,	 17,  19,  23,	29,	 31,  37,  41,
				   43,	47,	 53,  59,  61,	67,	 71,  73,  79,	83,	 89,  97,  101,
				   103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167,
				   173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239,
				   241, 251, 257, 263, 269, 271, 277, 281, 283, 293},
		  invp[] = {
			  500000004, 666666672, 600000005, 857142864, 181818184, 846153853, 647058829,
			  842105270, 260869568, 241379313, 870967749, 378378382, 341463418, 604651168,
			  595744686, 943396234, 949152550, 311475413, 313432839, 901408458, 589041101,
			  797468361, 915662658, 584269668, 731958769, 59405942,	 427184470, 775700941,
			  990825696, 106194692, 519685044, 809160312, 941605847, 395683457, 469798662,
			  516556296, 656050961, 883435590, 994011984, 208092488, 564245815, 66298344,
			  560209429, 305699485, 30456854,  492462316, 909952614, 874439469, 964757717,
			  288209610, 909871252, 719665278, 593361001, 87649404,	 929961097, 163498101,
			  256505579, 549815503, 747292425, 281138793, 349823325, 477815704};

int pw(int x, int y) {
	int r = 1;
	for (; y; y >>= 1, x = (ll)x * x % P)
		if (y & 1) r = (ll)r * x % P;
	return r;
}
int f_or(ll x, ll y) { return x | y; }
int f_mul(ll x, ll y) { return x * y % P; }

struct SGT {
#define L ch][0
#define R ch][1
#define mid (l + r) / 2
	int ch[N][2], sz[N], nc;
	ll s[N], s2[N], t[N], t2[N];
	SGT() { nc = 1; }
	void up(int x) {
		x[s] = x[L][s] | x[R][s];
		x[s2] = x[L][s2] * x[R][s2] % P;
	}
	void put(int x, ll y) { x[t] |= y, x[s] |= y; }
	void put2(int x, ll y) { x[t2] = x[t2] * y % P, x[s2] = x[s2] * pw(y, x[sz]) % P; }
	void pd(int x) {
		put(x[L], x[t]), put(x[R], x[t]), x[t] = 0;
		put2(x[L], x[t2]), put2(x[R], x[t2]), x[t2] = 1;
	}
	void build(int x, int l, int r, ll* a, ll* b) {
		if (x[t2] = 1, x[sz] = r - l + 1, l == r)
			return x[s] = a[l], x[s2] = b[l], void();
		build(x[L] = ++nc, l, mid, a, b), build(x[R] = ++nc, mid + 1, r, a, b), up(x);
	}
	void upd(int x, int l, int r, int ql, int qr, ll y) {
		if (ql <= l && r <= qr) return put(x, y);
		if (pd(x), ql <= mid) upd(x[L], l, mid, ql, qr, y);
		if (mid < qr) upd(x[R], mid + 1, r, ql, qr, y);
		up(x);
	}
	void upd2(int x, int l, int r, int ql, int qr, ll y) {
		if (ql <= l && r <= qr) return put2(x, y);
		if (pd(x), ql <= mid) upd2(x[L], l, mid, ql, qr, y);
		if (mid < qr) upd2(x[R], mid + 1, r, ql, qr, y);
		up(x);
	}
	ll qry(int x, int l, int r, int ql, int qr) {
		if (ql <= l && r <= qr) return x[s];
		if (pd(x), qr <= mid) return qry(x[L], l, mid, ql, qr);
		if (mid < ql) return qry(x[R], mid + 1, r, ql, qr);
		return qry(x[L], l, mid, ql, qr) | qry(x[R], mid + 1, r, ql, qr);
	}
	ll qry2(int x, int l, int r, int ql, int qr) {
		if (ql <= l && r <= qr) return x[s2];
		if (pd(x), qr <= mid) return qry2(x[L], l, mid, ql, qr);
		if (mid < ql) return qry2(x[R], mid + 1, r, ql, qr);
		return qry2(x[L], l, mid, ql, qr) * qry2(x[R], mid + 1, r, ql, qr) % P;
	}
} sgt;

ll a[N], b[N], msk;
int n, m, x, y, z;
char op[11];
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) {
		scanf("%lld", a + i);
		for (int j = 0; j < K; j++)
			if (a[i] % pri[j] == 0) b[i] |= 1ll << j;
	}
	sgt.build(1, 1, n, b, a);
	sgt.s[0] = 1;
	while (m--) {
		scanf("%s%d%d", op, &x, &y);
		if (*op == 'M') {
			scanf("%d", &z);
			msk = 0;
			for (int j = 0; j < K; j++)
				if (z % pri[j] == 0) msk |= 1ll << j;
			sgt.upd(1, 1, n, x, y, msk);
			sgt.upd2(1, 1, n, x, y, z);
		} else {
			ll tmp = sgt.qry2(1, 1, n, x, y);
			msk = sgt.qry(1, 1, n, x, y);
			for (int j = 0; j < K; j++)
				if ((msk >> j) & 1) tmp = tmp * invp[j] % P;
			printf("%lld\n", tmp);
		}
	}
}