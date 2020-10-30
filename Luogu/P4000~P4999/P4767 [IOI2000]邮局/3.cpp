// monotone queue, O(n^2 log n)

#include <algorithm>
#include <cstdio>
#include <cstring>

typedef std::pair<int, int> pii;
const int N = 3e3 + 33;

int n, m, a[N], q[N], rb[N], l, r;
int f[N][N], w[N][N];
int fd(int lv, int i, int j) {
	int l = j, r = n + 1;
	while (l <= r) {
		int mid = (l + r) / 2;
		if (f[lv][i] + w[i + 1][mid] >= f[lv][j] + w[j + 1][mid])
			r = mid - 1;
		else
			l = mid + 1;
	}
	return l;
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
	for (int lv = 2; lv <= m; lv++) {
		q[l = r = 1] = 0;
		for (int i = 1; i <= n; i++) {
			while (l < r && rb[l] < i) l++;
			f[lv][i] = f[lv - 1][q[l]] + w[q[l] + 1][i];
			while (l < r && rb[r - 1] >= fd(lv - 1, q[r], i)) r--;
			rb[r] = fd(lv - 1, q[r], i) - 1;
			q[++r] = i;
		}
	}
	printf("%d\n", f[m][n]);
}