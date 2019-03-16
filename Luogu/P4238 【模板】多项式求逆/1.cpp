#include <algorithm>
#include <cstdio>

const int P = 998244353, G = 3, N = 3e6 + 63;

int p(int x, int y) {
	int ret = 1;
	for (; y; y >>= 1, x = 1ll * x * x % P)
		if (y & 1) ret = 1ll * ret * x % P;
	return ret;
}

int r[N], l, lim;
void ntt(int *a, int n, int x) {
	for (int i = 0; i < n; ++i)
		if (i < r[i]) std::swap(a[i], a[r[i]]);
	for (int i = 1; i < n; i <<= 1) {
		int gn = p(G, (P - 1) / (i << 1));
		for (int j = 0; j < n; j += i << 1) {
			int t1, t2, g = 1;
			for (int k = 0; k < i; k++, g = 1ll * g * gn % P) {
				t1 = a[j + k], t2 = 1ll * g * a[j + k + i] % P;
				a[j + k] = (t1 + t2) % P, a[j + k + i] = (t1 - t2 + P) % P;
			}
		}
	}
	if (x == 1) return;
	int _ = p(n, P - 2);
	std::reverse(a + 1, a + n);
	for (int i = 0; i < n; ++i) a[i] = 1ll * a[i] * _ % P;
}

int n, a[N], b[N], c[N];
void go(int x) {
	if (x == 1) return void(b[0] = p(a[0], P - 2));
	go((x + 1) >> 1);
	lim = 1, l = 0;
	while (lim < (x << 1)) lim <<= 1, l++;
	for (int i = 1; i < lim; ++i) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (l - 1));
	for (int i = 0; i < x; ++i) c[i] = a[i];
	for (int i = x; i < lim; ++i) c[i] = 0;
	ntt(c, lim, 1), ntt(b, lim, 1);
	for (int i = 0; i < lim; ++i) b[i] = (2 - 1ll * c[i] * b[i] % P + P) % P * b[i] % P;
	ntt(b, lim, -1);
	for (int i = x; i < lim; ++i) b[i] = 0;
}

int main() {
	scanf("%d", &n);
	for (int i = 0; i < n; ++i) scanf("%d", a + i);
	go(n);
	for (int i = 0; i < n; ++i) printf("%d ", b[i]);
}