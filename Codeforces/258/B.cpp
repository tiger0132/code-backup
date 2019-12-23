#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 11, P = 1e9 + 7;

int f[N][N][N], num[N], tot;
int dfs(int x, int cnt, int sum, bool lim) {
	if (!x) return cnt == sum;
	if (!lim && ~f[x][cnt][sum]) return f[x][cnt][sum];
	int ub = lim ? x[num] : 9, r = 0;
	for (int i = 0; i <= ub; i++)
		r += dfs(x - 1, cnt + (i == 4 || i == 7), sum, lim && i == ub);
	if (!lim) f[x][cnt][sum] = r;
	return r;
}

int c[N];
int dfs2(int x, int sum) {
	if (x > 7) return 1;
	int ret = 0;
	for (int i = 0; i < sum; i++)
		if (c[i]) ret = (ret + 1ll * c[i]-- * dfs2(x + 1, sum - i)) % P, c[i]++;
	return ret;
}

int n, k, ans;
int main() {
	memset(f, -1, sizeof f);
	scanf("%d", &n);
	for (; n; n /= 10) num[++tot] = n % 10;
	for (int i = 0; i <= tot; i++)
		if ((c[i] = dfs(tot, 0, i, 1))) k = i;
	c[0]--;
	for (int i = 1; i <= k; i++) ans = (ans + 1ll * c[i] * dfs2(2, i)) % P;
	printf("%d", ans);
}