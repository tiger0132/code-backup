#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
#define int long long

const int INF = 2e9;

int n, h;
bool check(int k) {
	if (k <= h) {
		if (k >= INF) return 1;
		return k * (k + 1) / 2 >= n;
	}
	int mid = (k - h) / 2 + h;
	if (mid >= INF) return 1;
	if ((k - h) % 2) return (mid + h) * (mid - h + 1) + mid * (mid + 1) >= n * 2;
	return (mid - 1 + h) * (mid - h) + mid * (mid + 1) >= n * 2;
}
signed main() {
	scanf("%lld%lld", &n, &h);
	int l = 1, r = n, mid;
	while (l <= r) {
		mid = (l + r) / 2;
		if (check(mid))
			r = mid - 1;
		else
			l = mid + 1;
	}
	printf("%lld", r + 1);
}