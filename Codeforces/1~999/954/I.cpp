#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

typedef unsigned long long L;
const int N = 5.3e5 + 535, P = 998244353, G = 114514;

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
	poly(const poly& rhs) : v(rhs.v) {}

	size_t size() { return v.size(); }
	void resize(size_t n) { v.resize(n); }

	static int len(int n) { return 1 << (32 - __builtin_clz(n - 1)); }
	int& operator[](int i) { return v[i]; }

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
		for (int& i : v) i = (L)i * inv % P;
	}
	void mul(poly rhs) {
		int n = len(size() + rhs.size() - 1);
		dft(n), rhs.dft(n);
		for (int i = 0; i < n; i++) v[i] = (L)v[i] * rhs[i] % P;
		idft(n);
	}
} f[6], g[6], res[6][6];
struct DSU {
	int p[6], cc;
	void clear() {
		for (int i = 0; i < 6; i++) i[p] = i;
		cc = 6;
	}
	int f(int x) { return x[p] == x ? x : x[p] = f(x[p]); }
	void u(int x, int y) {
		if ((x = f(x)) != (y = f(y))) x[p] = y, cc--;
	}
} dsu;

int n, m, len;
char s[N], t[N];
int main() {
	scanf("%s%s", s, t);
	n = strlen(s), m = strlen(t);
	len = poly::len(n + m - 1);
	for (int i = 0; i < 6; i++) f[i].resize(n), g[i].resize(m);
	for (int i = 0; i < n; i++) f[s[i] - 'a'][i] = 1;
	for (int i = 0; i < m; i++) g[t[i] - 'a'][m - i - 1] = 1;
	for (int i = 0; i < 6; i++) f[i].dft(len), g[i].dft(len);
	for (int i = 0; i < 6; i++)
		for (int j = 0; j < 6; j++) {
			res[i][j].resize(len);
			for (int k = 0; k < len; k++) res[i][j][k] = (L)f[i][k] * g[j][k] % P;
			res[i][j].idft(len);
		}
	for (int i = m - 1; i < n; i++) {
		dsu.clear();
		for (int j = 0; j < 6; j++)
			for (int k = 0; k < 6; k++)
				if (res[j][k][i]) dsu.u(j, k);
		printf("%d ", 6 - dsu.cc);
	}
}