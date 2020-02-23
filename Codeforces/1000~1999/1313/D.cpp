#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 2e5 + 52;

int n, m, k, l[N], r[N], d[N], s[N], cnt, c[23333];
int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= n; i++) {
		scanf("%d%d", l + i, r + i);
		d[++cnt] = l[i], d[++cnt] = ++r[i];
	}
	std::sort(d + 1, d + cnt + 1);
	for (int i = 1; i <= cnt; i++) printf("%d%c", d[i], " \n"[i == cnt]);
	for (int i = 1; i <= n; i++) {
		l[i] = std::lower_bound(d + 1, d + cnt + 1, l[i]) - d;
		r[i] = std::lower_bound(d + 1, d + cnt + 1, r[i]) - d;
		l[i][s] += 1 << (i - 1), r[i][s] -= 1 << (i - 1);
		printf("%d -- %d\n", l[i], r[i]);
		printf("(%d -- %d)\n", l[i], r[i]);
	}
	for (int i = 1; i <= cnt; i++) {
		s[i] += s[i - 1];
		int len = d[i + 1] - d[i];
		printf("[%d] %d\n", len, s[i]);
		for (int T = 1; T < (1 << n); T++)
			if (__builtin_popcount(T & s[i]) % 2) c[T] += len;
	}
	int ans = 0;
	for (int i = 0; i < (1 << n); i++) printf("(%d)", c[i]), ans = std::max(ans, c[i]);
	printf("%d", ans);
}