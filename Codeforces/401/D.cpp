#include <algorithm>
#include <cstdio>
#include <cstring>

typedef long long ll;
const int N = 1e5 + 51, K = 1e2 + 21;

int c[11], coef[11];
inline int get(int x, int i) { return x / coef[i] % (c[i] + 1); }

ll dp[N][K];
int m, st;
ll dfs(int x, int rem) {
	if (!x) return !rem;
	if (~dp[x][rem]) return dp[x][rem];
	ll r = 0;
	for (int i = 0; i < 10; i++)
		if ((i || x != st) && get(x, i)) r += dfs(x - coef[i], (rem * 10 + i) % m);
	return dp[x][rem] = r;
}

char s[22];
int main() {
	memset(dp, -1, sizeof dp);
	scanf("%s%d", s, &m);
	for (int i = 0; s[i]; i++) c[s[i] - 48]++;
	coef[0] = 1;
	st = c[0];
	for (int i = 1; i < 10; i++) {
		coef[i] = coef[i - 1] * (c[i - 1] + 1);
		st += c[i] * coef[i];
	}
	printf("%lld", dfs(st, 0));
}