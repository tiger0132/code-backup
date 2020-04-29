#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <functional>
#include <vector>

typedef unsigned long long L;
const int N = 4e5 + 54, P = 998244353, G = 114514;

int pw(int x, int y) {
	int r = 1;
	for (; y; y >>= 1, x = (L)x * x % P)
		if (y & 1) r = (L)r * x % P;
	return r;
}

struct comb {
	int fac[N], ifac[N];
	void init(int n) {
		0 [fac] = 1;
		for (int i = 1; i <= n; i++) i[fac] = (L)(i - 1)[fac] * i % P;
		n[ifac] = pw(n[fac], P - 2);
		for (int i = n - 1; i >= 0; i--) i[ifac] = (L)(i + 1)[ifac] * (i + 1) % P;
	}
	int operator()(int n, int m) { return (L)n[fac] * m[ifac] % P * (n - m)[ifac] % P; }
} C;

L tmp[N];
struct poly {
	std::vector<int> v;

	inline poly() {}
	inline poly(int n) : v(n) {}
	inline poly(const poly &rhs) : v(rhs.v) {}

	inline int size() const { return v.size(); }
	inline void resize(int n) { v.resize(n); }
	inline int &operator[](int i) { return v[i]; }
	inline int operator[](int i) const { return v[i]; }
	void shrink() {
		while (!v.empty() && !v.back()) v.pop_back();
	}

	inline static int len(int n) { return 1 << (32 - __builtin_clz(n - 1)); }

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
		if (n <= 1) return;
		std::reverse(v.begin() + 1, v.end());
		int inv = P - (P - 1) / n;
		for (int &i : v) i = (L)i * inv % P;
	}
	void mul(
		poly rhs,
		std::function<int(int, int)> f = [](int x, int y) { return (L)x * y % P; }) {
		int n = len(size() + rhs.size() - 1);
		dft(n), rhs.dft(n);
		for (int i = 0; i < n; i++) v[i] = f(v[i], rhs[i]);
		idft(n), shrink();
	}
	void inv() {
		std::vector<int> va{pw(v[0], P - 2)};
		int n = size(), m = len(n);
		poly f;
		resize(m), v.swap(va);
		for (int i = 2; i <= m; i <<= 1) {
			f.resize(i);
			for (int j = 0; j < i; j++) f[j] = va[j];
			mul(f, [](int x, int y) { return x * (2 + P - (L)x * y % P) % P; });
			resize(i);
		}
		resize(n);
	}
} f, g;

int n;
int main() {
	scanf("%d", &n);
	f.resize(n + 1), g.resize(n + 1), C.init(n);
	for (int i = 0; i <= n; i++)
		f[i] = g[i] = (L)pw(2, (L)i * (i - 1) / 2 % (P - 1)) * i[C.ifac] % P;
	g.inv();
	g[0] = 1 - g[0];
	for (int i = 1; i <= n; i++) g[i] = (P - (L)g[i] * i % P) % P;
	g.mul(f);
	for (int i = 1; i <= n; i++)
		printf("%lld\n", (L)g[i] % P * (i - 1)[C.fac] % P * f[n - i] % P *
							 (n - i)[C.fac] % P * C(n - 1, i - 1) % P);
}