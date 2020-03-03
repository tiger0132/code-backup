#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long ll;
const int N = 2e5 + 52, K = 59;

ll p[K + 5], _tmp;
void ins(ll x) {
	for (int i = K, f; ~i; x ^= f * p[i--])
		if ((f = (x >> i) & 1) && !p[i]) return p[i] = x, void();
}
ll qry(ll x) {
	for (int i = K; ~i; i--) x = std::max(x, x ^ p[i]);
	return x;
}

int _p[N], sz[N];
ll xv[N], tmp;
int f(int x, ll& w = tmp) {
	while (x[_p]) w ^= x[xv], x = x[_p];
	return x;
}
void mg(int x, int y, ll z) {
	tmp = 0;
	if ((x = f(x)) != (y = f(y))) {
		if (x[sz] > y[sz]) std::swap(x, y);
		x[_p] = y, y[sz] += x[sz], x[xv] ^= z ^ tmp;
	}
}
inline ll qry(int x, int y) { return tmp = 0, f(x), f(y), tmp; }

int u[N], v[N];
ll w[N];

int n, m, q;
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) i[sz] = 1;
	for (int i = 1; i <= m; i++) {
		scanf("%d%d%lld", u + i, v + i, w + i);
		if (f(u[i]) != f(v[i]))
			mg(u[i], v[i], w[i]);
		else
			ins(qry(u[i], v[i]) ^ w[i]);
	}
	printf("%lld", qry(qry(1, n)));
}