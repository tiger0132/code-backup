#include <algorithm>
#include <cstdio>
#include <cstring>
#define int long long

int n, a, b, c;
signed main() {
	scanf("%lld%lld%lld%lld", &n, &c, &a, &b);
	for (int x, y = 0, t; y < a; y++)
		if (!((t = c - y * b) % a) && (x = t / a) >= 0 && x + y <= n)
			return !printf("%lld %lld %lld", x, y, n - x - y);
	puts("-1");
}