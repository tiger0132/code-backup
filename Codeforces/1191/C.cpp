#include <algorithm>
#include <cstdio>
#include <cstring>

const int N = 1e5 + 51;

long long n, m, k, lcnt, cnt, ans, x, rb;
int main() {
	scanf("%I64d%I64d%I64d", &n, &m, &k);
	for (int i = 1; i <= m; i++) {
		scanf("%I64d", &x);
		if (x - lcnt > rb) ans++, lcnt = cnt;
		if (x - cnt > rb) rb = (x - cnt + k - 1) / k * k;
		cnt++;
	}
	printf("%I64d", ans);
}