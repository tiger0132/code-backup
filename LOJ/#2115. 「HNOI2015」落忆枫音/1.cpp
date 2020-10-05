#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>

typedef long long L;
const int N = 1e5 + 51, P = 1e9 + 7;

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

int n, m, x, y, d[N], d2[N];
std::vector<int> g[N];
std::queue<int> q;
mod_t f[N], ans;
int main() {
	scanf("%d%d%d%d", &n, &m, &x, &y), ans = 1;
	for (int i = 1, u, v; i <= m; i++) {
		scanf("%d%d", &u, &v);
		u[g].push_back(v), v[d]++;
	}
	memcpy(d2, d, sizeof d2);
	y[d]++;
	for (int i = 2; i <= n; i++) ans *= i[d];
	if (y == 1) return !printf("%d\n", ans.x);
	f[y] = ans;
	for (int i = 1; i <= n; i++)
		if (!i[d2]) q.push(i);
	for (; !q.empty(); q.pop()) {
		int u = q.front();
		f[u] *= pw(u[d], P - 2);
		for (int nx : u[g]) {
			f[nx] += f[u];
			if (!--nx[d2]) q.push(nx);
		}
	}
	printf("%d\n", (ans - f[x]).x);
}