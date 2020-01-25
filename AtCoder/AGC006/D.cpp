#include <algorithm>
#include <cstdio>
#include <cstring>
#define mid (l + r) / 2

const int N = 2e5 + 52;

int n, m, a[N];
bool check(int x) {
	for (int i = 0; i < m - 1; i++) {
		if ((a[m + i] <= x && a[m + i + 1] <= x) || (a[m - i] <= x && a[m - i - 1] <= x))
			return 1;
		if ((a[m + i] > x && a[m + i + 1] > x) || (a[m - i] > x && a[m - i - 1] > x))
			return 0;
	}
	return a[1] <= x;
}

int l, r;
int main() {
	scanf("%d", &n);
	m = n, n = n * 2 - 1;
	for (int i = 1; i <= n; i++) scanf("%d", a + i);
	for (l = 1, r = n; l <= r;)
		if (check(mid))
			r = mid - 1;
		else
			l = mid + 1;
	printf("%d", l);
}