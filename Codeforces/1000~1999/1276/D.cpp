#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>

typedef std::pair<int, int> pii;
typedef long long L;
const int N = 2e5 + 52, P = 998244353;

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

std::vector<pii> g[N];
mod_t dp[N][3];
void dfs(int x, int p) {
	mod_t prod = 1;
	int fl = 0;

	dp[x][1] = 1;
	for (auto [_, nx] : x[g]) {
		if (nx == p) {
			fl++;
			continue;
		}
		dfs(nx, x);
		if (!fl) {
			dp[x][0] = dp[x][0] * (dp[nx][0] + dp[nx][2]) + dp[x][1] * dp[nx][2];
			dp[x][1] *= (dp[nx][0] + dp[nx][1]);
			dp[x][2] *= (dp[nx][0] + dp[nx][1]);
		} else {
			dp[x][0] *= (dp[nx][0] + dp[nx][2]);
			dp[x][1] *= (dp[nx][0] + dp[nx][2]);
			dp[x][2] = dp[x][2] * (dp[nx][0] + dp[nx][2]) + prod * dp[nx][2];
		}
		prod *= (dp[nx][0] + dp[nx][1]);
	}
	dp[x][2] += prod;
}

int n, x, y;
int main() {
	scanf("%d", &n);
	for (int i = 1; i < n; i++) {
		scanf("%d%d", &x, &y);
		g[x].push_back({i, y});
		g[y].push_back({i, x});
	}
	dfs(1, 1);
	printf("%d\n", (dp[1][0] + dp[1][1]).x);
}