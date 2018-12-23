#include <cstdio>

typedef long long ll;
const int N = 5e5+55, M = 2e7+72;

namespace BIT {
	ll r[N], n;
	inline int lowbit(int x) { return x&-x; }
	void add(int i, ll x) { for (; i <= n; i += lowbit(i)) r[i] += x; }
	ll query(int i) { ll ret = 0; for (; i; i -= lowbit(i)) ret += r[i]; return ret; }
	void add(int l, int r, ll x) { add(l, x); add(r+1, -x); }
	void init(int n_, ll *t) {
		n = n_;
		for (int i = 1; i <= n; i++) add(i, t[i] - t[i-1]);
	}
}
ll p_(ll x, ll y, ll z, int& f) {
	if (z == 1 || x % z == 0) { f = 1; return 0; }
	if (x >= z) x %= z, f = 1;
	ll ret = 1;
	for (; y; y >>= 1) {
		if (y & 1) {
			if ((ret *= x) >= z) f = 1, ret %= z;
		}
		if ((x *= x) >= z) f = 1, x %= z;
	}
	return ret;
}

int pr[M], np[M], phi[M], cnt;
ll a[N];
ll query(int l, int r, int p, int &f) {/*
	for (int i = l+1, _p = p; i <= r; i++) {
		_p = phi[_p];
		if (_p == 1) r = i;
	}
	ll lans = a[r] = BIT::query(r);
	int flag = 0;
	for (int i = r-1; i >= l; i--) {
		a[i] = BIT::query(i);
		if (flag) lans += phi[p];
		flag = 0;
		lans = p_(a[i], lans, p, f);
	}
	return lans;*/
	a[l] = BIT::query(l);
	if (l == r) return a[l];
	if (p == 1) return 0;
	int _=0; ll tmp = query(l+1, r, phi[p], _);
	tmp += _ * phi[p];
	return p_(a[l], tmp, p, f);
}

int n, m, op, l, r, x;
signed main() {
	phi[1] = 1;
	for (int i = 2; i < M; i++) {
		if (!np[i]) {
			pr[++cnt] = i;
			phi[i] = i-1;
		}
		for (int j = 1, k; j <= cnt && (k = i * pr[j]) < M; j++) {
			np[k] = 1;
			if (i % pr[j]) {
				phi[k] = phi[i] * phi[pr[j]];
			} else {
				phi[k] = phi[i] * pr[j];
				break;
			}
		}
	}
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%lld", a+i);
	BIT::init(n, a);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d%d%d", &op, &l, &r, &x);
		if (op == 1) {
			BIT::add(l, r, x);
		} else {
			int _; printf("%lld\n", query(l, r, x, _) % x);
		}
	}
}