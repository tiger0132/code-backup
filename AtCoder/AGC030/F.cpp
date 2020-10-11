#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long L;
const int N = 3e2 + 23, M = 6e2 + 26, P = 1e9 + 7;

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
} f[M][N][N], ans;

int a[M], v[M], fl[M], cnt;
int n;
int main() {
	scanf("%d", &n);
	for (int i = 1; i <= 2 * n; i++) {
		scanf("%d", a + i);
		if (a[i] != -1) v[a[i]] = 1;
	}
	for (int i = 1; i <= 2 * n; i += 2)
		if (a[i] < 0 && a[i + 1] < 0)
			cnt++;
		else if (a[i] > 0 && a[i + 1] > 0)
			fl[a[i]] = fl[a[i + 1]] = 1;
	f[2 * n + 1][0][0] = 1;
	for (int i = 2 * n; i >= 1; i--)
		for (int j = 0; j <= n; j++)
			for (int k = 0; k <= n; k++)
				if (fl[i])
					f[i][j][k] = f[i + 1][j][k];
				else if (!v[i]) {
					f[i][j + 1][k] += f[i + 1][j][k];
					if (j) f[i][j - 1][k] += f[i + 1][j][k];
					if (k) f[i][j][k - 1] += f[i + 1][j][k] * k;
				} else {
					f[i][j][k + 1] += f[i + 1][j][k];
					if (j) f[i][j - 1][k] += f[i + 1][j][k];
				}
	ans = f[1][0][0];
	for (int i = 2; i <= cnt; i++) ans *= i;
	printf("%d\n", ans.x);
}