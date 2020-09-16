#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

typedef unsigned long long L;
const int N = 1.1e6 + 611, P = 998244353, G = 114514;

int pw(int x, int y) {
	int r = 1;
	for (; y; y >>= 1, x = (L)x * x % P)
		if (y & 1) r = (L)r * x % P;
	return r;
}

L tmp[N];
struct poly {
	std::vector<int> v;

	inline poly() {}

	inline int size() { return v.size(); }
	inline void resize(int n) { v.resize(n); }
	inline void shrink() {
		while (!v.empty() && !v.back()) v.pop_back();
	}
	inline int &operator[](int i) { return v[i]; }

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
		std::reverse(v.begin() + 1, v.end());
		int inv = P - (P - 1) / n;
		for (int &i : v) i = (L)i * inv % P;
	}
	void mul(poly rhs) {
		int n = len(size() + rhs.size() - 1);
		dft(n), rhs.dft(n);
		for (int i = 0; i < n; i++) v[i] = (L)v[i] * rhs[i] % P;
		idft(n), shrink();
	}
} f, g0;

long long ans;
int n, v[N];
char s[N];
int main() {
	scanf("%s", s);
	n = strlen(s);
	f.resize(n), g0.resize(n);
	for (int i = 0; i < n; i++)
		if (s[i] == '0')
			f[i] = 1;
		else if (s[i] == '1')
			g0[n - i - 1] = 1;
	f.mul(g0);
	ans = 1ll * n * n;
	for (int i = 1; i < n; i++) {
		for (int j = i; j < n; j += i)
			if (f[n - j - 1] || f[n + j - 1]) goto end;
		ans ^= 1ll * (n - i) * (n - i);
	end:;
	}
	printf("%lld\n", ans);
}