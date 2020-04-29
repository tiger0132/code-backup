#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <vector>

typedef long long L;
const int N = 2e3 + 32;

int P;
void exgcd(int a, int b, int &x, int &y) {
	b ? exgcd(b, a % b, y, x), y -= x * (a / b) : (x = 1, y = 0);
}
int inv(int a) {
	int x, y;
	return exgcd(a, P, x, y), (x + P) % P;
}
int pw(int x, int y) {
	int r = 1;
	for (; y; y >>= 1, x = (L)x * x % P)
		if (y & 1) r = (L)r * x % P;
	return r;
}

struct comb {
	int C[N][N];  // sb ctr, fuck you
	void init(int n) {
		for (int i = 0; i <= n; i++) {
			C[i][0] = 1;
			for (int j = 1; j <= i; j++) C[i][j] = (C[i - 1][j] + C[i - 1][j - 1]) % P;
		}
	}
	int operator()(int n, int m) { return C[n][m]; }
} C;
struct poly {  // n^2 多项式
	std::vector<int> v;

	inline poly() {}
	inline poly(int n) : v(n) {}
	inline poly(const poly &rhs) : v(rhs.v) {}

	inline int size() const { return v.size(); }
	inline void resize(int n) { v.resize(n); }
	inline int &operator[](int i) { return v[i]; }
	inline int operator[](int i) const { return v[i]; }

	L tmp[N];
	void mul(const poly &rhs) {
		int n = size() + rhs.size() - 1;
		memset(tmp, 0, n * sizeof(L));
		for (int i = 0; i < size(); i++)
			for (int j = 0; j < rhs.size(); j++) tmp[i + j] += (L)v[i] * rhs[j] % P;
		resize(n);
		for (int i = 0; i < n; i++) v[i] = tmp[i] % P;
	}
	void inv() {
		int n = size();
		memset(tmp, 0, n * sizeof(L));
		tmp[0] = 1;
		for (int i = 1; i < n; i++) {
			for (int j = 0; j < i; j++) tmp[i] -= (L)C(i, j) * tmp[j] % P * v[i - j] % P;
			tmp[i] = (tmp[i] % P + P) % P;
		}
		for (int i = 0; i < n; i++) v[i] = tmp[i];
	}
} f, g;

int n;
int main() {
	scanf("%d%d", &n, &P);
	f.resize(n + 1), g.resize(n + 1), C.init(n);
	for (int i = 0; i <= n; i++) f[i] = pw(2, (L)i * (i - 1) / 2);
	for (int i = 0; i <= n; i++) g[i] = (L)f[i] % P;
	g.inv();
	// g[0] = 1 - g[0];
	for (int i = 1; i <= n; i++) g[i] = (P - (L)g[i] % P) % P;
	for (int i = 1; i <= n; i++) {
		L ans = 0;
		for (int j = 1; j <= i; j++) {
			ans += (L)C(i - 1, j - 1) * g[j] % P * f[i - j] % P;
		}
		ans = ans % P * f[n - i] % P * C(n - 1, i - 1) % P;
		printf("%lld\n", ans);
	}
}