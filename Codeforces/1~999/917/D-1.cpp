#include <algorithm>
#include <cstdio>
#include <cstring>

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
	for (; y; y >>= 1, x *= x)
		if (y & 1) r *= x;
	return r;
}

Z g[N][N];
int n;
Z det() {
	Z ret = 1;
	for (int i = 1; i < n; i++) {
		for (int j = i + 1; !g[i][i].x && j < n; j++)
			if (g[j][i].x) ret = -ret, std::swap(g[i], g[j]);
		for (int j = i + 1; j < n; j++) {
			Z d = g[j][i] * pw(g[i][i], P - 2);
			for (int k = i; k < n; k++) g[j][k] -= g[i][k] * d;
		}
		ret = ret * g[i][i];
	}
	return ret;
}

Z dif[N][N], coef[N][N], ans[N];
int ed[N][N];
int main() {
	scanf("%d", &n);
	for (int i = 1, x, y; i < n; i++) {
		scanf("%d%d", &x, &y);
		ed[x][y] = ed[y][x] = 1;
	}
	for (int k = 0; k < n; k++) {
		for (int i = 1; i <= n; i++) g[i][i] = 0;
		for (int i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				if (i != j) {
					int v = ed[i][j] ? k ? P - k : 0 : P - 1;
					g[i][i] -= v, g[i][j] = v;
				}
		dif[0][k] = det();
	}
	coef[1][1] = 1;
	for (int i = 2; i < n; i++)
		for (int j = 1; j <= i; j++)
			coef[i][j] = coef[i - 1][j - 1] - coef[i - 1][j] * (i - 1);
	ans[0] = dif[0][0];
	Z fac = 1;
	for (int i = 1; i < n; i++) {
		Z inv = pw(fac = fac * i, P - 2);
		for (int j = i; j < n; j++) dif[i][j] = dif[i - 1][j] - dif[i - 1][j - 1];
		for (int j = 1; j <= i; j++) ans[j] += dif[i][i] * coef[i][j] * inv;
	}
	for (int i = 0; i < n; i++) printf("%d%c", ans[i].x, " \n"[i == n - 1]);
}