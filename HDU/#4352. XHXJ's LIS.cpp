#include <algorithm>
#include <cstdio>
#include <cstring>
#define popcnt(x) __builtin_popcount(x)

typedef long long L;
const int N = 22;

L f[N][N][1 << 10];
int rec[N], top;
int nxt(int S, int x) {
	for (int i = x; i < 10; i++)
		if ((S >> i) & 1) return S ^ (1 << i) ^ (1 << x);
	return S ^ (1 << x);
}
L dfs(int i, int k, int S, bool tr, bool lim) {
	if (!i) return popcnt(S) == k;
	if (!lim && ~f[i][k][S]) return f[i][k][S];
	int rb = lim ? rec[i] : 9;
	L ret = 0;
	for (int j = 0; j <= rb; j++) {
		ret += dfs(i - 1, k, tr && !j ? 0 : nxt(S, j), tr && !j, lim && j == rb);
	}
	if (!lim) f[i][k][S] = ret;
	return ret;
}
L calc(L x, int k) {
	for (top = 0; x; x /= 10) rec[++top] = x % 10;
	return dfs(top, k, 0, 1, 1);
}

int k, t;
L l, r;
int main() {
	memset(f, -1, sizeof f);
	for (scanf("%*d"); ~scanf("%lld%lld%d", &l, &r, &k);)
		printf("Case #%d: %lld\n", ++t, calc(r, k) - calc(l - 1, k));
}