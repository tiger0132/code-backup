#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
#define int long long

typedef unsigned __int128 L;
const int N = 5.3e5 + 535, P = 1231453023109121, G = 3;

int pw(int x, int y) {
	int r = 1;
	for (; y; y >>= 1, x = (L)x * x % P)
		if (y & 1) r = (L)r * x % P;
	return r;
}

L tmp[N];
struct poly {
	std::vector<int> v;

	poly() {}
	poly(const poly &rhs) : v(rhs.v) {}

	size_t size() { return v.size(); }
	void resize(size_t n) { v.resize(n); }
	int &operator[](int i) { return v[i]; }

	int len(int n) { return 1 << (32 - __builtin_clz(n - 1)); }

	void dft(int n) {
		resize(n);
		if (n <= 1) return;
		for (int i = 0, ri = 0; i < n; i++) {
			tmp[i] = v[ri];
			for (int k = n >> 1; (ri ^= k) < k;) k >>= 1;
		}
		for (int i = 1; i < n; i <<= 1) {
			int wn = pw(G, (P - 1) / (i << 1));
			for (int j = 0; j < n; j += i << 1) {
				L *a = tmp + j, *b = tmp + j + i;
				for (int k = 0, w = 1; k < i; k++, w = (L)w * wn % P) {
					int y = b[k] * w % P;
					b[k] = a[k] + P - y, a[k] += y;
				}
			}
		}
		for (int i = 0; i < n; i++) v[i] = tmp[i] % P;
	}
	void idft(int n) {
		dft(n);
		std::reverse(v.begin() + 1, v.end());
		int inv = P - (P - 1) / n;
		for (int i = 0; i < n; i++) v[i] = (L)inv * v[i] % P;
	}
	void mul(poly rhs) {
		int n = len(size() + rhs.size() - 1);
		dft(n), rhs.dft(n);
		for (int i = 0; i < n; i++) v[i] = (L)v[i] * rhs[i] % P;
		idft(n);
	}
} f, g;

int n, k, x, s, c;
long long ans;
signed main() {
	scanf("%lld%lld", &n, &k);
	f.resize(n + 1), g.resize(n + 1);
	f[0]++, g[n]++;
	for (int i = 1; i <= n; i++) {
		scanf("%lld", &x), s += (x < k);
		f[s]++, g[n - s]++;
		if (x >= k)
			ans += ++c;
		else
			c = 0;
	}
	f.mul(g);
	printf("%lld ", ans);
	for (int i = n + 1; i <= n * 2; i++) printf("%lld ", f[i]);
}