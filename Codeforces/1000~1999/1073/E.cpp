#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long L;
const int N = 22, K = 1024, P = 998244353;

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
struct rec {
	mod_t ans, cnt;
};

int a[N], len, k;
rec dp[N][K];
mod_t pw[N];
rec dfs(int x, int S, bool tr, bool lim) {
	if (!x) return {0, 1};
	if (!tr && !lim && ~dp[x][S].ans.x) return dp[x][S];
	int ub = lim ? x[a] : 9;
	rec ret{0, 0};
	for (int i = 0, T; i <= ub; i++)
		if (__builtin_popcount(T = S | ((i || !tr) << i)) <= k) {
			rec tmp = dfs(x - 1, T, tr && !i, lim && i == ub);
			ret.cnt += tmp.cnt;
			ret.ans += tmp.ans + pw[x - 1] * i * tmp.cnt;
		}
	if (!tr && !lim) dp[x][S] = ret;
	return ret;
}
mod_t calc(L x) {
	for (len = 0; x; x /= 10) a[++len] = x % 10;
	return dfs(len, 0, 1, 1).ans;
}

L l, r;
int main() {
	pw[0] = 1;
	for (int i = 1; i < N; i++) pw[i] = pw[i - 1] * 10;

	memset(dp, -1, sizeof dp);
	scanf("%lld%lld%d", &l, &r, &k);
	printf("%d\n", (calc(r) - calc(l - 1)).x);
}