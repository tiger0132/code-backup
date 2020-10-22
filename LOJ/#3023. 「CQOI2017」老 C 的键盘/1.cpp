#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

typedef long long L;
const int N = 1e2 + 21, P = 1e9 + 7;

struct mod_t {
	static int norm(int x) { return x + (x >> 31 & P); }
	static void norm2(int& x) { x += x >> 31 & P; }
	int x;
	mod_t() {}
	mod_t(int v) : x(v) {}
	mod_t(long long v) : x(v) {}
	mod_t(char v) : x(v) {}
	mod_t operator+(const mod_t& rhs) const { return norm(x + rhs.x - P); }
	mod_t operator-(const mod_t& rhs) const { return norm(x - rhs.x); }
	mod_t operator*(const mod_t& rhs) const { return (L)x * rhs.x % P; }
	void operator+=(const mod_t& rhs) { norm2(x += rhs.x - P); }
	void operator-=(const mod_t& rhs) { norm2(x -= rhs.x); }
	void operator*=(const mod_t& rhs) { x = (L)x * rhs.x % P; }
};

mod_t pw(mod_t x, int y) {
	mod_t r = 1;
	for (; y; y >>= 1, x *= x)
		if (y & 1) r *= x;
	return r;
}

mod_t fac[N], ifac[N];
int n;
void init() {
	0 [fac] = 0 [ifac] = 1;
	for (int i = 1; i < N; i++) i[fac] = (i - 1)[fac] * i;
	ifac[N - 1] = pw(fac[N - 1], P - 2);
	for (int i = N - 2; i; i--) i[ifac] = (i + 1)[ifac] * (i + 1);
}
inline mod_t C(int n, int m) {
	if (n < m || n < 0 || m < 0) return 0;
	return n[fac] * m[ifac] * (n - m)[ifac];
}

std::vector<int> g[N];
mod_t f[N][N];
int sz[N];
char s[N];
void dfs(int x) {
	x[sz] = 1, f[x][1] = 1;
	for (int nx = x * 2; nx <= std::min(n, x * 2 + 1); nx++) {
		dfs(nx);
		if (s[nx] == '<')
			for (int k = x[sz] + nx[sz]; k >= 1; k--) {
				mod_t tmp = 0;
				for (int i = 1; i <= std::min(x[sz], k); i++)
					for (int j = k - i + 1; j <= nx[sz]; j++)
						tmp += f[x][i] * f[nx][j] * C(k - 1, i - 1) *
							   C(x[sz] + nx[sz] - k, x[sz] - i);
				f[x][k] = tmp;
			}
		else
			for (int k = x[sz] + nx[sz]; k >= 1; k--) {
				mod_t tmp = 0;
				for (int i = 1; i <= std::min(x[sz], k); i++)
					for (int j = 1; j <= std::min(k - i, nx[sz]); j++)
						tmp += f[x][i] * f[nx][j] * C(k - 1, i - 1) *
							   C(x[sz] + nx[sz] - k, x[sz] - i);
				f[x][k] = tmp;
			}
		x[sz] += nx[sz];
	}
}

mod_t ans;
int main() {
	init();
	scanf("%d%s", &n, s + 2);
	dfs(1);
	for (int i = 1; i <= n; i++) ans += f[1][i];
	printf("%d\n", ans.x);
}