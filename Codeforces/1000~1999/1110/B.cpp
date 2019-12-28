#include <algorithm>
#include <cstdio>

const int N = 1e5 + 51;

int n, m, k, ans;
int d[N];

int main() {
	scanf("%d%d%d", &n, &m, &k);
	for (int i = 1; i <= n; i++) scanf("%d", d + i);
	for (int i = 1; i <= n; i++) d[i - 1] = d[i] - d[i - 1];
	std::sort(d + 1, d + n);
	for (int i = 1; i <= n - k; i++) ans += d[i];
	printf("%d", ans + k);
}