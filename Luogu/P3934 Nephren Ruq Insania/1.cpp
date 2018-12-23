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
ll p_(ll x, ll y, ll z) {
	if (z == 1 || x % z == 0) return 0;
	x %= z; ll ret = 1;
	for (; y; y >>= 1) {
		if (y & 1) {
			if ((ret *= x) >= z) ret %= z;
		}
		if ((x *= x) >= z) x %= z;
	}
	return ret;
}

int pr[M], np[M], phi[M], cnt;
ll a[N];
ll query(int l, int r, int p) {
	a[l] = BIT::query(l);
	if (p == 1) return 1;
	if (a[l] >= p) (a[l] %= p) += p;
	if (l == r) return a[l];
	return p_(a[l], query(l+1, r, phi[p]), p);
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
	scanf("%lld%lld", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%lld", a+i);
	BIT::init(n, a);
	for (int i = 1; i <= m; i++) {
		scanf("%lld%lld%lld%lld", &op, &l, &r, &x);
		if (op == 1) {
			BIT::add(l, r, x);
		} else {
			printf("%lld\n", query(l, r, x) % x);
		}
	}
}