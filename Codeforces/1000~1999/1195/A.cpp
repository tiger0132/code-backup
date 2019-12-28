#include <algorithm>
#include <cstdio>
int a[11111], n, k, x, u, v, c, ans;
int main() {
	scanf("%d%d", &n, &k);
	for (int i = 1; i <= n; i++) scanf("%d", &x), a[x]++;
	for (int i = 1; i <= k; i++) u += a[i] / 2, v += a[i] % 2;
	c = (n + 1) / 2;
	if (u >= c)
		printf("%d", c * 2);
	else
		printf("%d", u * 2 + std::min(c - u, v));
}