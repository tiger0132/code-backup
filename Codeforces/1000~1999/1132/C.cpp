#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 5e3 + 35;

int n, m, ans, sum, l[N], r[N], a[N], f[3][N];

int main() {
	scanf("%d%d", &n, &m);
	for (int i = 1; i <= m; i++) {
		scanf("%d%d", l + i, r + i);
		a[l[i]]++, a[r[i] + 1]--;
	}
	for (int i = 1; i <= n; i++) {
		a[i] += a[i - 1];
		f[1][i] += f[1][i - 1];
		f[2][i] += f[2][i - 1];
		if (a[i]) sum++;
		if (a[i] == 1) f[1][i]++;
		if (a[i] == 2) f[2][i]++;
	}
	for (int i = 1; i < m; i++) {
		for (int j = i + 1; j <= m; j++) {
			int l1 = l[i], r1 = std::min(r[i], l[j] - 1);
			int l2 = l[j], r2 = r[i];
			int l3 = std::max(r[i] + 1, l[j]), r3 = r[j];
			int tmp = sum;
			if (l1 <= r1) tmp -= f[1][r1] - f[1][l1 - 1];
			if (l2 <= r2) tmp -= f[2][r2] - f[2][l2 - 1];
			if (l3 <= r3) tmp -= f[1][r3] - f[1][l3 - 1];
			ans = std::max(ans, tmp);
		}
	}
	printf("%d", ans);
}