// D&C, O(n^2 log n)

#include <algorithm>
#include <cstdio>
#include <cstring>

typedef std::pair<int, int> pii;
const int N = 3e3 + 33;

int f[N][N], w[N][N];
int n, m, a[N];
void solve(int id, int l, int r, int ql, int qr) {
	if (l > r) return;
	int mid = (l + r) >> 1;
	pii v = {1e9, 0};
	for (int k = ql; k <= std::min(mid, qr); k++)
		v = std::min(v, {f[id - 1][k] + w[k + 1][mid], k});
	f[id][mid] = v.first;
	solve(id, l, mid - 1, ql, v.second);
	solve(id, mid + 1, r, v.second, qr);
}
int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	for (int i = 1; i <= n; i++)
		for (int j = i; j <= n; j++) {
			w[i][j] = w[i][j - 1] + a[j] - a[(i + j) >> 1];
		}
	memset(f, 0x3f, sizeof f);
	for (int i = 1; i <= n; i++) f[1][i] = w[1][i];
	for (int i = 2; i <= m; i++) solve(i, 1, n, 1, n);
	printf("%d\n", f[m][n]);
}