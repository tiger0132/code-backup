#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long L;
const int N = 3e2 + 23, P = 10007;

int _inv[P];
void init() {
	_inv[1] = 1;
	for (int i = 2; i < P; i++) _inv[i] = (P - P / i) * _inv[P % i] % P;
}
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
	mod_t operator*(const mod_t& rhs) const { return x * rhs.x % P; }
	mod_t operator/(const mod_t& rhs) const { return x * _inv[rhs.x] % P; }
	void operator+=(const mod_t& rhs) { norm2(x += rhs.x - P); }
	void operator-=(const mod_t& rhs) { norm2(x -= rhs.x); }
	void operator*=(const mod_t& rhs) { (x *= rhs.x) %= P; }
	void operator/=(const mod_t& rhs) { (x *= _inv[rhs.x]) %= P; }
} mat[N][N], ans = 1;

int n, m;
int main() {
	init();
	scanf("%d%d", &n, &m);
	for (int i = 1, x, y; i <= m; i++) {
		scanf("%d%d", &y, &x);
		mat[x][y] -= 1;
		mat[y][y] += 1;
	}
	for (int i = 2; i <= n; i++)
		for (int j = i + 1; j <= n; j++)
			while (mat[j][i].x) {
				mod_t t = mat[i][i] / mat[j][i];
				for (int k = i; k <= n; k++) mat[i][k] -= t * mat[j][k];
				for (int k = 2; k <= n; k++) std::swap(mat[i][k], mat[j][k]);
				ans *= P - 1;
			}
	for (int i = 2; i <= n; i++) ans *= mat[i][i];
	printf("%d\n", ans.x);
}