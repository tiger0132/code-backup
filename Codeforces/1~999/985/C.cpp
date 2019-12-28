#include <algorithm>
#include <cstdio>
#include <cstring>
#include <iostream>
#define int long long

const int N = 1e5 + 51;

int n, k, l, p1, p2, ans, c, a[N];
signed main() {
	scanf("%lld%lld%lld", &n, &k, &l);
	for (int i = 1; i <= n * k; i++) scanf("%lld", &a[i]);
	std::sort(a + 1, a + n * k + 1);
	if (a[n] - a[1] > l) return puts("0"), 0;
	p1 = n * k;
	while (a[p1] - a[1] > l) p1--;
	p2 = p1;
	for (int i = n * k; i - k >= p1; i = i - k + 1) ans += a[p2--], c++;
	for (int i = 1; i <= p1 - c; i = i + k) ans += a[i];
	printf("%lld", ans);
}