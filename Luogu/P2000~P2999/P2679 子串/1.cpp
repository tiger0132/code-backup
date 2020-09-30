#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e3 + 31, M = 2e2 + 22, P = 1e9 + 7;
struct mod_t {
	static int norm(int x) { return x + (x >> 31 & P); }
	static void norm2(int& x) { x += x >> 31 & P; }
	int x;
	mod_t() {}
	mod_t(int v) : x(v) {}
	mod_t operator+(const mod_t& rhs) const { return norm(x + rhs.x - P); }
	void operator+=(const mod_t& rhs) { norm2(x += rhs.x - P); }
};

mod_t f[M][M][2];
char a[N], b[M];
int n, m, K;
int main() {
	scanf("%d%d%d%s%s", &n, &m, &K, a + 1, b + 1);
	f[0][0][0] = 1;
	for (int i = 1; i <= n; i++)
		for (int j = K; j >= 1; j--)
			for (int k = m; k >= 1; k--) {
				f[j][k][0] += f[j][k][1];
				if (a[i] == b[k])
					f[j][k][1] = f[j][k - 1][1] + f[j - 1][k - 1][0] + f[j - 1][k - 1][1];
				else
					f[j][k][1] = 0;
			}
	printf("%d\n", (f[K][m][0] + f[K][m][1]).x);
}