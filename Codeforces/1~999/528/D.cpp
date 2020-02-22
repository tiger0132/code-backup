#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

typedef unsigned long long L;
const int N = 1e6 + 61, P = 998244353, G = 114514;

int pw(int x, int y) {
	int r = 1;
	for (; y; y >>= 1, x = (L)x * x % P)
		if (y & 1) r = (L)r * x % P;
	return r;
}
struct poly {
	std::vector<int> v;

	poly() {}
	poly(int n) : v(n) {}
	poly(const poly& rhs) : v(rhs.v) {}

	static int len(int n) { return 1 << (32 - __builtin_clz(n)); }

	inline size_t size() { return v.size(); }
	inline bool empty() { return v.empty(); }
	inline void resize(int n) { v.resize(n); }
	inline void clear() { v.clear(); }

	inline int& operator[](int i) { return v[i]; }

	void dft(int n) {
		static L tmp[N];
		resize(n);
		if (n <= 1) return;
		for (int i = 0, ri = 0; i < n; i++) {
			tmp[i] = v[ri];
			for (int k = n >> 1; (ri ^= k) < k;) k >>= 1;
		}
		for (int i = 1; i < n; i *= 2) {
			int wn = pw(G, (P - 1) / (i * 2));
			for (int j = 0; j < n; j += i * 2) {
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
		int tmp = P - (P - 1) / n;
		for (int& i : v) i = (L)i * tmp % P;
	}
	void mul(poly rhs) {
		int n = len(size() + rhs.size() - 1);
		dft(n), rhs.dft(n);
		for (int i = 0; i < n; i++) v[i] = (L)v[i] * rhs[i] % P;
		idft(n);
	}
} a[4], b[4];

int last[5], mp[128], ans;
char s[N], t[N];
int n, m, k;
int main() {
	'A'[mp] = 0, 'T'[mp] = 1, 'G'[mp] = 2, 'C'[mp] = 3;
	scanf("%d%d%d%s%s", &n, &m, &k, s, t);
	for (int i = 0; i < 4; i++) a[i].resize(n), b[i].resize(m);
	for (int i = 0; i < m; i++) b[t[i][mp]][m - i - 1] = 1;
	for (int i = 0; i < n; i++) s[i] = s[i][mp];

	0 [last] = 1 [last] = 2 [last] = 3 [last] = -1e9;
	for (int i = 0; i < n; i++) {
		s[i][last] = i;
		for (int j = 0; j < 4; j++) a[j][i] |= j[last] >= i - k;
	}
	0 [last] = 1 [last] = 2 [last] = 3 [last] = 1e9;
	for (int i = n - 1; i >= 0; i--) {
		s[i][last] = i;
		for (int j = 0; j < 4; j++) a[j][i] |= j[last] <= i + k;
	}

	for (int i = 0; i < 4; i++) a[i].mul(b[i]);
	for (int i = m - 1; i < m + n - 1; i++)
		ans += (a[0][i] + a[1][i] + a[2][i] + a[3][i]) == m;
	printf("%d", ans);
}