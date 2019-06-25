#include <algorithm>
#include <cstdio>
#define $(p, q, x) ((p ? q : p) = (x))
const int N = 1e7 + 71;
int n, x, u, v, _, a[N], b[N], c[N], r[N];
long long mn = 1e18, t;
int main() {
	for (int i = scanf("%d", &n); i <= n; c[r[i]]++, $(a[r[i]], b[r[i]], i), i++) scanf("%d", r + i);
	for (int i = 1; i < N; i++) {
		int p = 0, q = 0;
		for (int j = i; j < N; j += i) {
			if (c[j]) $(p, q, a[j]);
			if (p && q) break;
			if (c[j] > 1) $(p, q, b[j]);
			if (p && q) break;
		}
		if (p && q && mn > (t = 1ll * r[p] * r[q] / std::__gcd(r[p], r[q]))) u = p, v = q, mn = t;
	}
	u > v && (std::swap(u, v), 0);
	printf("%d %d", u, v);
}