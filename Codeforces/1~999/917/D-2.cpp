#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

typedef long long L;
const int N = 1e2 + 21, P = 1e9 + 7;
struct Z {
	static int norm(int x) { return x + (x >> 31 & P); }
	static void norm2(int& x) { x += x >> 31 & P; }
	int x;
	Z() {}
	Z(int v) : x(v) {}
	Z(long long v) : x(v) {}
	Z(char v) : x(v) {}
	Z operator+(const Z& rhs) const { return norm(x + rhs.x - P); }
	Z operator-(const Z& rhs) const { return norm(x - rhs.x); }
	Z operator-() const { return norm(-x); }
	Z operator*(const Z& rhs) const { return (L)x * rhs.x % P; }
	void operator+=(const Z& rhs) { norm2(x += rhs.x - P); }
	void operator-=(const Z& rhs) { norm2(x -= rhs.x); }
	void operator*=(const Z& rhs) { x = (L)x * rhs.x % P; }
};
Z pw(Z x, int y) {
	Z r = 1;
	for (y = (y + P - 1) % (P - 1); y; y >>= 1, x *= x)
		if (y & 1) r *= x;
	return r;
}

Z f[N][N][2], tmp[N][2];
std::vector<int> g[N];
int n, sz[N];
void dfs(int x, int p) {
	f[x][0][0] = f[x][1][1] = 1;
	x[sz] = 1;
	for (int nx : x[g])
		if (nx != p) {
			dfs(nx, x);
			memset(tmp, 0, sizeof tmp);
			for (int i = 0; i <= x[sz]; i++)
				for (int j = 0; j <= nx[sz]; j++) {
					tmp[i + j][0] += f[x][i][0] * (f[nx][j][0] + f[nx][j][1]);
					tmp[i + j][1] += f[x][i][1] * (f[nx][j][0] + f[nx][j][1]) +
									 f[x][i][0] * f[nx][j][1];
				}
			x[sz] += nx[sz];
			memcpy(f[x], tmp, sizeof tmp);
		}
}

Z C[N][N], t[N], ans[N];
int main() {
	scanf("%d", &n);
	for (int i = 1, x, y; i < n; i++) {
		scanf("%d%d", &x, &y);
		x[g].push_back(y);
		y[g].push_back(x);
	}
	dfs(1, -1);
	for (int i = 0; i <= n; i++) {
		C[i][0] = 1;
		for (int j = 1; j <= i; j++) C[i][j] = C[i - 1][j - 1] + C[i - 1][j];
	}
	for (int i = 0; i < n; i++) t[i] = f[1][n - i][1] * pw(n, n - i - 2);
	for (int i = 0; i < n; i++)
		for (int j = i; j < n; j++)
			if ((j - i) & 1)
				ans[i] -= C[j][i] * t[j];
			else
				ans[i] += C[j][i] * t[j];
	for (int i = 0; i < n; i++) printf("%d%c", ans[i].x, " \n"[i == n - 1]);
}