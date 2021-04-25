#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long L;
const int N = 2e2 + 22, P = 1e9 + 7;

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

Z g0[N], g_ln[N], g[N], d[N][N], ans[N];
int n, k;
int main() {
	scanf("%d%d", &n, &k);
	for (int i = 0; i <= k; i++) g0[i] = pw(i + 1, P - 2);
	for (int i = 1; i <= k; i++) {
		Z tmp = 0;
		for (int j = 1; j < i; j++) tmp += (Z)j * g_ln[j] * g0[i - j];
		g_ln[i] = g0[i] - tmp * pw(i, P - 2);
	}
	for (int i = 1; i <= k; i++) g_ln[i] *= n - k + P;
	g[0] = 1;
	for (int i = 1; i <= k; i++) {
		Z tmp = 0;
		for (int j = 1; j <= i; j++) tmp += (Z)j * g_ln[j] * g[i - j];
		g[i] = tmp * pw(i, P - 2);
	}
	d[0][0] = 1;
	for (int i = 1; i <= k; i++) {
		if (i == 1) d[i][0] = 1;
		for (int j = 1; j <= k; j++) d[i][j] = d[i][j - 1] + d[i - 1][j];
		for (int j = 0; j <= k; j++) d[i][j] *= i;
		for (int j = k; j >= 1; j--) d[i][j] = d[i][j - 1] * pw(j, P - 2);
		d[i][0] = 0;
	}
	for (int i = 0; i <= k; i++) {
		Z tmp = 0;
		for (int j = 0; j <= k; j++) tmp += g[j] * d[k - i][k - j];
		for (int j = n; j > n - i; j--) tmp *= j;
		ans[i] = tmp;
		if (i > 1) ans[i] += ans[i - 2];
		if (i) printf("%d%c", ans[i].x, " \n"[i == k]);
	}
}